#include "xml/XMLFile.h"

using namespace Xml;


XMLFile::XMLFile(const char* fileName) {

    this->parametersStart = -1;
    this->parametersEnd = -1;
    this->labelsStart = -1;
    this->labelsEnd = -1;
    this->mainStart = -1;
    this->mainEnd = -1;

    this->parameters = nullptr;
    this->labels = nullptr;
    this->main = nullptr;

    this->fileName = fileName;
    this->file = readFile(fileName);

    // This will be filled by this->formatFile()
    this->fileLength = 0;

    // Pre-processing
    this->formatFile();
    this->locateSections();

    /*   Init each tag sequence   */

    // Parameters
    this->parameters = new TagSequence(this->file, this->parametersStart, this->parametersEnd, this->fileName);
    this->parameters->populateStringTags();

    // Labels
    this->labels = new TagSequence(this->file, this->labelsStart, this->labelsEnd, this->fileName);
    this->labels->populateStringTags();

    // Main
    this->main = new TagSequence(this->file, this->mainStart, this->mainEnd, this->fileName);
    this->main->populateStringTags();
    this->main->populatePrimTags();

    this->applyLabels();

    return;

}

XMLFile::~XMLFile() {

    delete[] this->file;

    delete this->parameters;
    delete this->labels;
    delete this->main;

    return;

}

XMLFile* XMLFile::copy() {

    // This empty constructor does not initialize any member variables
    XMLFile* ret = new XMLFile();

    ret->fileName = this->fileName;

    ret->file = new char[this->fileLength];
    memcpy(ret->file, this->file, this->fileLength);
    ret->fileLength = this->fileLength;

    ret->parameters = this->parameters->copy();
    ret->labels = this->labels->copy();
    ret->main = this->main->copy();

    ret->parametersStart = this->parametersStart;
    ret->parametersEnd = this->parametersEnd;
    ret->labelsStart = this->labelsStart;
    ret->labelsEnd = this->labelsEnd;
    ret->mainStart = this->mainStart;
    ret->mainEnd = this->mainEnd;

    return ret;

}

void XMLFile::log() {

    // Log file contents
    logWrite("XMLFile object contents:", true);
    logWrite("File Name: \"");
    logWrite(this->fileName);
    logWrite("\"", true);
    logWrite(this->file);
    
    logWrite("\n\n");

    if (this->parametersStart == -1 || this->parametersEnd == -1) {
        logWrite("No valid <parameters> section!", true);
    } 

    else {
        logWrite("Parameters section:", true);
        for (int i = this->parametersStart; i < this->parametersEnd; i++) {
            logWrite(this->file[i]);
        }
    }

    logWrite("\n\n\n");

    if (this->labelsStart == -1 || this->labelsEnd == -1) {
        logWrite("No valid <labels> section!", true);
    } 

    else {
        logWrite("Labels section:", true);
        for (int i = this->labelsStart; i < this->labelsEnd; i++) {
            logWrite(this->file[i]);
        }
    }

    logWrite("\n\n\n");

    if (this->mainStart == -1 || this->mainEnd == -1) {
        logWrite("No valid <main> section!", true);
    } 

    else {
        logWrite("Main section:", true);
        for (int i = this->mainStart; i < this->mainEnd; i++) {
            logWrite(this->file[i]);
        }
    }

    logWrite("\n\n\n");

    logWrite("Parameters Tag Sequence:", true);

    this->parameters->log();


    logWrite("\n\n\n");

    logWrite("Labels Tag Sequence:", true);

    this->labels->log();


    logWrite("\n\n\n");

    logWrite("Main Tag Sequence:", true);

    this->main->log();

    return;

}

void XMLFile::setParameter(const char* tag, int value) {
    
    char* valueString = new char[MAX_TAG_LENGTH];
    intToString(value, valueString, MAX_TAG_LENGTH);

    // Forward to the const char* overload
    this->setParameter(tag, (const char*) valueString);

    delete[] valueString;

    return;

}

void XMLFile::setParameter(const char* tag, float value) {

    char* valueString = new char[MAX_TAG_LENGTH];
    floatToString(value, valueString, MAX_TAG_LENGTH, 4);

    // Forward to the const char* overload
    this->setParameter(tag, (const char*) valueString);

    delete[] valueString;

    return;
    
}

void XMLFile::setParameter(const char* tag, const char* value) {

    /*
        I need to add an underscore prefix to the parameter tag
        These underscores are used to differentiate between parameter names for the elements, and the parameters of the file
        Because it is added here, it does not need to be included when calling this function
    */

    // Find length
    int length = 0;
    for (; tag[length] != '\0'; length++) {}

    if (length == 0) {
        logWrite("XMLFile::setParameter() was called on a param name that has 0 length!", true);
        return;
    }

    if (length > MAX_TAG_LENGTH) {
        logWrite("XMLFile::setParameter() was called on a param name longer than MAX_TAG_LENGTH!", true);
        logWrite(" -> param name \"");
        logWrite(tag);
        logWrite("\" is longer than MAX_TAG_LENGTH, which is ");
        logWrite(MAX_TAG_LENGTH, true);  
        return;
    }

    char* prefixedTag = new char[length + 2];

    prefixedTag[0] = '_';

    // Copy over the string (with null terminator)
    memcpy(&(prefixedTag[1]), tag, length + 1);

    // Forward to tagSequence
    this->main->swapStringTag(prefixedTag, value);

    // Free the created tag
    delete[] prefixedTag;

    return;
    
}

void XMLFile::setLabel(const char* tag, const char* value) {

    // Just forward to tag sequence
    this->main->swapStringTag(tag, value);

    return; 

}

void XMLFile::formatFile() {

    /*
        This function removes all unnessecary whitespace and non printable characters from the file
        This will write over this->file, but it does not change the contents of the actual file on disk
        The whole point of this is just to make parsing easier. It will be more predictable what will come after what

        I use a two pointer approach here
        The first pointer will refer to the location where the next valid char should go
        The second pointer will refer to the char from the file thats being checked
        This will effectively trim the file, removing all unwanted chars and leaving some extra space at the end
    */

    int firstPointer = 0;
    int secondPointer = 0;

    // Tells if im inside a tag right now
    // This is to allow single spaces in elements, between traits
    bool insideElement = false;

    // Says if the last char was a space or not. This will filter out instances of multiple spaces in a row
    // Only gets used when inside a tag, and it basically caps the spaces at one between traits
    bool lastWasSpace = false;

    char currentChar;
    bool isValid;

    // Used for matching comment block tags. Being "<!--" and "-->"
    char commentChar1;
    char commentChar2;
    char commentChar3;

    // Says if im in a comment or not. While in a comment, all chars are discarded
    bool inComment = false;

    // Second pointer will always be >= first pointer, so no need to check first
    while ( (this->file[secondPointer]) != '\0' ) {

        currentChar = this->file[secondPointer];
        isValid = isValidChar(currentChar);

        // If the character is invalid, move the second pointer over, but keep the first pointer static
        if ( !isValid ) {
            secondPointer++;
            continue;
        }

        // Cases where im entering or leaving an element
        if (currentChar == '<') {
            
            insideElement = true;
            
            // Check for comment block start. This is represented by the substring "<!--"
            // Note: This can read into the null terminator, but it will leave before trying to access past it
            //       Because of the use of goto, it checks each char and only checks the next after ensuring the last was valid

            commentChar1 = this->file[secondPointer + 1];
            if (commentChar1 != '!') goto NoOpenComment;

            commentChar2 = this->file[secondPointer + 2];
            if (commentChar2 != '-') goto NoOpenComment;

            commentChar3 = this->file[secondPointer + 3];
            if (commentChar3 != '-') goto NoOpenComment;

            // If the code reaches here, set the inComment flag
            inComment = true;

        }
        
        // Will jump here if the char is a <, but its not a comment start tag
        NoOpenComment:

        if (currentChar == '>') {
            
            insideElement = false;

            // Check for comment block end. This is represented by the substring "-->"
            // This is easier than the open comment, because I just check the last two characters at the same time
            // I do have to make sure secondPointer is greater than 2 though
            
            if (secondPointer >= 2) {

                commentChar1 = this->file[secondPointer - 1];
                commentChar2 = this->file[secondPointer - 2];

                if (
                    commentChar1 == '-' &&
                    commentChar2 == '-'
                ) {
                    
                    // Reset inComment flag
                    inComment = false;

                    // Skip this char, as its part of the comment
                    secondPointer++;
                    continue;

                }

            }

        }

        // Discard all comment chars
        if (inComment) {
            secondPointer++;
            continue;
        }

        // Handle space characters
        if (currentChar == ' ') {

            // Ignore spaces outside tags
            if (!insideElement) {
                secondPointer++;
                continue;
            }

            // First space inside tag (meaning, not directly after another space)
            if (!lastWasSpace) {
                lastWasSpace = true;
            }

            // Redundant space inside tag
            else {
                secondPointer++;
                continue;
            }

        }

        // Reset lastWasSpace if needed
        else
            lastWasSpace = false;

        // Write the char and move both pointers
        this->file[firstPointer] = currentChar;
        firstPointer++;
        secondPointer++;

    }

    // Null terminate
    this->file[firstPointer] = '\0';
    this->fileLength = firstPointer;

    return;

}

void XMLFile::locateSections() {

    /*
        This finds the index within the file of each reserved tag
        Actually holds the index after the first, and before the second. 
        So the contents between the two indices (inclusive) is whats between the open and close tags

        The reserved tags are:
        - <parameters>  => this->parametersStart
        - </parameters> => this->parametersEnd
        - <labels>      => this->labelsStart
        - </labels>     => this->labelsEnd
        - <main>        => this->mainStart
        - </main>       => this->mainEnd


        This should be called after formatFile, as formatFile will overwrite the contents of this->file
    */


    // Struct to define a search string
    struct SearchTag {
        const char* string;     // String to find
        const int length;       // Length, also determines when its been found. Does NOT include the null terminator
        int index = 0;          // Index of the current char being matched
        bool found = false;     // True if its been found already
        int foundAt = -1;       // Stores the location in the file where the tag exists
    };


    // Parameters open
    SearchTag parametersStart = {"<parameters>", 12};

    // Parameters close
    SearchTag parametersEnd = {"</parameters>", 13};

    // Labels open
    SearchTag labelsStart = {"<labels>", 8};

    // Labels close
    SearchTag labelsEnd = {"</labels>", 9};

    // Main open
    SearchTag mainStart = {"<main>", 6};

    // Main close
    SearchTag mainEnd = {"</main>", 7};

    
    /*   
        Lambda helper functions for the loop   

        These functions update the given SearchTags based on the characters
        In the context of the loop, this will be called for each character in the file

        There is two because theres slightly different handling for start and end tags
        Start tags will find the index after the end of the tag
        Eng tags will find the index before the start of the tag
    */

    // This will be called for each 'Start' tag
    auto matchCharStart = [](SearchTag& tag, char c, int fileIndex) {

        if ( !tag.found ) {

            // Check against current
            if (c == tag.string[tag.index]) {

                tag.index++;

                // If the index matches the last index, the whole string has been found
                if (tag.index == tag.length) {
                    tag.found = true;
                    tag.foundAt = fileIndex + 1;    // This will point to the char after the tag
                }

            }

            // If no match, reset the index
            else tag.index = 0;

        }

    };

    // This will be called for each 'End' tag
    auto matchCharEnd = [](SearchTag& tag, char c, int fileIndex) {

        if ( !tag.found ) {

            // Check against current
            if (c == tag.string[tag.index]) {

                tag.index++;

                // If the index matches the last index, the whole string has been found
                if (tag.index == tag.length) {
                    tag.found = true;
                    tag.foundAt = fileIndex - (tag.length - 1);     // This will point to the char before the tag
                }

            }

            // If no match, reset the index
            else tag.index = 0;

        }

    };


    // Now the loop (which is very simple due to all the work done above)
    char currentChar;
    for (int i = 0; file[i] != '\0'; i++) {

        currentChar = file[i];

        // Start tags
        matchCharStart(parametersStart, currentChar, i);
        matchCharStart(labelsStart,     currentChar, i);
        matchCharStart(mainStart,       currentChar, i);

        // End tags
        matchCharEnd(parametersEnd, currentChar, i);
        matchCharEnd(labelsEnd,     currentChar, i);
        matchCharEnd(mainEnd,       currentChar, i);

    }


    /*   Error checking stuff   */

    // Its not allowed to have EXACLTY ONE of these two tags, so I use XORs here

    // Parameters
    if ( (!parametersStart.found) ^ (!parametersEnd.found) ) {

        // General error output
        logWrite("Error when validating XML file: \'");
        logWrite(this->fileName);
        logWrite("\'", true);
        
        // Specific error outputs
        if ( !parametersStart.found ) {
            logWrite(" -> Failed to find an opening <parameters> tag to match the closing </parameters> tag", true);
        }

        else if ( !parametersEnd.found ) {
            logWrite(" -> Failed to find a closing </parameters> tag to match the opening <parameters> tag", true);
        }

        // Do not finish the code. This leaves all the section pointers as -1
        return;

    }

    // Labels
    if ( (!labelsStart.found) ^ (!labelsEnd.found) ) {
        
        // General error output
        logWrite("Error when validating XML file: \'");
        logWrite(this->fileName);
        logWrite("\'", true);
        
        // Specific error outputs
        if ( !labelsStart.found ) {
            logWrite(" -> Failed to find an opening <labels> tag to match the closing </labels> tag", true);
        }

        else if ( !labelsEnd.found ) {
            logWrite(" -> Failed to find a closing </labels> tag to match the opening <labels> tag", true);
        }

        // Do not finish the code. This leaves all the section pointers as -1
        return;

    }

    // There must be a main block, so if either doesnt exist, throw an error
    if ( (!mainStart.found) || (!mainEnd.found) ) {

        // General error output
        logWrite("Error when validating XML file: \'");
        logWrite(this->fileName);
        logWrite("\'", true);
        
        // Specific error outputs
        if ( (!mainStart.found) && (!mainEnd.found) ) {
            logWrite(" -> Failed to find an opening <main> tag and a closing </main> tag", true);
        }

        else if ( !mainStart.found ) {
            logWrite(" -> Failed to find an opening <main> tag", true);
        }

        else if ( !mainEnd.found ) {
            logWrite(" -> Failed to find a closing </main> tag", true);
        }

        // Do not finish the code. This leaves all the section pointers as -1
        return;
        
    }

    /*   Order checking   */

    // If any of these tags are backwards (End before Start), loops in other functions will break

    // Parameters
    if ( (parametersStart.found) && (parametersEnd.found) ) {   // Verify that the parameters section exists, as its not mandatory
        if ( parametersStart.foundAt > parametersEnd.foundAt ) {

            logWrite("Error when validating XML file: \'");
            logWrite(this->fileName);
            logWrite("\'", true);

            logWrite(" -> </parameters> tag should not appear before <parameters> tag");

        }
    }

    // Labels
    if ( (labelsStart.found) && (labelsEnd.found) ) {   // Verify that the labels section exists, as its not mandatory
        if ( labelsStart.foundAt > labelsEnd.foundAt ) {

            logWrite("Error when validating XML file: \'");
            logWrite(this->fileName);
            logWrite("\'", true);

            logWrite(" -> </labels> tag should not appear before <labels> tag");

        }
    }

    // Main
    if ( mainStart.foundAt > mainEnd.foundAt ) {

        logWrite("Error when validating XML file: \'");
        logWrite(this->fileName);
        logWrite("\'", true);

        logWrite(" -> </main> tag should not appear before <main> tag");

    }


    // Store the found values
    this->parametersStart = parametersStart.foundAt;
    this->parametersEnd = parametersEnd.foundAt;
    this->labelsStart = labelsStart.foundAt;
    this->labelsEnd = labelsEnd.foundAt;
    this->mainStart = mainStart.foundAt;
    this->mainEnd = mainEnd.foundAt;

    return;

}

void XMLFile::applyLabels() {
    
    // Skip if there is no labels section
    if (this->labelsStart == -1 || this->labelsEnd == -1) return;

    int labelCount = this->labels->stringTagCount;

    if (labelCount % 2 != 0) {
        logWrite("XML::applyLabels() found an uneven number of label tags!", true);
        logWrite(" -> In file \"");
        logWrite(this->fileName);
        logWrite("\"", true);
        return;
    }

    char* oldTag;
    char* newTag;

    // This is passed as the outparam to TagSequence::getStringTag() becuase I dont care about the length here
    int _;

    for (int i = 0; i < labelCount; i += 2) {

        // Get the 2 string tags from the label
        oldTag = this->labels->getStringTag(i, &_);
        newTag = this->labels->getStringTag(i + 1, &_);

        // Treat the label as a parameter (its functionally the same)
        this->setLabel(oldTag, newTag);

    }

    return;

}

#include "ui/XML.h"



/*   Functions only accessible in this file   */
namespace {

    bool isValidChar(char c) {

        // Only spaces count as syntactical whitespace
        if (c == ' ') return true;

        // Allow only chars between a certain range, which is the range of readable ASCII chars
        // Between 0x20 and 0x7E inclusive
        return ( c >= 0x20 && c <= 0x7E );

    }

    bool isReservedChar(char c) {

        // These are all the reserved chars. ie. not allowed in tag names
        if (c == '<') return true;
        if (c == '>') return true;
        if (c == '/') return true;
        if (c == '=') return true;
        if (c == ' ') return true;

        return false;

    }

    int getTagLength(const char* tag) {

        int length = 0;
    
        for (; tag[length] != '\0'; length++) {
    
            // Return error value if length exceeds MAX_TAG_LENGTH
            if (length >= MAX_TAG_LENGTH) return -1;
    
        }
    
        return length;
    
    }

}



// Constructor
XML::XML(const char* fileName) {

    // Variable initialization
    this->parametersStart = -1;
    this->parametersEnd = -1;
    this->labelsStart = -1;
    this->labelsEnd = -1;
    this->mainStart = -1;
    this->mainEnd = -1;

    this->tagSequence = nullptr;

    this->fileName = fileName;
    this->file = readFile(fileName);

    // Pre-processing
    this->formatFile();
    this->locateSections();

    // Init tag sequence
    this->tagSequence = new TagSequence(this->file, this->mainStart, this->mainEnd);
    this->populateTagSequence();

    // Log file contents
    logWrite("Full file contents:", true);
    logWrite(this->file);
    
    logWrite("\n\n\n");

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

    this->tagSequence->log();

    logWrite("\n\n\n");

    this->setParameter("_width", 12345);

    this->tagSequence->log();

    logWrite("\n\n\n");

    this->applyLabels();

    this->tagSequence->log();

    return;

}

// Destructor
XML::~XML() {

    if (this->file != nullptr) delete[] this->file;
    if (this->tagSequence != nullptr) delete[] this->tagSequence;

    return;

}

// Instance Functions
void XML::setParameter(const char* tag, int value) {
    
    char* valueString = new char[MAX_TAG_LENGTH];
    intToString(value, valueString, MAX_TAG_LENGTH);

    // Forward to the const char* overload
    this->setParameter(tag, (const char*) valueString);

    delete[] valueString;

}

void XML::setParameter(const char* tag, float value) {

    char* valueString = new char[MAX_TAG_LENGTH];
    floatToString(value, valueString, MAX_TAG_LENGTH, 4);

    // Forward to the const char* overload
    this->setParameter(tag, (const char*) valueString);

    delete[] valueString;
    
}

void XML::setParameter(const char* tag, const char* value) {

    // Forward to tagSequence
    this->tagSequence->swapTag(tag, value);
    
}

WindowElement* XML::buildElement() {
    return nullptr;
}

Window* XML::buildWindow() {
    return nullptr;
}

void XML::formatFile() {

    /*
        This function removes all unnessecary whitespace and non printable characters from the file
        This will write over this->file, but it does not change the contents in a way that affects the data within
        The whole point of this is just to make parsing easier, it will be more predictable what will come after what

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

    // For the loop
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

    return;

}

void XML::locateSections() {

    /*
        This finds the index within the file of each reserved tag
        Actually holds the index after the first, and before the second. 
        So the contents between the two indices is whats between the open and close tags

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
        In the context of the loop, these will be called for each character in the file

        There is two because theres slightly different handling for start and end tags
        Start tags will find the index after the end of the tag
        Eng tags will find the index before the start of the tag
        This leaves a range that represents the data between the two tags
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


    // Now the loop
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

        // Do not finish the code. This leaves the section pointers as -1
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

        // Do not finish the code. This leaves the section pointers as -1
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

        // Do not finish the code. This leaves the section pointers as -1
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

void XML::populateTagSequence() {

    /*   Stuff for the first loop   */

    // This is the internal index of the tag. 
    // This is related, but not the same as, the actual index of this->tagSequence
    int tagIndex = 0;

    // This will point to the first char of the current string tag
    // This is used to copy the string tag from this->file to this->tagSequence
    char* tagStart = nullptr;

    // Current character being handled + flag if its a reserved char (see XML::isReserved() for details)
    char currentChar;
    bool isReserved;

    // True when the index lies inside a string tag, this lets each non reserved char side by side count as just one tag
    bool inTag = false;

    // This is the length of the current string tag. This is passed to this->setTag()
    int tagLength = 0;

    // This loop populates the string tags only.
    // Only the main section is parsed here, as the other sections are treated differently
    for (int i = this->mainStart; i < this->mainEnd; i++) {

        currentChar = this->file[i];
        isReserved = isReservedChar(currentChar);

        if (isReserved) {
            
            // This means i just finished iterating over a string tag
            if (inTag) {

                // Write the tag to this->tagSequence
                this->tagSequence->setTag(tagIndex, tagStart, tagLength);

                // Update the tagIndex to the next slot
                tagIndex++;

                // Reset the flag
                inTag = false;
                tagLength = 0;

            }

        }

        else {

            // If im already in a tag, add another char to the length
            if (inTag) {
                tagLength++;
            }

            // If not, this is the start of a new tag
            else {

                // Store the first char of the tag
                tagStart = &(this->file[i]);

                // Set the flag
                inTag = true;
                tagLength = 1;

            }

        }

    }


    /*   Stuff for the second loop   */

    // Reset
    currentChar = '\0';
    tagIndex = 0;
    inTag = false;

    // Here i need to know the previous char in some contexts
    char prevChar;

    // Flags for if each primitive tag is open or closed in the current context
    bool inParams = false;
    bool inChildren = false;

    // Used for checking previously set state. This is needed in some contexts
    PrimitiveTagState state;

    // This loop populates the primitive tags
    // I do also need to keep track of the tagIndex here, so a bunch of the logic is copied from the last loop
    // This all *could* be in the same loop as above, but i chose to seperate them for readability
    for (int i = this->mainStart; i < this->mainEnd; i++) {

        prevChar = currentChar;
        currentChar = this->file[i];
        isReserved = isReservedChar(currentChar);

        if (isReserved) {
            
            // This means i need to update the tagIndex
            if (inTag) {

                // Update the tagIndex to the next slot
                tagIndex++;

                // Reset the flag
                inTag = false;

            }

            // Reserved char handling
            switch (currentChar) {

                case '<': {

                    /*
                        The < usually indicates ELEMENT OPEN
                        The only exception is when the next char is a /,
                        but that would be overwritten in the '/' case anyway

                        There can also be a case with the substring "/><" where ELEMENT should CLOSE and OPEN
                        In this case, i use the CLOSE_OPEN state
                        I check for this by seeing if the state is already on CLOSE
                    */

                    state = this->tagSequence->getPrimitiveTag(tagIndex, ELEMENT);

                    if (state == CLOSE) {
                        this->tagSequence->setPrimitiveTag(tagIndex, ELEMENT, CLOSE_OPEN);
                    }

                    else {
                        this->tagSequence->setPrimitiveTag(tagIndex, ELEMENT, OPEN);
                    }

                    break;

                }

                case '>': {

                    /*
                        The only logical use of the > character is to delimit the params and children sections
                        This always closes the PARAMS section if it is OPEN
                        This only opens CHILDREN if the last char was not a /
                    */
                    
                    // CLOSE PARAMS if needed
                    if (inParams) {
                        this->tagSequence->setPrimitiveTag(tagIndex, PARAMS, CLOSE);
                        inParams = false;
                    }
                    
                    // OPEN CHILDREN if the element was not self closing
                    if (prevChar != '/') {
                        this->tagSequence->setPrimitiveTag(tagIndex, CHILDREN, OPEN);
                        inChildren = true;
                    }

                    break;

                }

                case '/': {

                    /*
                        A / character indicates the end of the element
                        This will also reset both PARAMS and CHILDREN to CLOSE if they were OPEN

                        There also needs to be some special handling in the case of the substring "/></"
                        In this case, i use the DOUBLE_CLOSE state to indicate a self closing tag right before a closing tag
                    */
            
                    state = this->tagSequence->getPrimitiveTag(tagIndex, ELEMENT);

                    // If two / chars appear next to each other, this is invalid
                    if (prevChar == '/') {

                        logWrite("XML::populateTagSequence() found 2 '/' characters in a row!", true);

                        logWrite(" -> In file \"");
                        logWrite(this->fileName);
                        logWrite("\"", true);

                        logWrite(" -> This is most likely a typo in the file", true);

                        return;

                    }

                    // Overwrite CLOSE_OPEN with DOUBLE_CLOSE if applicable
                    if (state == CLOSE_OPEN) {
                        this->tagSequence->setPrimitiveTag(tagIndex, ELEMENT, DOUBLE_CLOSE);
                    }

                    else {
                        this->tagSequence->setPrimitiveTag(tagIndex, ELEMENT, CLOSE);
                    }

                    // CLOSE other types if needed
                    if (inParams) {
                        this->tagSequence->setPrimitiveTag(tagIndex, PARAMS, CLOSE);
                        inParams = false;
                    }

                    if (inChildren) {
                        this->tagSequence->setPrimitiveTag(tagIndex, CHILDREN, CLOSE);
                        inChildren = false;
                    }

                    break;

                }

                case ' ': {

                    /*
                        The space handling is very simple becuase i filtered out all spaces not inside tags
                        This means that any space will indicate the beginning of the PARAMS section
                        That is unless it is already open of course
                    */

                    if (inParams) break;

                    this->tagSequence->setPrimitiveTag(tagIndex, PARAMS, OPEN);
                    inParams = true;

                    break;

                }

                // Equals is also reserved, but i dont need to track it
                default:
                    break;

            }

        }

        else {
            inTag = true;
        }

    }

    return;

}

void XML::applyLabels() {

    // Skip if there is no labels section
    if ( (this->labelsStart == -1) || (this->labelsEnd == -1) ) return;

    // These variables store the new and old tag values specified by each label
    // These are seperate buffers so they can be properly null terminated and passed to setParameter
    // The +1 is so theres space for the null terminator
    char* oldTag = new char[MAX_TAG_LENGTH + 1];
    int oldTagIndex = 0;

    char* newTag = new char[MAX_TAG_LENGTH + 1];
    int newTagIndex = 0;

    // Current char data
    char currentChar;
    bool isReserved;

    // This says which buffer is currently being written to
    // Enum is used for better readability
    enum ActiveBuffer {
        NONE,
        OLD,
        NEW
    };
    ActiveBuffer activeBuffer = NONE;

    // This is used for debugging to specify which label has the issue
    int labelNumber = 1;

    // Loop through the labels section
    for (int i = this->labelsStart; i < this->labelsEnd; i++) {

        currentChar = this->file[i];
        isReserved = isReservedChar(currentChar);

        if (isReserved) {

            switch (currentChar) {

                // These are all equivalent in this context
                // Any of these just mean that the last label is done and the next one will be starting
                case '<':
                case '>':
                case '/': {

                    // This means there is no data to use yet
                    if (activeBuffer == NONE) break;

                    // This means there was no equals in the label element
                    if (activeBuffer == OLD) {

                        logWrite("Warning: XML::applyLabels() found no equals in one of the label elements!", true);

                        logWrite(" -> In file \"");
                        logWrite(this->fileName);
                        logWrite("\" at label ");
                        logWrite(labelNumber, true);

                        break;

                    }

                    // Make sure there are valid strings for each buffer before trying to set the label
                    if ( (oldTagIndex > 0) && (newTagIndex > 0) ) {

                        // Null terminate each buffer
                        oldTag[oldTagIndex] = '\0';
                        newTag[newTagIndex] = '\0';

                        // Write the label using setParameter
                        this->setParameter(
                            (const char*) (oldTag),
                            (const char*) (newTag)
                        );

                        // Update number
                        labelNumber++;

                    }

                    // Reset the indexes in prep for the next label
                    oldTagIndex = 0;
                    newTagIndex = 0;
                    activeBuffer = NONE;

                    break;

                }


                // Equals seperates the new and old tags
                case '=': {

                    // Set activeBuffer if needed
                    if (activeBuffer == NONE) {
                        activeBuffer = OLD;
                    }
                    
                    // This means there was more than one equals in the element
                    if (activeBuffer == NEW) {

                        logWrite("Warning: XML::applyLabels() found more than one equals in one of the label elements!", true);

                        logWrite(" -> In file \"");
                        logWrite(this->fileName);
                        logWrite("\" at label ");
                        logWrite(labelNumber, true);

                        break;

                    }

                    activeBuffer = NEW;
                    break;

                }

                // This shouldnt ever happen
                default:
                    break;

            }

        }

        else {

            if (activeBuffer == NONE) {
                activeBuffer = OLD;
            }

            switch (activeBuffer) {

                case OLD:
                    oldTag[oldTagIndex] = currentChar;
                    oldTagIndex++;
                    break;

                case NEW:
                    newTag[newTagIndex] = currentChar;
                    newTagIndex++;
                    break;

                // activeBuffer == NONE is not possible, because its set above
                default:
                    break;

            }

        }

    }

    // Clean up
    delete[] oldTag;
    delete[] newTag;

}

#include "ui/XML.h"

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
    this->tagSequenceLength = -1;

    this->fileName = fileName;
    this->file = readFile(fileName);

    // Pre-processing
    this->formatFile();
    this->locateSections();

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

    logWrite("Buffer length needed: ");
    logWrite(this->getSequenceLength(), true);


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
    
    char* valueString = new char[32];
    intToString(value, valueString, 32);

    this->setParameter(tag, (const char*) valueString);

    delete[] valueString;

}

void XML::setParameter(const char* tag, float value) {

    char* valueString = new char[32];
    floatToString(value, valueString, 32, 4);

    this->setParameter(tag, (const char*) valueString);

    delete[] valueString;
    
}

void XML::setParameter(const char* tag, const char* value) {

    // Traverse the XML file, this can be sped up by:
    //      - Using the fact that every custom tag is 32 bytes, and every primitive tag is 1 byte
    //      - This lets you check each custom char until it mismatches, then jump almost directly to the start of the next

    // find any tags that match the requested one
    // Anything that matches will be swapped with value
    
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
    // In this case, single spaces are allowed as whitespace between traits
    bool insideTag = false;

    // Says if the last char was a space or not. This will filter out any multiple spaces in a row
    // Only gets used when inside a tag, and it basically caps the spaces at one between traits
    bool lastWasSpace = false;

    // For the loop
    char currentChar;
    bool isValid;

    // Second pointer will always be >= first pointer, so no need to check first
    while ( (this->file[secondPointer]) != '\0' ) {

        currentChar = this->file[secondPointer];
        isValid = XML::isValidChar(currentChar);

        // If the character is invalid, move the second pointer over, but keep the first pointer static
        if ( !isValid ) {
            secondPointer++;
            continue;
        }

        // Determine if im entering or leaving a tag
        if (currentChar == '<') insideTag = true;
        if (currentChar == '>') insideTag = false;

        // Handle space characters
        if (currentChar == ' ') {

            // Ignore spaces outside tags
            if (!insideTag) {
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


    // Stuff for the loop
    int index = 0;
    char currentChar;

    while (file[index] != '\0') {

        currentChar = file[index];


        // Start tags
        matchCharStart(parametersStart, currentChar, index);
        matchCharStart(labelsStart,     currentChar, index);
        matchCharStart(mainStart,       currentChar, index);

        // End tags
        matchCharEnd(parametersEnd, currentChar, index);
        matchCharEnd(labelsEnd,     currentChar, index);
        matchCharEnd(mainEnd,       currentChar, index);


        index++;

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

int XML::getSequenceLength() {

    /*
        This returns the length of string needed to hold all of the XML data inside the <main> tag
        This will just count the amount of complex tags inside main, then add space for the primitive tags as well
        The total count will be:
        (tagCount * XML::MAX_TAG_LENGTH) + ((tagCount + 1) * 3)
    */


    // Error check
    if ( (this->mainStart == -1) || (this->mainEnd == -1) ) {

        // General error output
        logWrite("Cannot get sequence length of invalid main tag", true);

        // Specific error outputs
        if (this->mainStart == -1)
            logWrite(" -> Missing <main> tag!", true);

        if (this->mainEnd == -1)
            logWrite(" -> Missing </main> tag!", true);

        // Invalid return value
        return -1;

    }

    
    // Helper lamba function for loop
    // Just returns true 


    // Stuff for the loop
    char currentChar;
    bool isReserved;

    // Counts the complex tags (XML::MAX_TAG_LENGTH bytes each)
    int tagCount = 0;

    // True when the index lies inside a tag, this lets each non reserved char side by side count as just one tag
    bool inTag = false;


    // Iterate over data between <main> and </main>
    for (int i = this->mainStart; i < this->mainEnd; i++) {

        currentChar = this->file[i];
        isReserved = XML::isReservedChar(currentChar);

        if (isReserved) {
            
            if (inTag) {
                inTag = false;
                tagCount++;
            }

        }

        else {
            inTag = true;
        }

    }
    
    int length = ( (tagCount * XML::MAX_TAG_LENGTH) + ((tagCount + 1) * 3) );

    this->tagSequenceLength = length;
    return length;

}

void XML::populateTagSequence() {

    if (this->tagSequenceLength <= 0) {
        logWrite("Cannot populate tag sequence before finding length needed!", true);
        logWrite(" -> Must call XML::getSequenceLength() before XML::populateTagSequence()", true);
        return;
    }

    // Allocate for tag sequence buffer
    this->tagSequence = new char[this->tagSequenceLength];
    int bufferPointer = 0;

    /*   This loop populates the string tags (XML::MAX_TAG_LENGTH bytes each)   */

    // Skip the first three bytes (they are primitive tag bytes)
    bufferPointer = 3;

    // This ensures i dont accidentally write past the buffer length
    int bufferPointerLimit = this->tagSequenceLength - 36;

    for (int i = this->mainStart; i < this->mainEnd; i++) {

        if (bufferPointer >= )

    }

    return;

}

bool XML::isValidChar(char c) {

    // Only spaces count as syntactical whitespace
    if (c == ' ') return true;

    // Allow only chars between a certain range, which is the range of readable ASCII chars
    // Between 0x20 and 0x7E inclusive
    return ( c >= 0x20 && c <= 0x7E );

}

bool XML::isReservedChar(char c) {

    // These are all the reserved chars. ie. not allowed in tag names
    if (c == '<') return true;
    if (c == '>') return true;
    if (c == '/') return true;
    if (c == '=') return true;
    if (c == ' ') return true;

    return false;

}

#include "xml/TagSequence.h"


// Constructor
TagSequence::TagSequence(char* file, int fromIndex, int toIndex) {

    /*
        This returns the length of string needed to hold all of the XML data inside the <main> tag
        This will just count the amount of complex tags inside main, then add space for the primitive tags as well
        The total count will be:
        (tagCount * XML::MAX_TAG_LENGTH) + ((tagCount + 1) * XML::PRIM_TAG_LENGTH)
    */


    // Stuff for the loop
    char currentChar;
    bool isReserved;

    // Counts the complex tags (XML::MAX_TAG_LENGTH bytes each)
    int tagCount = 0;

    // True when the index lies inside a tag, this lets each non reserved char side by side count as just one tag
    bool inTag = false;


    // Iterate over data between <main> and </main>
    for (int i = fromIndex; i < toIndex; i++) {

        currentChar = file[i];
        isReserved = isReservedChar(currentChar);

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
    
    int length = ( (tagCount * MAX_TAG_LENGTH) + ((tagCount + 1) * PRIM_TAG_LENGTH) );

    this->bufferLength = length;
    this->tagCount = tagCount;
    this->primTagCount = tagCount + 1;

    // Allocate the buffer
    this->buffer = new char[this->bufferLength];

    // Initialize the buffer values
    memset(this->buffer, '\0', this->bufferLength);

    for (int i = 0; i < this->primTagCount; i++)
        this->resetPrimitiveTags(i);

    logWrite("Buffer length needed: ");
    logWrite(this->bufferLength);
    logWrite(" bytes", true);

    return;

}

// Destructor
TagSequence::~TagSequence() {
    if (this->buffer != nullptr) delete[] this->buffer;
}

// Instance Functions
void TagSequence::log() {

    logWrite("Tag Sequence:", true);

    int offset;
    int tagIndex;

    PrimitiveTagType primType;
    PrimitiveTagState primState;

    for (int i = 0; i < this->bufferLength; i++) {

        offset = i % (MAX_TAG_LENGTH + PRIM_TAG_LENGTH);
        tagIndex = floor( (float) ( i / (MAX_TAG_LENGTH + PRIM_TAG_LENGTH) ) );

        // Prim tag logging
        if (offset < PRIM_TAG_LENGTH) {
            
            primType = (PrimitiveTagType) offset;
            primState = this->getPrimitiveTag(tagIndex, primType);

            // Skip logging NONE states
            if (primState == NONE) continue;

            logNewLine();

            logWrite("[ Prim Tag ]   -> ");

            switch (primType) {
                
                case ELEMENT:
                    logWrite("Element");
                    break;
                
                case PARAMS:
                    logWrite("Params");
                    break;

                case CHILDREN:
                    logWrite("Children");
                    break;

                default:
                    logWrite("???");
                    break;

            }

            logWrite(" = ");

            switch (primState) {
                
                case OPEN:
                    logWrite("Open");
                    break;

                case CLOSE:
                    logWrite("Close");
                    break;

                case CLOSE_OPEN:
                    logWrite("Close-Open");
                    break;

                case DOUBLE_CLOSE:
                    logWrite("Double-Close");
                    break;

                default:
                    logWrite("???");
                    break;

            }

        }

        // String tag label
        if (offset == PRIM_TAG_LENGTH) {
            logNewLine();
            logWrite("[ String Tag ] -> ");
        }

        // String tag logging
        if (offset >= PRIM_TAG_LENGTH)
            logWrite(this->buffer[i]);

    }

    return;

}

int TagSequence::validatePrimTags() const {
    return 0;
}

char* TagSequence::getTag(int index, int* lengthOut) const {

    if (lengthOut == nullptr) {
        logWrite("Tried to call XML::getTag(int, int*) on a nullptr!", true);
        return nullptr;
    }

    // Check for invalid index. Logging is handled within the call
    if (validateTagIndex(index, "getTag")) return nullptr;


    // This finds the effective index in tagSequence for the given index
    // Start by skipping the first primitive tags
    int effectiveIndex = PRIM_TAG_LENGTH;

    // Each index needs to be XML::MAX_TAG_LENGTH + XML::PRIM_TAG_LENGTH bytes apart
    effectiveIndex += (index * (MAX_TAG_LENGTH + PRIM_TAG_LENGTH));

    // This shouldnt ever happen becuase i check index against this->tagCount, but its good to be sure
    if (effectiveIndex + MAX_TAG_LENGTH >= this->bufferLength) {

        logWrite("Tried to call XML::getTag(int, int*) with out of bounds index!", true);
        logWrite(" -> Tried index ");
        logWrite(index);
        logWrite(", effective index is ");
        logWrite(effectiveIndex);
        logWrite(" which is beyond the maximum of ");
        logWrite(this->bufferLength, true);
        
        return nullptr;

    }

    // Find the length of the tag, either until a null terminator or XML::MAX_TAG_LENGTH
    int tagLength = 0;
    while (true) {

        /*   Break cases   */

        // If the string is less than XML::MAX_TAG_LENGTH bytes, there will be '\0' filling the rest of the space
        if (this->buffer[effectiveIndex + tagLength] == '\0') break;

        tagLength++;

        // If the tag is the max length. In this case there wont be a '\0' char so i must check this manually
        // This also decrements the length count, because it will be 1 higher than allowed
        if (tagLength > MAX_TAG_LENGTH) {
            tagLength--;
            break;
        }

    }

    // Set the lengthOut parameter
    *lengthOut = tagLength;

    // Return the pointer to the tag location in tagSequence
    return &(this->buffer[effectiveIndex]);

}

void TagSequence::setTag(int index, char* tag, int length) {

    if (this->buffer == nullptr) {
        logWrite("Tried to call XML::setTag(int, char*, int) before initializing tagSequence!", true);
        return;
    }

    if (tag == nullptr) {
        logWrite("Tried to call XML::setTag(int, char*, int) on a nullptr!", true);
        return;
    }

    // Check for invalid index. Logging is handled within the call
    if (validateTagIndex(index, "setTag")) return;

    // This finds the effective index in tagSequence for the given index
    // Start by skipping the first primitive tags
    int effectiveIndex = PRIM_TAG_LENGTH;

    // Each index needs to be XML::MAX_TAG_LENGTH + XML::PRIM_TAG_LENGTH bytes apart
    effectiveIndex += (index * (MAX_TAG_LENGTH + PRIM_TAG_LENGTH));
    
    // This shouldnt ever happen becuase i check index against this->tagCount, but its good to be sure
    if (effectiveIndex + MAX_TAG_LENGTH >= this->bufferLength) {

        logWrite("Tried to call XML::setTag(int, char*, int) with out of bounds index!", true);
        logWrite(" -> Tried index ");
        logWrite(index);
        logWrite(", effective index is ");
        logWrite(effectiveIndex);
        logWrite(" which is beyond the maximum of ");
        logWrite(this->bufferLength, true);

        return;
        
    }

    int effectiveLength = length;

    // Warning if the length is too big
    // This is just so i know if i need to increase the max length
    // This will also cap the length to XML::MAX_TAG_LENGTH
    if (length > MAX_TAG_LENGTH) {

        logWrite("Warning: [XML::setTag()] Tried to write a tag longer than maximum allowed length!", true);
        logWrite(" -> Tried to write length ");
        logWrite(length);
        logWrite(" while the max length is ");
        logWrite(MAX_TAG_LENGTH, true);

        effectiveLength = MAX_TAG_LENGTH;

    }

    // Copy the bytes over
    memcpy(
        &(this->buffer[effectiveIndex]),   // Location to write
        tag,                                    // Source
        effectiveLength                         // Byte count
    );

    // Fill the rest of the space in the tag with '\0' chars
    if (effectiveLength < MAX_TAG_LENGTH) {
        memset(
            &(this->buffer[effectiveIndex + effectiveLength]),     // Location to write
            '\0',                                                  // Byte to write
            MAX_TAG_LENGTH - effectiveLength                       // Byte count
        );
    }

    return;

}

void TagSequence::swapTag(const char* oldTag, const char* newTag) {

    // Error checks
    if (oldTag == nullptr) {
        logWrite("Called TagSequence::swapTag(const char*, const char*) with 'oldTag' as a null pointer!", true);
        return;
    }

    if (newTag == nullptr) {
        logWrite("Called TagSequence::swapTag(const char*, const char*) with 'newTag' as a null pointer!", true);
        return;
    }

    /*   Find length of each tag   */

    // Returns -1 if tag is too long
    int oldTagLength = getTagLength(oldTag);

    // Log error if the length is invalid
    if (oldTagLength < 0) {

        logWrite("TagSequence::swapTag() is trying to find a string tag longer than MAX_TAG_LENGTH!", true);
        
        logWrite(" -> is trying to find \"");
        logWrite(oldTag);
        logWrite("\", while the maximum allowed length is ");
        logWrite(MAX_TAG_LENGTH, true);
        
        logWrite(" -> Either update MAX_TAG_LENGTH, or fix the input string", true);

        return;

    }

    // Returns -1 if tag is too long
    int newTagLength = getTagLength(newTag);

    // Log error if the length is invalid
    if (newTagLength < 0) {

        logWrite("TagSequence::swapTag() is trying to write a string tag longer than MAX_TAG_LENGTH!", true);
        
        logWrite(" -> is trying to write \"");
        logWrite(newTag);
        logWrite("\", while the maximum allowed length is ");
        logWrite(MAX_TAG_LENGTH, true);
        
        logWrite(" -> Either update MAX_TAG_LENGTH, or fix the input string", true);

        return;
        
    }


    // Stuff for the loop

    // Holds the return values of this->getTag()
    char* currentTag;
    int currentTagLength;

    // This is just used to track if no matches were found
    // If none were found I log it, just in case that was not intended
    int matchCount = 0;

    // Loop to find and replace the applicable tags
    for (int i = 0; i < this->tagCount; i++) {

        // Get tag values
        currentTag = this->getTag(i, &currentTagLength);

        // Early continue if lengths do not match
        if (oldTagLength != currentTagLength) continue;

        // Iterate over the tag to compare
        bool matches = true;
        for (int j = 0; j < currentTagLength; j++) {

            if (oldTag[j] != currentTag[j]) {
                matches = false;
                break;
            }

        }

        // If the loop never reset matches, the tag should be replaced
        if (matches) {
            this->setTag(i, (char*) newTag, newTagLength);
            matchCount++;
        }

    }

    // Log warning if the parameter was not found
    if (matchCount == 0) {
        logWrite("Warning: TagSequence::swapTag() did not find the given oldTag!", true);
        logWrite(" -> Tried to find \"");
        logWrite(oldTag);
        logWrite("\" but failed", true);
    }

    return;

}

void TagSequence::resetPrimitiveTags(int index) {

    // Check for invalid index. Logging is handled within the call
    if (validatePrimTagIndex(index, "resetPrimitiveTags")) return;


    int effectiveIndex = index * (MAX_TAG_LENGTH + PRIM_TAG_LENGTH);

    this->buffer[ effectiveIndex + ( (int) ELEMENT ) ]  = NONE;
    this->buffer[ effectiveIndex + ( (int) PARAMS ) ]   = NONE;
    this->buffer[ effectiveIndex + ( (int) CHILDREN ) ] = NONE;

    return;
    
}

PrimitiveTagState TagSequence::getPrimitiveTag(int index, PrimitiveTagType type) const {

    // Check for invalid index. Logging is handled within the call
    if (validatePrimTagIndex(index, "getPrimitiveTag")) return NONE;

    // Effective index of the start of the primitive tag buffer
    int effectiveIndex = index * (MAX_TAG_LENGTH + PRIM_TAG_LENGTH);

    // Returns the respective byte, after casting to the enum
    return ( (PrimitiveTagState) this->buffer[ effectiveIndex + ( (int) type ) ] );

}

void TagSequence::setPrimitiveTag(int index, PrimitiveTagType type, PrimitiveTagState state) {

    // Check for invalid index. Logging is handled within the call
    if (validatePrimTagIndex(index, "setPrimitiveTag")) return;

    // Effective index of the start of the primitive tag buffer
    int effectiveIndex = index * (MAX_TAG_LENGTH + PRIM_TAG_LENGTH);

    this->buffer[ effectiveIndex + ( (int) type ) ] = ( (char) state );

    return;

}

int TagSequence::validateTagIndex(int index, const char* functionName) const {

    // Too low
    if (index < 0) {

        // If no function name was given, output a general log
        if (functionName == nullptr) {
            logWrite("Tried to call unspecified TagSequence function with index less than 0!", true);
        }

        // Otherwise give a specific output log
        else {
            logWrite("Tried to call TagSequence::");
            logWrite(functionName);
            logWrite(" with index less than 0!", true);
        }

        return 1;

    }

    // Too high
    if (index >= this->tagCount) {

        // If no function name was given, output a general log
        if (functionName == nullptr) {
            logWrite("Tried to call unspecified TagSequence function with index out of range!", true);
        }

        // Otherwise give a specific output log
        else {
            logWrite("Tried to call TagSequence::");
            logWrite(functionName);
            logWrite(" with index out of range!", true);
        }

        logWrite(" -> Tried index ");
        logWrite(index);
        logWrite(" with tagCount of ");
        logWrite(this->tagCount, true);

        return 1;

    }

    // Index is valid
    return 0;

}

int TagSequence::validatePrimTagIndex(int index, const char* functionName) const {

    // Too low
    if (index < 0) {

        // If no function name was given, output a general log
        if (functionName == nullptr) {
            logWrite("Tried to call unspecified TagSequence function with index less than 0!", true);
        }

        // Otherwise give a specific output log
        else {
            logWrite("Tried to call TagSequence::");
            logWrite(functionName);
            logWrite(" with index less than 0!", true);
        }

        return 1;

    }

    // Too high
    if (index >= this->primTagCount) {

        // If no function name was given, output a general log
        if (functionName == nullptr) {
            logWrite("Tried to call unspecified TagSequence function with index out of range!", true);
        }

        // Otherwise give a specific output log
        else {
            logWrite("Tried to call TagSequence::");
            logWrite(functionName);
            logWrite(" with index out of range!", true);
        }

        logWrite(" -> Tried index ");
        logWrite(index);
        logWrite(" with primTagCount of ");
        logWrite(this->primTagCount, true);

        return 1;

    }

    // Index is valid
    return 0;

}
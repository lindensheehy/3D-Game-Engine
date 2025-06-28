#pragma once

#include "util/Utility.h"

#include "xml/Core.h"


namespace Xml {

class TagSequence {

    /*
        This class is sort of just a glorified string buffer
        This just abstracts away from the byte level operations needed to work with the raw XML
        
        Functionally you can treat it as two arrays, with one having an extra element
        One array holds the string tags (after calling TagSequence::populateStringTags())
        The other holds the primitive tags (after calling TagSequence::populatePrimTags())
    */

    public: 

        /*   Instance Variables   */

        // These hold the amounts of each tag in the buffer
        // Used for validating indexes
        int stringTagCount;
        int primTagCount;


        // Constructor
        TagSequence(char* file, int fromIndex, int toIndex, const char* fileName = nullptr);

        // Destructor
        ~TagSequence();


        /*   Instance Functions   */

        // Performs a deep copy
        TagSequence* copy() const;

        // Logs the contents of the tag sequence
        void log() const;

        // Populates 'stringTagCount', 'primTagCount', and 'bufferLength'
        void findBufferLength();

        // Gets the string tag at the given index. lengthOut will be filled with the length of the tag
        char* getStringTag(int index, int* lengthOut) const;

        // Will set the tag at the given index to the string. Will only write to length, or XML::MAX_TAG_LENGTH (whatever is smaller)
        void setStringTag(int index, char* tag, int length);

        // Swaps each instance of oldTag with newTag in the internal buffer
        void swapStringTag(const char* oldTag, const char* newTag);
        
        // Sets all the primitive tags at that index to NONE states
        void resetPrimitiveTags(int index);

        // Returns the PrimitiveTag stored at that index for the respective type
        PrimitiveTagState getPrimitiveTag(int index, PrimitiveTagType type) const;

        // Puts a primitive tag at a location. The actual position is right before the cooresponding string tag index
        void setPrimitiveTag(int index, PrimitiveTagType type, PrimitiveTagState state);

        void populateStringTags();

        void populatePrimTags();


    private:

        /*   Instance Variables   */

        // This is the file that the TagSequence is related to
        char* file;
        int fileLength;

        // This class really doesnt need this, but it helps to log specific errors
        const char* fileName;

        // Buffer holding the tagSequence
        char* buffer;
        int bufferLength;


        /*   Instance Functions  */

        // Empty constructor to help with deep copy
        TagSequence() {}

        // Returns non zero if the index is out of range
        // functionName can be optionally used to more specific logging
        int validateStringTagIndex(int index, const char* functionName = nullptr) const;

        // Returns non zero if the index is out of range
        // functionName can be optionally used to more specific logging
        int validatePrimTagIndex(int index, const char* functionName = nullptr) const;

};

}

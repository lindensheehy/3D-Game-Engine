#pragma once

#include "util/Utility.h"


class TagSequence {

    /*
        This class is sort of just a glorified string buffer
        This just abstracts away from the byte level operations needed to work with the XML
        
        Functionally you can treat it as two arrays, with one having an extra element
        Only 
    */

    public: 

        // Constructor
        TagSequence(char* file, int fromIndex, int toIndex);

        // Destructor
        ~TagSequence();

        /*   Instance Functions   */

        // Logs the contents of the tag sequence
        void log();

        // Returns non zero if the primitive tags are invalid
        // Also logs specific errors on invalid tags
        int validatePrimTags() const;

        // Gets the string tag at the given index. lengthOut will be filled with the length of the tag
        char* getTag(int index, int* lengthOut) const;

        // Will set the tag at the given index to the string. Will only write to length, or XML::MAX_TAG_LENGTH (whatever is smaller)
        void setTag(int index, char* tag, int length);

        // Swaps each instance of oldTag with newTag in the internal buffer
        void swapTag(const char* oldTag, const char* newTag);
        
        // Sets all the primitive tags at that index to NONE states
        void resetPrimitiveTags(int index);

        // Returns the PrimitiveTag stored at that index for the respective type
        PrimitiveTagState getPrimitiveTag(int index, PrimitiveTagType type) const;

        // Puts a primitive tag at a location. The actual position is right before the cooresponding string tag index
        // More than one can be set at once. This is capped at XML::PRIM_TAG_LENGTH, which is the amount of types of prim tags
        // This is just to abstract away from the byte level operations involved
        void setPrimitiveTag(int index, PrimitiveTagType type, PrimitiveTagState state);

    private:

        /*   Instance Variables   */

        // Buffer holding the tagSequence
        char* buffer;
        int bufferLength;

        // These hold the amounts of each tag in the buffer
        // Used for validating indexes
        int tagCount;
        int primTagCount;


        /*   Instance Functions  */

        // Returns non zero if the index is out of range
        // functionName can be optionally used to more specific logging
        int validateTagIndex(int index, const char* functionName = nullptr) const;

        // Returns non zero if the index is out of range
        // functionName can be optionally used to more specific logging
        int validatePrimTagIndex(int index, const char* functionName = nullptr) const;

};
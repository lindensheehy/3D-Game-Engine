#pragma once

constexpr int MAX_TAG_LENGTH = 64;

// These help to group the Primitive tags. The values are the relative indexes
constexpr int PRIM_TAG_LENGTH = 3;
enum PrimitiveTagType : int {

    ELEMENT = 0,
    PARAMS = 1,
    CHILDREN = 2

};

// These are the actual bytes that are stored in the buffer
enum PrimitiveTagState : char {

    // These are the possible states for each PrimitiveTagType
    NONE = 0x00,
    OPEN = 0x02,
    CLOSE = 0x03,

    /*   These ones should be unique to the ELEMENT type   */

    // This is used when two elements lie directly next to each other
    // Indicated by substring "/><"
    CLOSE_OPEN = 0x04,

    // This is used when there is a self closing tag right before a closing tag
    // Indicated by substring "/></"
    DOUBLE_CLOSE = 0x05

};

// This is used to determine expected trait types on XML elements
enum TraitType {
    INT,
    FLOAT,
    STRING,
};

/*   Some general helper functions   */

// Returns true if the char should be considered valid in the XML file
bool isValidChar(char c);

// Returns true if the char is reserved. ie. disallowed in tag names
// This counts: '<' '>' '/' '=' ' '
bool isReservedChar(char c);

// Returns the length of the tag. 
// Very similar to strlen, but this early returns after a certain length
int getTagLength(const char* tag);

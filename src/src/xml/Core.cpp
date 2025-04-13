#include "xml/Core.h"

using namespace Xml;


bool Xml::isValidChar(char c) {

    // Only spaces count as syntactical whitespace
    if (c == ' ') return true;

    // Allow only chars between a certain range, which is the range of readable ASCII chars
    // Between 0x20 and 0x7E inclusive
    return ( c >= 0x20 && c <= 0x7E );

}

bool Xml::isReservedChar(char c) {

    // These are all the reserved chars. ie. not allowed in tag names
    if (c == '<') return true;
    if (c == '>') return true;
    if (c == '/') return true;
    if (c == '=') return true;
    if (c == ' ') return true;

    return false;

}

int Xml::getTagLength(const char* tag) {

    int length = 0;

    for (; tag[length] != '\0'; length++) {

        // Return error value if length exceeds MAX_TAG_LENGTH
        if (length >= MAX_TAG_LENGTH) return -1;

    }

    return length;

}

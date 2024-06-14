#include <iostream>

#include "../src/log/log.cpp"

int main() {

    logInit("testlog.txt");

    logWrite("test");

    return 0;
}
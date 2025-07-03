#pragma once

#include "util/Log.h"


// Test counters
int totalTests;
int passedTests;

// This template allows this class to be used for any function signature
template<typename returnType, typename... args>
class FunctionWrapper {
    /*
        This class is used to define functions based on their return value and parameters
        The reason for this is so there is a general testing function hich is defined once somewhere rather than having it seperately a bunch of times
    */

    public:

        // Hold the function pointer
        returnType (*func)(args...);
        const char* funcName;

        // Constructor
        FunctionWrapper(returnType (*func)(args...), const char* funcName) {
            this->func = func;
            this->funcName = funcName;
        }

        // Calls the function with a set of arguments
        returnType call(args... arguments) {
            return func(arguments...);
        }

        // This calls the function with some args and tests it against the expected value
        // percentTolerance is the percent difference the actual is allowed to be off from the expected by
        bool test(returnType expected, args... arguments, double percentTolerance = 0) {

            // Get actual value
            
            // Hide any written logs from function call, like error messages
            logWrite("<span class=\"hidden\">\n");
            returnType actual = func(arguments...);
            logWrite("</span>\n");

            double error;
            bool passed;

            if (percentTolerance == 0) {
                passed = (actual == expected);
            }

            else {

                if (expected != 0) 
                    error = 100 * (((double) actual - (double) expected) / (double) expected);
                else
                    error = 100 * ((double) actual);

                passed = ((error >= 0) ? error : -error) <= percentTolerance;

            }

            totalTests++; 

            logWrite(
                "<br>\n"
                "<p>\n"
            );

            logWrite("Test: ");
            logWrite(this->funcName);
            logWrite("(");

            bool firstFlag = true;

            // Lambda function to log packed items
            (..., [&]
            {   
                
                // Print the ", " on every iteration after the first
                if (firstFlag)
                    firstFlag = false;
                else
                    logWrite(", ");

                logWrite(arguments);

            } ());

            logWrite(") == ");
            logWrite(expected);
            logNewLine();

            if (passed) {
                logWrite(
                    "<span class=\"test-pass\">\n"
                    "   Passed!\n"
                    "</span>\n"
                );  

                if (percentTolerance != 0) {
                    logWrite("<p class=\"note\">\n");
                    logWrite( "Error: ");
                    logWrite(error);
                    logWrite(" / ");
                    logWrite(percentTolerance);
                    logWrite(" %");
                    logWrite("</p>\n");
                }

                logWrite(
                    "</p>\n"
                );

                passedTests++;
                return true;
            }

            else {
                
                logWrite(
                    "<span class=\"test-fail\">\n"
                    "   Failed!\n"
                    "</span>\n"
                );
                logWrite("<p class=\"note\">\n");
                logWrite("Output: ");
                logWrite(actual);
                logWrite("</p>\n");

                logWrite(
                    "</p>\n"
                );

                return false;
            }

        }

};

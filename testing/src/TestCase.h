#include "FunctionWrapperClass.h"
#include "ArgWrapperClass.h"

#include "../../src/log/log.h"

// This template allows this class to be used for any function signature
template<typename returnType, typename... args>
class TestCase {
    /*
        This class is used to create test cases
        As an input it takes a function to test and a set of parameters and return values to test
    */

    public:

        // Instance Variables
        FunctionWrapper<returnType, args...>* func;
        ArgWrapper<args...> argSet;

        // Constructor
        TestCase(FunctionWrapper<returnType, args...>* func, ArgWrapper<args...> argSet) {
            this->func = func;
            this->argSet = argSet;
        }

        // Destructor
        ~TestCase() {
            
            if (this->func != nullptr)
                delete this->func;

            if (this->argSet != nullptr)
                delete this->argSet;

            return;

        }

        /*   Instance Functions   */

        // Runs all test cases
        void run() {

        }

    private:

        /*   Instance Functions   */

        // Runs a single test case. This is called from run()
        void runSet(int set) {

        }

};
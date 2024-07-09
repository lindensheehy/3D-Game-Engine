

class TestCase {
    /*
        This class is used to create test cases
        As an input it takes a function to test and a set of parameters and return values to test
    */

    public:

        class Function {
            /*
                This class is used to define functions based on their return value and parameters
                The reason for this is so the TestCase class can just use an instance of this rather than having tons functions
            */

            /*   Instance Variables   */

            void* (*func)(args...);


            // Constructors
            Function(double (*func)(double)) {
                this->func = func;
            }

        };

        // Constructor
        TestCase();

};
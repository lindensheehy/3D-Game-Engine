template<typename... types>
class SetList {

};

template<typename... args>
        class ArgumentSet {
            /*
                Hold a single set of arguments
                These objects are used in ArgWrapper
            */

            public:

                args* items;

                ArgumentWrapper(int size, args... input) {
                    this->items = new args[sizeof...(args) * size]{input...};
                }

                ~ArgumentSet() {

                    if (this->items != nullptr) 
                        delete[] this->items;

                    return;

                }

        };

template<typename type>
class LinkedList;

class WindowHandle;

class DataClass;

// I am just using namespace here, but keep in mind what i said above

class BindManager {

    public:

        struct Bind {
            WindowHandle* handle;
            void (*func)(void*);
        };  

        LinkedList<Bind>* BindSet;

        BindManager() {

            this->binding = new Binding();

        }

        class Binding {

            public:

                Binding() {

                    this->window3 = new Window3();

                    // Add more instantiations as needed

                }
            
                void bindWindow1(WindowHandle* handle);

                void bindWindow2(WindowHandle* handle);

                class Window3 {

                    public:

                        DataClass* someData;

                        Window3() : someData(nullptr) {} 

                        void bindWindow3(WindowHandle* handle);

                    private:

                        // Functions bound to buttons
                        void window3Button1();
                        void window3Button2();

                };
                Window3* window3;

                // Add more classes as needed

        };


        Binding* binding;
    
};


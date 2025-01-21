#include "ui/Action.h"

class Action {

    /*
        Super class for all actions that buttons should do.
        This class does nothing on its own and shouldnt be used, the subclasses are the useful part
    */

    public:

        /*   Instance Variables   */

        // Constructor
        Action();

        // Destructor
        virtual ~Action();

        /*   Instance Functions   */

        virtual void run() {}

};


class ActionLogWrite : public Action {

    public:

        /*   Instance Variables   */

        const char* message;

        // Constructor
        ActionLogWrite(const char* message);

        // Destructor
        ~ActionLogWrite() override;

        /*   Instance Functions   */

        void run() override;

};


class ActionCloseWindow : public Action {

    public:

        /*   Instance Variables   */

        UI* ui; 
        Window* window; // Window to close

        // Constructor
        ActionCloseWindow(UI* ui, Window* window);

        // Destructor
        ~ActionCloseWindow() override;

        /*   Instance Functions   */

        void run() override;

};
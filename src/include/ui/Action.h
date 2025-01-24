

enum ActionType {
    CLOSE_WINDOW,
    WRITE_TO_VALUE
};

class Action {

    public:

        // Constructor
        Action();

        // Destructor
        virtual ~Action();

};

class ActionCloseWindow : public Action {

    public:

        // Constructor
        ActionCloseWindow();

        // Destructor

};
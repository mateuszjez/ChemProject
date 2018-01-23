#ifndef EQUATION_MENU_H
#define EQUATION_MENU_H
#include "StateMachine.h"
#include "EquationReader.h"

class Equation_Menu : StateMachine{
    public:
        Equation_Menu() {
            try{
                form_reader.getAtomList("AtomList.txt");
                able_to_run = true;
                }
            catch(std::exception& e){std::cerr<<e.what();}
        }
        ~Equation_Menu() {std::cout<<"\n~Equation_Menu()\n";}
        Command run(bool show_dialog = true);                                           ///overridden, return type may be changed
        bool is_able_to_run() {return able_to_run;}
    protected:
    ///Commands:
        const std::string CMDNAME   = "name";
        const std::string CMDREADEQ = "eq";
        const std::string CMDFIXEQ  = "fix";
        const std::string CMDPRINTEQ= "print";
        const std::string CMDREVEQ  = "rev";
    ///States:
        const std::string NAME      = "name";
        const std::string READEQ    = "read_equation";
        const std::string FIXEQ     = "fix_equation";
        const std::string PRINTEQ   = "print_equation";
        const std::string REVEQ     = "reverse_equation";

    private:
        FormulaReader   form_reader;
        Equation        equation;
        EquationReader  eq_reader;
        bool            able_to_run = false;
    ///States declarations
        Command stateStart(bool show_dialog = true);                               ///overridden
        Command stateHelp(bool show_dialog = true);                                ///overridden
        Command stateName(bool show_dialog = true);            ///to set name of created object
        Command stateReadEquation(bool show_dialog = true);
        Command stateFixEquation(bool show_dialog = true);
        Command statePrintEquation(bool show_dialog = true);
        Command stateReverseEquation(bool show_dialog = true);
    ///Other functions
        std::string command_interpreter(std::string parent_state, Command command);  ///overridden, returns state
        bool is_command(Command cmd);                                           ///overridden,
        bool is_command(std::string str) {return is_command(Command(str));}     ///overloaded,
};

#endif // EQUATION_MENU_H

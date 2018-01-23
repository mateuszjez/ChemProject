#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED
#include "StateMachine.h"
#include "Equation_Menu.h"

class Main_Menu : StateMachine{
    public:
        Main_Menu() {}
        ~Main_Menu() {std::cout<<"\n~Main_Menu()\n";}
        Command run(bool show_dialog = true);               ///overridden,
    protected:
    ///State identifiers and associated commands:
        const std::string EQUATION  = "chemical_equation";
        const std::string CMDEQ     = "equation";
        const std::string PROCESS   = "chemical_process";
        const std::string CMDPROCESS= "process";
        const std::string FDBASE    = "formulas_database";  ///proposition
        const std::string CMDFDBASE = "fdbase";             ///proposition
        const std::string RDBASE    = "reactions_database"; ///proposition
        const std::string CMDRDBASE = "rdbase";             ///proposition
    ///Other Commands:
    private:
    ///Declarations of states
        Command stateStart(bool show_dialog = true);               ///overridden,
        Command stateHelp(bool show_dialog = true);                ///overridden,
        Command stateEquation(bool show_dialog = true);
        Command stateProcess(bool show_dialog = true);             ///may consist a set of equation type objects
        Command stateFormulasDataBase(bool show_dialog = true);    ///proposition
        Command stateReactionsDataBase(bool show_dialog = true);   ///proposition
    ///Other functions
        std::string command_interpreter(std::string parent_state, Command command);  ///overridden, returns state
        bool is_command(Command cmd);                                           ///overridden,
        bool is_command(std::string str) {return is_command(Command(str));}     ///overloaded,
};


#endif // MAIN_MENU_H_INCLUDED

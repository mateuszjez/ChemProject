#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <iostream>
#include <cstdlib>
#include "Inspect.h"
#include "Command.h"

    class StateMachine{
        public:
            StateMachine() {}
            virtual ~StateMachine() {std::cout<<"\n~StateMachine()\n";}

        protected:
            Command command_reader();                       ///may be overridden but does not have to
            ///States identifiers:
            const std::string START     = "start";
            const std::string WELCOME   = "welcome";
            const std::string HELP      = "help";
            const std::string RETURN    = "return";
            const std::string QUITATTMPT= "quit_attempt";
            const std::string QUITDEF   = "quit_definitely";
            const std::string CLRSCRN   = "clear_screen";
            const std::string IGNORE    = "stateIgnore";
            ///Commands:
            const std::string CMDSTART  = "start";
            const std::string CMDRETURN = "return";
            const std::string CMDABOUT  = "about";
            const std::string CMDHELP   = "help";
            const std::string CMDWELCOME= "welcome";
            const std::string CMDQUIT   = "quit";
            const std::string CMDQUITDEF= "quit_definitely";
            const std::string CMDNOTLOW = "not_lower_case";
            const std::string CMDNEWLINE= "new_line";
            const std::string CMDCLRSCRN= "cls";
            const std::string CMDIGNORE = "command_ignore";

        ///declarations of main loop
            virtual Command run(bool show_dialog) = 0;

        ///declarations of states
            Command             stateDefault(std::string state,Command command);
            virtual Command     stateStart(bool show_dialog) = 0;
            virtual Command     stateHelp(bool show_dialog)  = 0;
            Command             stateIgnore(Command command);///special state
            void                ignore_residual_strings();  ///uses command_buffer
            void                clearScreen() {system("cls");}
            Command             get_command_buffer() const {return command_buffer;}
            bool                is_last_command() {return command_buffer.is_last;}
            std::string         command_interpreter(std::string parent_state, Command command); ///command interpreter, returns state

        private:
            Command             stateWelcome(bool show_dialog = true);
            Command             stateClearScreen(Command command);
            Command             stateQuitAttempt(bool show_dialog = true);
            Command             command_buffer;
            virtual bool is_command(Command str) = 0;
            StateMachine(const StateMachine&);
            StateMachine& operator=(const StateMachine&);
    };

#endif // STATEMACHINE_H

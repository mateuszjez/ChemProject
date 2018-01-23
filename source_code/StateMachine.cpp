#include "StateMachine.h"

Command StateMachine::command_reader(){
    command_buffer.is_last = true;
    char ch = char(std::cin.peek());

    while(true){                            ///cleaning white spaces
        std::cin.get(ch);
        if(!isspace(ch)||ch=='\n') break;   ///'\n' must be excluded from white spaces to stop the loop at the end of line
    }

    if(islower(ch)) {///first lowercase means command
        std::cin.putback(ch);
        std::string strcommand;
        while(true){
            std::cin.get(ch);
            if(!isspace(ch)) strcommand = strcommand + ch;
            else{
                command_buffer = strcommand;
                if(ch!='\n') {command_buffer.is_last = false;
//            std::cout<<" command_buffer.is_last = false : 1; command: "<<command_buffer.command<<"\n";
                }
                return command_buffer;
            }
        }
    }
    else if(ch=='\n') { ///'\n' will be returned as a new line
        command_buffer = CMDNEWLINE;
        command_buffer.is_last = true;
//            std::cout<<" command_buffer.is_last = true : 1; command: "<<command_buffer.command<<"\n";
        return command_buffer;
    }
    else {                      ///not lowercase will be returned as a command
        command_buffer = CMDNOTLOW;
        std::cin.putback(ch);///if character is put back, value is_last must not be true (value ch still remains in cin buffer)
        command_buffer.is_last = false;
//            std::cout<<" command_buffer.is_last = false : 2; command: "<<command_buffer.command<<"\n";
        return command_buffer;
    }
    return command_buffer;
}
Command StateMachine::stateDefault(std::string state,Command command) {
    if(state==WELCOME)          return stateWelcome();
    else if(state==CLRSCRN)     return stateClearScreen(command);
    else if(state==QUITATTMPT)  return stateQuitAttempt(command.is_last);
    return command;
}
Command StateMachine::stateWelcome(bool show_dialog){
    std::cout<< "Welcome to chemical interpreter and calculator.\n"
                "Author: Mateusz Jez, 30 October 2017\n"
                "Press enter to continue or type 'help' to learn more.\n";
    if(show_dialog) std::cout<<"> ";
    Command command = command_reader();
    //ignore_residual_strings();
    return command;
}
Command StateMachine::stateQuitAttempt(bool show_dialog){
    if(show_dialog) std::cout<<"Do you really want to quit the program (y/n): ";
    while(true){
        Command decision        = command_reader();
        if(decision=="y")       return Command(CMDQUITDEF);
        else if(decision=="n")  return Command(CMDSTART);
        else std::cout<<"Wrong command type 'y' for yes or 'n' for no: ";
    }
}
Command StateMachine::stateClearScreen(Command command){///special state
    clearScreen();
    command = CMDSTART;///is_last field remains unchanged
    return command;
}
Command StateMachine::stateIgnore(Command command){///special state
//    std::cout<<"\nstateIgnore:\ncommand = "<<command.command<<command.is_last<<"\n";
//    Command cmdh=get_command_buffer();
//    std::cout<<"command_buffer = "<<cmdh.command<<cmdh.is_last<<"\n";
    ignore_residual_strings();
    return command;
}
void    StateMachine::ignore_residual_strings(){
    if(command_buffer.is_last) return;
    else{
        char ch;
        while(true){
            std::cin.get(ch);
            if(ch=='\n'){
                command_buffer.is_last = true;
                return;
            }
        }
    }
    return;
}

std::string StateMachine::command_interpreter(std::string parent_state, Command command){///overridden, returns state
//Inspect::insp_variable("command","command_interpreter",command);
    if(command==CMDABOUT)           return WELCOME;
    else if(command==CMDWELCOME)    return WELCOME;
    else if(command==CMDHELP)       return HELP;
    else if(command==CMDRETURN)     return RETURN;
    else if(command==CMDQUIT)       return QUITATTMPT;
    else if(command==CMDQUITDEF)    return QUITDEF;
    else if(command==CMDCLRSCRN)    return CLRSCRN;
    return parent_state;
}


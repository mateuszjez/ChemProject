#include "Main_Menu.h"
///Overridden functions:
std::string Main_Menu::command_interpreter(std::string parent_state, Command command){///overridden, returns state
    if(command==CMDEQ)              return EQUATION;
    else if(command==CMDPROCESS)    return PROCESS;
    else if(command==CMDRETURN)     return START;
    else if(command==CMDNOTLOW)     return IGNORE;
    return StateMachine::command_interpreter(parent_state,command);
}
Command Main_Menu::run(bool show_dialog){///overridden, returns command
    Command command = CMDWELCOME;
    std::string state = command_interpreter(START,command);
    while(true){
        if(state==START)            command = stateStart(show_dialog);
        else if(state==HELP)        command = stateHelp(show_dialog);
        else if(state==EQUATION)    command = stateEquation(show_dialog);
        else if(state==PROCESS)     command = stateProcess(show_dialog);
        else if(state==FDBASE)      command = stateFormulasDataBase(show_dialog);
        else if(state==RDBASE)      command = stateReactionsDataBase(show_dialog);
        else if(state==QUITDEF)     return command;
        else if(state==IGNORE)      command = stateIgnore(CMDSTART);
        else                        command = stateDefault(state,command);
        show_dialog = is_last_command();
        state = command_interpreter(START,command);
    }
    return command;
}
Command Main_Menu::stateStart(bool show_dialog){///overridden, returns command
    if(show_dialog)
        std::cout<<"Choose operating mode or type 'help' to learn more:\n> ";
    return command_reader();
}
Command Main_Menu::stateHelp(bool show_dialog){///overridden, returns command
    Command command("All");
    if(!show_dialog) command = command_reader();
    ignore_residual_strings();
    if(command==CMDNEWLINE) command = "All";
    bool othr = true;
    if(command==CMDABOUT||command=="All"){std::cout<<"\t"<<CMDABOUT<<"\t- information about program (splash screen)\n";othr=false;}
    if(command==CMDEQ||command=="All")   {std::cout<<"\t"<<CMDEQ<<"- simple chemical equation mode\n";othr=false;}
    if(command==CMDPROCESS||command=="All"){std::cout<<"\t"<<CMDPROCESS<<"\t- chemical process mode\n";othr=false;}
    if(command==CMDFDBASE||command=="All"){std::cout<<"\t"<<CMDFDBASE<<"\t- browsing through formulas database\n";othr=false;}
    if(command==CMDRDBASE||command=="All"){std::cout<<"\t"<<CMDRDBASE<<"\t- browsing through reaction database\n";othr=false;}
    if(command==CMDQUIT||command=="All")  {std::cout<<"\t"<<CMDQUIT<<"\t- quit the program\n";othr=false;}
    if(command==CMDCLRSCRN||command=="All")  {std::cout<<"\t"<<CMDCLRSCRN<<"\t- clear the screen\n";othr=false;}
    if(command==CMDHELP||command=="All")  {std::cout<<"\t"<<CMDHELP<<"\t- information about available commands\n";othr=false;}
    if(othr) std::cout<<"\t'"<<command.command<<"; is not recognized as a command\n";
    std::cout<<"> ";
    return command_reader();
}
bool        Main_Menu::is_command(Command cmd){///overridden
    if(command_interpreter("not_command",cmd)=="not_command") return false;
    else return true;
}

///this machine functions
Command Main_Menu::stateEquation(bool show_dialog){
    Command command(CMDSTART);
    Equation_Menu eq_machine;
    if(eq_machine.is_able_to_run()) command = eq_machine.run(is_last_command());
    else ignore_residual_strings();
    return command;
}

Command Main_Menu::stateProcess(bool show_dialog){             ///may consist a set of equations objects
    std::cout<<"\nprocess mode is not implemented yet\n> ";
    Command command = command_reader();
    //ignore_residual_strings();
    return command;
}
Command Main_Menu::stateFormulasDataBase(bool show_dialog){    ///proposition
    std::cout<<"\nprocess fdbase is not implemented yet\n> ";
    return command_reader();
}
Command Main_Menu::stateReactionsDataBase(bool show_dialog){   ///proposition
    std::cout<<"\nprocess rdbase is not implemented yet\n> ";
    return command_reader();
}



#include "Equation_Menu.h"
///Overridden functions:
std::string Equation_Menu::command_interpreter(std::string parent_state, Command command){///overridden, returns state
    if(command==CMDNAME)            return NAME;
    else if(command==CMDREADEQ)     return READEQ;
    else if(command==CMDNOTLOW)     return READEQ;
    else if(command==CMDFIXEQ)      return FIXEQ;
    else if(command==CMDPRINTEQ)    return PRINTEQ;
    else if(command==CMDREVEQ)      return REVEQ;
    return StateMachine::command_interpreter(parent_state,command);//check if there is possibility to use base function
}
Command Equation_Menu::run(bool show_dialog){///overridden, return value may be changed
    Command command;
    std::string state = START;
    if(show_dialog)
        std::cout<<"Equation mode. Type 'help' to learn more or input a command:\n";
    while(true){
        if(state==START)            command = stateStart(show_dialog);
        else if(state==HELP)        command = stateHelp(show_dialog);
        else if(state==NAME)        command = stateName(show_dialog);
        else if(state==READEQ)      command = stateReadEquation(show_dialog);
        else if(state==FIXEQ)       command = stateFixEquation(show_dialog);
        else if(state==PRINTEQ)     command = statePrintEquation(show_dialog);
        else if(state==REVEQ)       command = stateReverseEquation(show_dialog);
        else if(state==RETURN)      return Command(CMDSTART);
        else if(state==QUITDEF)     return command;
        else                        command = stateDefault(state,command);
        show_dialog = is_last_command();
        state = command_interpreter(START,command);
    }
    return command;
}
Command Equation_Menu::stateStart(bool show_dialog){///overridden, returns command
    if(show_dialog) std::cout<<"> ";
    return command_reader();
}
Command Equation_Menu::stateHelp(bool show_dialog){///overridden, returns command
    Command command("All");
    if(!show_dialog) command = command_reader();
    ignore_residual_strings();
    if(command==CMDNEWLINE) command = "All";
    bool othr = true;
    if(command==CMDNAME||command=="All")    {std::cout<<"\n\t"<<CMDNAME<<"\t- set name of reaction\n";othr=false;}
    if(command==CMDREADEQ||command=="All")  {std::cout<<"\t"<<CMDREADEQ<<"\t- input reaction\n";othr=false;}
    if(command==CMDFIXEQ||command=="All")   {std::cout<<"\t"<<CMDFIXEQ<<"\t- set stoichiometry and fix reaction\n";othr=false;}
    if(command==CMDPRINTEQ||command=="All") {std::cout<<"\t"<<CMDPRINTEQ<<"\t- print reaction on the screen\n";othr=false;}
    if(command==CMDREVEQ||command=="All")   {std::cout<<"\t"<<CMDREVEQ<<"\t- reverse reaction sides\n";othr=false;}
    if(command==CMDRETURN||command=="All")  {std::cout<<"\t"<<CMDRETURN<<"\t- return to main mode\n";othr=false;}
    if(othr) std::cout<<"\t'"<<command.command<<"; is not recognized as a command specific for this mode\n";
    return Command(CMDSTART);
}

bool    Equation_Menu::is_command(Command cmd){///overridden
    if(command_interpreter("not_command",cmd)=="not_command") return false;
    else return true;
}

///this machine states
Command Equation_Menu::stateName(bool show_dialog){///to finish implementation
    if(show_dialog)
        std::cout<<"Input equation's name: \n";
    Command name = command_reader();
    if(!is_command(name)) equation.set_name(name.command);
    if(name==CMDNOTLOW){
        std::cout<<"Name of equation should start with lowercase.\n";
        ignore_residual_strings();
    }
    return Command(CMDSTART);
}

Command Equation_Menu::stateReadEquation(bool show_dialog){///to finish implementation
    if(show_dialog) std::cout<<"Input chemical equation:\n> ";
    char ch = char(std::cin.peek());
    try{
        if(ch=='('||isdigit(ch)||isupper(ch))
            equation = eq_reader.read_equation(form_reader);
    }
    catch(std::exception& e){
        std::cerr<<e.what();
    }
    return Command(CMDSTART);
}
Command Equation_Menu::stateFixEquation(bool show_dialog){
    try{
        if(equation.size()>0){
            equation.fix_stoichiometry();
            if(show_dialog) {std::cout<<"\t"; equation.print_equation();}
        }
    }
    catch(std::exception& e){
        std::cerr<<e.what();
    }
    return Command(CMDSTART);
}
Command Equation_Menu::statePrintEquation(bool show_dialog){
    std::cout<<"\t";
    equation.print_equation();
    if(equation.is_stoichiometric())
        std::cout<<"\tChemical equation is stoichiometric.\n";
    else
        std::cout<<"\tChemical equation is not stoichiometric.\n";
    return Command(CMDSTART);
}
Command Equation_Menu::stateReverseEquation(bool show_dialog){
    equation.reverse_equation();
    if(show_dialog) {std::cout<<"\t"; equation.print_equation();}
    return Command(CMDSTART);
}


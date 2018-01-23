#include "EquationReader.h"
Equation                EquationReader::read_equation(FormulaReader& form_reader,std::string equation_name){
    Equation        equation_out = read_equation(form_reader);
    if(equation_out.get_name()=="")
        equation_out.set_name(equation_name);
    return equation_out;
}
Equation                EquationReader::read_equation(FormulaReader& form_reader){
    Equation    equation_out("Equation not read");

    equation_out.set_equation(read_equation_without_checks(form_reader));
    equation_out.fix_equation();
    equation_out.set_name("");

    return equation_out;
}
std::vector<Formula>    EquationReader::read_equation_without_checks(FormulaReader& form_reader){
    char                    ch;
    std::vector<Formula>    equation;
    double                  number_multiplier = -1.0;

    try{
        while(std::cin.get(ch)){
            form_reader.clear_buffer();
            if(isalnum(ch)||ch=='(') std::cin.putback(ch);
            if((ch=='\n')||(ch=='='&&number_multiplier>0)) {std::cin.putback(ch); return equation;}
            if(ch=='='&&number_multiplier<0) number_multiplier = 1.0;
            if(!isspace(ch)&&!(ch=='+')){
               equation.push_back(form_reader.read_formula());
               equation[equation.size()-1].set_number(equation[equation.size()-1].get_number()*number_multiplier);
            }
        }

        form_reader.clear_buffer();
        return equation;
    }
    catch(std::exception& e){
        std::cerr<<e.what();
        equation.clear();
        char ch;
        while(std::cin.get(ch))
            if(ch=='\n') return equation;
    }

    return equation;
}



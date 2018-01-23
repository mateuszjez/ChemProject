#ifndef EQUATIONREADER_H
#define EQUATIONREADER_H
#include "FormulaReader.h"
#include "EQUATION.H"
#include "INSPECT.H"

class EquationReader{
    public:
        EquationReader() {}
        ~EquationReader() {}
        Equation        read_equation(FormulaReader& form_reader,std::string equation_name);
        Equation        read_equation(FormulaReader& form_reader);
    private:
        std::vector<Formula>        read_equation_without_checks(FormulaReader& form_reader);
        //FormulaReader form_reader;
};

#endif // EQUATIONREADER_H

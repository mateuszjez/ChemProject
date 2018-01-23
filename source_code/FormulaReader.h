#ifndef FormulaReader_H
#define FormulaReader_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "FORMULA.H"

class FormulaReader{///This class should be treated as a stream of formulas
    public:
        FormulaReader(std::string path) {getAtomList(path);}
        FormulaReader() {}
        ~FormulaReader() {}
        void            clear_buffer() {empty_buffer = true; formula_buffer.clear_formula();}
        void            getAtomList(std::string path);  //reads atom list (only once) from file and store it in AtomList and MassList
        Formula         read_formula();                 //reads formula and store it in formula_buffer
        Formula         get_formula();
        bool            is_buffer_empty() {return empty_buffer;}
        bool            is_atom(std::string symbol);    //compares symbol with AtomList
        void            printAtomList();
    private:
        std::string     read_atom();                    //reads symbol of atom, evoked by read_element
        Element         read_element();                 //reads symbol of atom together with its index, evoked by read_formula
        Formula         read_formula_recursively();     //recursive function evoked by reads_formula
        bool            are_parentheses_balanced(std::string formula);//returns true if balanced
        bool            are_parentheses(std::string formula);//returns true when finds '('
        double          countMolarMass();
        Formula         formula_buffer;
        bool            empty_buffer = true;
        std::vector<std::string> AtomList;  //list of symbols of atoms
        std::vector<double>      MassList;  //list of molar mass of atoms
};

#endif // FormulaReader_H

#ifndef FORMULA_H
#define FORMULA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include "INSPECT.H"

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

class Element{  ///Class to store information about atoms and their number in molecule
    public:
        Element(std::string str,int index):Symbol(str),element_index(index) {}
        ~Element() {}
        std::string Symbol;
        int element_index;
};
class Formula{   ///Class to store chemical formula of molecule and information about composition its
    public:
        Formula() {}
        ~Formula() {}
        void                    add_element(Element element_in);//change Composition and modify formula
        void                    add_atoms(Element element_in);  //change Composition and do not modify formula
        std::string             get_name(unsigned i)const {if(names.size()>0&&names.size()>i) return names[i]; return "";}//return ""; should be replaced with error
        std::vector<std::string>get_names()         const {return names;}
        std::string             get_formula()       const {return formula;}
        void                    set_formula(std::string new_formula) {formula = new_formula;}
        std::vector<Element>    get_Composition()   const {return Composition;}
        unsigned                Composition_size()  const {return Composition.size();}
        double                  get_MolarMass()     const {return MolarMass;}
        void                    set_MolarMass(double new_mass) {MolarMass = new_mass;}
        double                  get_number()        const {return number;}
        void                    set_number(double new_number) {number = new_number;}
        Element                 get_Element(unsigned position)          const {return Composition[position];}
        std::string             get_Element_Symbol(unsigned position)   const {
            if(position<Composition.size())
                return Composition[position].Symbol;
            throw std::runtime_error("ERROR! Wrong position in vector.");
        }
        bool                    is_symbol(std::string symbol)           const;  //checks whether symbol exists in formula
        int                     get_Element_index(unsigned position)    const {
            if(position<Composition.size())
                return Composition[position].element_index;
            throw std::runtime_error("ERROR! Wrong position in vector.");
        }
        int                     get_Element_index(std::string symbol)   const {
            for(unsigned i = 0;i<Composition.size();i++)
                if(Composition[i].Symbol==symbol) return Composition[i].element_index;
            return 0;
        }
        void                    set_Element_index(unsigned position,int new_index){
            if(position<Composition.size()){
                Composition[position].element_index = new_index;
                return;
            }
            throw std::runtime_error("ERROR! Wrong position in vector.");
        }
        void                    clear_formula() {formula="";Composition.clear();MolarMass=0.0;number=1.0;}
        //string state_of_matter; //at standard temperature
        //double boiling_point; /
        //double heat_of_vaporisation; //at standard temperature
        void                    swap(Formula& formula_to_swap);
        double                  stoichiometric_sign() const{if(number<0)return -1; return +1;}
    private:
        std::vector<std::string>names;       //variable to store a common names for the formula
        std::string             formula;    //string representation of chemical formula
        std::vector<Element>    Composition;//list of atoms and their numbers in chemical molecule
        double                  MolarMass = 0.0;
        double                  number = 1.0;    //indicates number of molecules written before formulas in chemical equation
};
Formula        operator+(const Formula& form1,const Formula& form2);
Formula        operator+(const Formula& form1,const Element& elem); //change Composition and modify formula
Formula        operator*(const Formula& form1,const int& num);

#endif // FORMULA_H

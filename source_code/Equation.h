#ifndef EUQATION_H
#define EUQATION_H
#include <cstdlib>
#include "Lin_Eq_Lib.h"
#include "Formulas_Collection.h"
//#include <algorithm> // std::min_element
//#include <iterator>  // std::begin, std::end
#include "INSPECT.H"

class Equation : public Formulas_Collection{
    public:
        Equation() {}
        Equation(std::string name_in) {name = name_in;}
        Equation(std::string name_in,std::vector<Formula> equation_in) {name = name_in; collection = equation_in;}
        ~Equation() {}

        std::vector<Formula>    get_equation()          const {return get_collection();}
        void                    set_equation(std::vector<Formula> new_equation) {set_collection(new_equation);}
        void                    fix_equation();

        bool                    is_stoichiometric()     const;
        void                    fix_stoichiometry();
        void                    reverse_equation();

        void                    print_equation()        const;
};

#endif // EUQATION_H

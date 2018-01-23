#ifndef FORMULAS_COLLECTION_H
#define FORMULAS_COLLECTION_H
#include <cstdlib>
#include "FORMULA.H"
#include "Lin_Eq_Lib.h"
#include "INSPECT.H"

class Formulas_Collection
{
    public:
        virtual ~Formulas_Collection() = 0;

        std::string             get_name()              const  {return name;}
        void                    set_name(std::string new_name) {name = new_name;}

        unsigned                size()                  const  {return collection.size();}
    protected:
        Formulas_Collection() {}
        std::vector<Formula>    get_collection()        const  {return collection;}
        void                    set_collection(std::vector<Formula> new_coll) {collection.clear(); collection = new_coll;}

        std::vector<std::string>get_formulas()          const;
        std::vector<std::string>get_list_of_symbols()   const;
        void                    clear()                        {name.clear(); collection.clear();}

        bool                    is_in(std::string formula_or_name);
        bool                    is_in(Formula formula);
        bool                    is_similar(Formula formula);
        std::string             name;
        std::vector<Formula>    collection;

    private:
//        Formulas_Collection(const Formulas_Collection&);// in this case I cannot use this
//        Formulas_Collection& operator=(const Formulas_Collection&);
};

#endif // FORMULAS_COLLECTION_H

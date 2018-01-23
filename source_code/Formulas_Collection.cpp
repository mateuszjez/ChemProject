#include "Formulas_Collection.h"
Formulas_Collection:: ~Formulas_Collection() = default;
std::vector<std::string>    Formulas_Collection::get_formulas()        const {
    std::vector<std::string> formulas;
    for(unsigned i = 0;i<collection.size();i++)
        formulas.push_back(collection[i].get_formula());
    return formulas;
}

std::vector<std::string>    Formulas_Collection::get_list_of_symbols() const{
    std::vector<std::string>    symbols;
    for(unsigned i_form=0;i_form<collection.size();i_form++){
        std::vector<Element> Composition = collection[i_form].get_Composition();;
        for(unsigned i_symb=0;i_symb<Composition.size();i_symb++){
            if(!Lin_Eq_Lib::is_str_in_str_list(Composition[i_symb].Symbol,symbols))
                symbols.push_back(Composition[i_symb].Symbol);
        }
    }
    return symbols;
}

bool                        Formulas_Collection::is_in(std::string formula_or_name){
    Formula form;
    bool check = false;
    for(unsigned i=0;i<collection.size();i++){
        if(formula_or_name==collection[i].get_formula()){
            form = collection[i];
            check = true;
            break;
        }
    }
    if(form.get_names().size()==0) return check;
    if(!check)
        for(unsigned i=0;i<form.get_names().size();i++)
            if(formula_or_name == form.get_name(i)) return true;
    return check;
}
bool                        Formulas_Collection::is_in(Formula formula){
    Formula form;
    bool check = false;
    for(unsigned i=0;i<collection.size();i++){
        if(formula.get_formula()==collection[i].get_formula()){
            check = true;
            form = collection[i];
            break;
        }
    }
    if(form.get_names().size()==0 || formula.get_names().size()==0) return check;
    if(check)
        for(unsigned i=0;i<formula.get_names().size();i++)
            for(unsigned j=0;j<form.get_names().size();j++)
                if(formula.get_name(i) == form.get_name(j)) return true;
    return check;
}

bool                        Formulas_Collection::is_similar(Formula formula){
    for(unsigned i=0;i<collection.size();i++){
        if(formula.get_formula()==collection[i].get_formula())              return true;
        else if(formula.get_names().size()!=0 && collection[i].get_names().size()!=0){
            for(unsigned j=0;j<formula.get_names().size();j++)
                for(unsigned k=0;k<collection[i].get_names().size();k++)
                    if(formula.get_name(j) == collection[i].get_name(k))    return true;
        }
    }
    return false;
}

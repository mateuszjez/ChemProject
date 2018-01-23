#include "FORMULA.H"

void            Formula::add_element(Element element_in){//change Composition and modify formula
    formula = formula + element_in.Symbol;
    if(element_in.element_index!=1)
        formula = formula + patch::to_string(element_in.element_index);
    add_atoms(element_in);
}
void            Formula::add_atoms(Element element_in){//change Composition and do not modify formula
    for(unsigned i=0;i<Composition.size();i++)
        if(element_in.Symbol==Composition[i].Symbol){
            Composition[i].element_index += element_in.element_index;
            return;
        }
    Composition.push_back(element_in);
}
bool            Formula::is_symbol(std::string symbol) const{//checks whether symbol exists in formula
    for(unsigned i = 0; i < Composition.size(); i++)
        if(Composition[i].Symbol==symbol) return true;
    return false;
}
Formula         operator+(const Formula& form1,const Formula& form2){
    Formula form_out = form1;
    form_out.set_formula(form_out.get_formula() + form2.get_formula());
    for(unsigned i=0;i<form2.Composition_size();i++){
        form_out.add_atoms(form2.get_Element(i));
    }
    return form_out;
}
Formula         operator+(const Formula& form1,const Element& elem){//change Composition and modify formula
    Formula form_out = form1;
    form_out.add_element(elem);
    return form_out;
}
Formula         operator*(const Formula& form1,const int& num){
    Formula form_out = form1;
    if(num!=1){
        form_out.set_formula("(" + form_out.get_formula() + ")" + patch::to_string(num));
        for(unsigned i=0;i<form_out.Composition_size();i++){
            form_out.set_Element_index(i,form_out.get_Element_index(i)*num);
        }
    }
    return form_out;
}

void            Formula::swap(Formula& formula_to_swap){
    Formula temp = *this;
    *this = formula_to_swap;
    formula_to_swap = temp;
}



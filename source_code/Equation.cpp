#include "EQUATION.H"
using namespace Lin_Eq_Lib;

bool                        Equation::is_stoichiometric()   const{
    if(collection.size()==0) return false;

    std::vector<Element> elem_sum = collection[0].get_Composition();
    std::vector<std::string>  elem_symbol;
    std::vector<double>  elem_number;

    for(unsigned i=0;i<elem_sum.size();i++){
        elem_symbol.push_back(elem_sum[i].Symbol);
        elem_number.push_back(double(elem_sum[i].element_index)*collection[0].get_number());
    }

    bool is_symbol_in_elem_symbol = false;

    for(unsigned i=1;i<collection.size();i++){
        elem_sum = collection[i].get_Composition();
        for(unsigned j=0;j<elem_sum.size();j++){
            for(unsigned k=0;k<elem_symbol.size();k++){
                if(elem_sum[j].Symbol==elem_symbol[k]){
                    elem_number[k] = elem_number[k] + double(elem_sum[j].element_index)*collection[i].get_number();
                    is_symbol_in_elem_symbol = true;
                    break;
                }
            }
            if(!is_symbol_in_elem_symbol){
                elem_symbol.push_back(elem_sum[j].Symbol);
                elem_number.push_back(double(elem_sum[j].element_index*collection[i].get_number()));
            }
            is_symbol_in_elem_symbol = false;
        }
    }

    for(unsigned i=0;i<elem_number.size();i++)
        if(fabs(elem_number[i])>1e-10)return false;

    return true;
}

void                        Equation::fix_stoichiometry(){
    if(collection.size()<2) return;

    std::vector<Formula>              equation_buffer = collection;

    std::vector<std::string>          symbols = get_list_of_symbols();

    std::vector<std::vector<double> > vector_matrix = create_vector_matrix(collection,symbols);
//Inspect::insp_vector_matrix("Matrix of atoms in molecules", "fix_stoichiometry()", symbols, get_formulas(), vector_matrix);

    std::vector<double> stoichiometry;
    std::vector<unsigned> linear_independent = linear_independence(vector_matrix);
//Inspect::insp_vector("Linear independence","fix_stoichiometry()",linear_independent,Inspect::vertical);

    unsigned num_of_lin_indpndc = 0;
    for(unsigned i=0;i<linear_independent.size();i++)
        num_of_lin_indpndc += linear_independent[i];

    if(vector_matrix.size()>(num_of_lin_indpndc+1))
        throw std::runtime_error("\nERROR! Unable to calculate stoichiometry for this equation.");

    std::vector<std::vector<double> > sub_vector_matrix = fix_vector_matrix_for_stoichiometry(vector_matrix,linear_independent);

    stoichiometry = solve_linear_equation_system(sub_vector_matrix);
//Inspect::insp_vector("Initial stoichiometry","fix_stoichiometry()",get_formulas(),stoichiometry,Inspect::horizontal);

    double min_coef = Lin_Eq_Lib::min_abs_greater_than_zero(stoichiometry);
    if(min_coef==0) throw std::runtime_error("\nERROR! Division by zero!");
    for(unsigned i=0;i<stoichiometry.size();i++)
        collection[i].set_number(collection[i].stoichiometric_sign()*stoichiometry[i]/min_coef);
    fix_equation();

    if(!is_stoichiometric()){
        collection = equation_buffer;
        throw std::runtime_error("\nERROR! Unable to calculate stoichiometry for this equation.");
    }
}

void                        Equation::fix_equation(){
    if(collection.size()>0){
        std::vector<Formula> equation_fixed;

        for(unsigned i=0;i<(collection.size()-1);i++)                         ///Merge formulas if formula is repeated.
            for(unsigned j=(i+1);j<collection.size();j++)
                if(collection[i].get_formula()==collection[j].get_formula()){
                    double new_number = collection[i].get_number() + collection[j].get_number();
                    collection[i].set_number(new_number);
                    collection[j].clear_formula();
                }
        for(unsigned i=0;i<collection.size();i++)                             ///Only stoichiometric coefficient != 0 are considered.
            if(collection[i].get_formula()!=""&&collection[i].get_number()!=0)
                equation_fixed.push_back(collection[i]);

        for(unsigned i=0;i<equation_fixed.size();i++)                       ///Sets proper order of formulas in equation.
            if(equation_fixed[i].get_number()>0){
                for(unsigned j=i+1;j<equation_fixed.size();j++)
                    if(equation_fixed[j].get_number()<0){
                        equation_fixed[i].swap(equation_fixed[j]);
                        break;
                    }
            }
        collection = equation_fixed;
    }
}

void                        Equation::print_equation()      const{
    if(collection.size()==0){
        std::cout<<"Equation not read!\n";
        return;
    }

    std::cout<<"Equation "<<name<<": ";
    for(unsigned i=0;i<collection.size();i++){
        if((i+1)<collection.size()){
            if(collection[i].get_number()<0 && collection[i+1].get_number()>0){
                if(i>0) std::cout<<" + ";
                if(fabs(collection[i].get_number())!=1) std::cout<<fabs(collection[i].get_number());
                std::cout<<collection[i].get_formula()<<" = ";
                i++;
                if(fabs(collection[i].get_number())!=1) std::cout<<fabs(collection[i].get_number());
                std::cout<<collection[i].get_formula();
            }
            else{
                if(i>0) std::cout<<" + ";
                if(fabs(collection[i].get_number())!=1) std::cout<<fabs(collection[i].get_number());
                std::cout<<collection[i].get_formula();
            }
        }
        else{
            if(i>0) std::cout<<" + ";
            if(fabs(collection[i].get_number())!=1) std::cout<<fabs(collection[i].get_number());
            std::cout<<collection[i].get_formula();
        }
    }
    std::cout<<";\n";
}

void                        Equation::reverse_equation() {
    std::vector<Formula> equation_rev;
    unsigned right_side_index = 0;
    if(is_stoichiometric()){
        for(unsigned i=0;i<collection.size();i++)
            if(collection[i].get_number()>0){
                collection[i].set_number(-collection[i].get_number());
                equation_rev.push_back(collection[i]);
                if(right_side_index==0) right_side_index = i;
            }
        for(unsigned i=0;i<right_side_index;i++){
            collection[i].set_number(-collection[i].get_number());
            equation_rev.push_back(collection[i]);
        }
        collection = equation_rev;
    }
}


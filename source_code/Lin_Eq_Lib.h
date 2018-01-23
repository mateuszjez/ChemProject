#ifndef LIN_EQ_LIB_H_INCLUDED
#define LIN_EQ_LIB_H_INCLUDED
#include "FORMULA.H"
#include <cmath>
#include "INSPECT.H"
namespace Lin_Eq_Lib{ ///Linear Equation Library
    double                              min_abs_greater_than_zero(std::vector<double> dArray);
    bool                                is_str_in_str_list(std::string str,std::vector<std::string> str_list);
    std::vector<std::vector<double> >   create_vector_matrix(std::vector<Formula> equation,std::vector<std::string> symbols);
    double                              determinant(std::vector<std::vector<double> > matrix);
    std::vector<double>                 solve_linear_equation_system(std::vector<std::vector<double> > vector_matrix);
    std::vector<unsigned>               linear_independence(std::vector<std::vector<double> > vector_matrix);
    std::vector<std::vector<double> >   fix_vector_matrix_for_stoichiometry(std::vector<std::vector<double> > vector_matrix,std::vector<unsigned> linear_independent);
    void                                sort_simultaneously(std::vector<unsigned>& val2check,std::vector<unsigned>& val2follow);
}


#endif // LIN_EQ_LIB_H_INCLUDED

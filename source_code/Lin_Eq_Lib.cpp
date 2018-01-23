#include "Lin_Eq_Lib.h"

void                                show_matrix(std::vector<std::vector<double> > matrix,std::string title);

double                              Lin_Eq_Lib::min_abs_greater_than_zero(std::vector<double> dArray){ //returns dArray entry of smallest absolute value
    double min_dArray = dArray[0];
    for(unsigned i=1;i<dArray.size();i++)
        if(fabs(min_dArray)>fabs(dArray[i])&&dArray[i]!=0) min_dArray = dArray[i];
    if(min_dArray==0) throw std::runtime_error("\nERROR! All values in dArray are equal to zero.");
    return min_dArray;
}

bool                                Lin_Eq_Lib::is_str_in_str_list(std::string str,std::vector<std::string> str_list){
    for(unsigned i = 0; i < str_list.size(); i++)
        if(str_list[i]==str) return true;
    return false;
}

std::vector<std::vector<double> >   Lin_Eq_Lib::create_vector_matrix(std::vector<Formula> equation,std::vector<std::string> symbols){
    std::vector<double> vect_symbols(symbols.size(),0);
    std::vector<std::vector<double> > vector_matrix(equation.size(),vect_symbols);

    for(unsigned i_eq=0;i_eq<equation.size();i_eq++)
        for(unsigned i_s=0;i_s<symbols.size();i_s++){
            if(equation[i_eq].get_number()==0) throw std::runtime_error("ERROR! Division by zero!");
            vector_matrix[i_eq][i_s] = double(equation[i_eq].get_Element_index(symbols[i_s])) * equation[i_eq].get_number()/fabs(equation[i_eq].get_number());
        }
//Inspect::insp_vector_matrix("vector_matrix","create_vector_matrix",vector_matrix);

    return vector_matrix;
}

double                              Lin_Eq_Lib::determinant(std::vector<std::vector<double> > matrix){
//Inspect::insp_variable("matrix.size()", "LinEqLib::determinant()", matrix.size());
//Inspect::insp_variable("matrix[0].size()", "LinEqLib::determinant()", matrix[0].size());
    unsigned Msize = matrix.size();
//Inspect::insp_variable("Msize", "LinEqLib::determinant()", Msize);
    unsigned Msize2 = matrix[0].size();
//Inspect::insp_variable("Msize2", "LinEqLib::determinant()", Msize2);
    if(Msize==1)
        if(Msize==1&&Msize2==1)
            return matrix[0][0];
        else return 0;
    else if(Msize==0) return 0;     //should throw an error
    if(Msize!=Msize2) return 0;     //should throw an error
    unsigned subMsize = Msize - 1;  //submatrix size

    std::vector<double>                 mltpl_coef(subMsize,0);            //coefficients for multiplying
    std::vector<std::vector<double> >   submatrix(subMsize,mltpl_coef);    //mltpl_coef filled with 0 used to initialize submatrix

    double result = 1;
    bool row_filled_with_0 = true;

//Inspect::insp_variable("matrix[0][0]", "LinEqLib::determinant()", matrix[0][0]);
    if(matrix[0][0]==0){
//Inspect::insp_variable("case if(matrix[0][0]==0)");
        for(unsigned i=1;i<Msize;i++)
            if(matrix[i][0]!=0) {
                matrix[0].swap(matrix[i]);
                result = -result;
                row_filled_with_0 = false;
                break;
            }
    }
    else{
//Inspect::insp_variable("else case");
        row_filled_with_0 = false;
    }
//Inspect::insp_variable("row_filled_with_0", "LinEqLib::determinant()", row_filled_with_0);

    if(row_filled_with_0) return 0.0;

    if(matrix[0][0]==0) throw std::runtime_error("ERROR! Division by zero!");
    for(unsigned i=1;i<Msize;i++)
        mltpl_coef[i-1] = -matrix[0][i]/matrix[0][0];
//Inspect::insp_vector("mltp_coef", "LinEqLib::determinant",mltpl_coef,Inspect::vertical);

    for(unsigned i=0;i<subMsize;i++)
        for(unsigned j=0;j<subMsize;j++)
            submatrix[i][j] = matrix[i+1][j+1] + matrix[i+1][0]*mltpl_coef[j];

//Inspect::insp_vector_matrix("submatrix","LinEqLib::determinant",submatrix);

    return result*matrix[0][0]*determinant(submatrix);
}
std::vector<double>                 Lin_Eq_Lib::solve_linear_equation_system(std::vector<std::vector<double> > vector_matrix){
    if(vector_matrix.size()!=(vector_matrix[0].size()+1))
        throw std::runtime_error("\nERROR! Wrong vector_matrix size in solve_linear_equation_system function.");

    unsigned dimension = vector_matrix[0].size();
//Inspect::insp_variable("dimension", "LinEqLib::solve_linear_equation_system", dimension);

    std::vector<std::vector<double> > main_matrix;
    std::vector<double> right_side = vector_matrix[dimension];
    std::vector<double> results;
    double              main_determinant;

    for(unsigned i=0;i<dimension;i++){
        main_matrix.push_back(vector_matrix[i]);
        right_side[i] = -right_side[i];
    }

    main_determinant = determinant(main_matrix);
//Inspect::insp_variable("main_determinant", "LinEqLib::solve_linear_equation_system", main_determinant);
//Inspect::insp_vector_matrix("main_matrix", "LinEqLib::solve_linear_equation_system", main_matrix);

    if(main_determinant==0) throw std::runtime_error("\nERROR! Solution does not exist.");

    std::vector<std::vector<double> > auxiliary_matrix;

    for(unsigned i=0;i<dimension;i++){
        auxiliary_matrix = main_matrix;
        auxiliary_matrix[i] = right_side;
        results.push_back(determinant(auxiliary_matrix)/main_determinant);
    }
    results.push_back(1.0);
    return results;
}

std::vector<unsigned>               Lin_Eq_Lib::linear_independence(std::vector<std::vector<double> > vector_matrix){//recursive function
    unsigned Msize1 = vector_matrix.size();         ///Msize1 - number of columns in the vector_matrix
    unsigned Msize2 = vector_matrix[0].size();      ///Msize2 - number of rows in the vector_matrix
    if(Msize1==0||Msize2==0) throw std::runtime_error("\nERROR! Wrong vector_matrix size in linear_independence function.");

    std::vector<unsigned> vector_out(Msize2,0); ///vector to indicate linear independence, 1/0 - independent/dependent equation

    if(Msize2==1){                              ///if only one row passed all cells equals to zero indicates linear dependence
        for(unsigned i=0;i<Msize1;i++)
            if(vector_matrix[i][0]!=0)
                vector_out[0] = 1;
        return vector_out;
    }

    unsigned subMsize2 = 0;
    std::vector<unsigned> indexsubMsize2(Msize2,0); ///important vector for ordering and positioning of equations
    std::vector<unsigned> revindexsubMsize2;        ///important vector for ordering and positioning of equations
    for(unsigned i=0;i<Msize2;i++)
        for(unsigned j=0;j<Msize1;j++)
            if(vector_matrix[j][i]!=0){             ///all cells in row == zero indicates linear dependence
                vector_out[i] = 1;                  ///if any cell in row != 0 independence of equation is assumed
                indexsubMsize2[i] = subMsize2;      ///indexes of rows chosen to further examination of independence
                revindexsubMsize2.push_back(i);     ///indexes of chosen rows to associate results from further examination
                subMsize2++;                        ///vertical size of the matrix with chosen equations
                break;
            }
    if(subMsize2==1) return vector_out;             ///only one non_zero row indicates that this equation is independent

                                                    ///sub_vector_matrix is the matrix with chosen equations
    std::vector<std::vector<double> > sub_vector_matrix(Msize1,std::vector<double>(subMsize2,0));
    for(unsigned i=0;i<Msize2;i++)
        if(vector_out[i]!=0){
            for(unsigned j=0;j<Msize1;j++)
                sub_vector_matrix[j][indexsubMsize2[i]] = vector_matrix[j][i];
        }

    unsigned subMsize1 = Msize1 - 1;                ///sub_vector_matrix has lower number of columns
    if(subMsize1==0) return vector_out;
    if(sub_vector_matrix[0][0]==0){                 ///non zero cell must be chosen as the upper left cell for Gauss elimination
        for(unsigned i=1;i<Msize1;i++)
            if(sub_vector_matrix[i][0]!=0) {
                sub_vector_matrix[0].swap(sub_vector_matrix[i]);
                break;
            }
    }

    subMsize2--;                                    ///size of submatrix is lower by one
    std::vector<double>                 mltpl_coef(subMsize2,0);            //coefficients for multiplying
    std::vector<std::vector<double> >   submatrix(subMsize1,mltpl_coef);    //mltpl_coef filled with 0 used to initialize submatrix

    if(sub_vector_matrix[0][0]==0)  throw std::runtime_error("ERROR! Division by zero!");

    for(unsigned i=1;i<=subMsize2;i++)
        mltpl_coef[i-1] = 0.0-(sub_vector_matrix[0][i]/sub_vector_matrix[0][0]);

    for(unsigned i=0;i<subMsize2;i++)
        for(unsigned j=0;j<subMsize1;j++)
            submatrix[j][i] = sub_vector_matrix[j+1][i+1] + sub_vector_matrix[j+1][0]*mltpl_coef[i];

    std::vector<unsigned> sub_vector_out = linear_independence(submatrix);

    for(unsigned i=0;i<sub_vector_out.size();i++)
        vector_out[revindexsubMsize2[i+1]] = sub_vector_out[i];

    return vector_out;
}

std::vector<std::vector<double> >   Lin_Eq_Lib::fix_vector_matrix_for_stoichiometry(std::vector<std::vector<double> > vector_matrix,std::vector<unsigned> linear_independent){
    unsigned Msize1 = vector_matrix.size();
    unsigned Msize2 = vector_matrix[0].size();

    if(Msize1==0||Msize2==0)
        throw std::runtime_error("\nERROR! Wrong vector_matrix size in fix_vector_matrix_for_stoichiometry function.");

    std::vector<std::vector<double> >   vector_matrix_out(Msize1,std::vector<double>(Msize1-1,0));
    std::vector<unsigned>               independent_index;

    for(unsigned i=0;i<Msize2;i++)
        if(linear_independent[i]!=0)
            independent_index.push_back(i);

    if(independent_index.size()<(Msize1-1))
        throw std::runtime_error("\nERROR! Something wrong with independent_index size in fix_vector_matrix_for_stoichiometry function.");

    for(unsigned i=0;i<Msize1;i++)
        for(unsigned j=0;j<(Msize1-1);j++)
            vector_matrix_out[i][j] = vector_matrix[i][independent_index[j]];
//Inspect::insp_vector("independent_index","LinEqLib::fix_vector_matrix_for_stoichiometry",independent_index,Inspect::vertical);
//Inspect::insp_vector_matrix("vector_matrix_out","LinEqLib::fix_vector_matrix_for_stoichiometry",vector_matrix_out);

    return vector_matrix_out;
}
void                                Lin_Eq_Lib::sort_simultaneously(std::vector<unsigned>& val2check,std::vector<unsigned>& val2follow){
    bool issorted = true;
    for(unsigned i=0;i<val2check.size()-1;i++){
        if(val2check[i]>val2check[i+1]){
            unsigned tempcheck  = val2check[i];
            unsigned tempfollow = val2follow[i];
            val2check[i]        = val2check[i+1];
            val2follow[i]       = val2follow[i+1];
            val2check[i+1]      = tempcheck;
            val2follow[i+1]     = tempfollow;
            issorted = false;
        }
    }
    if(!issorted) sort_simultaneously(val2check,val2follow);
}


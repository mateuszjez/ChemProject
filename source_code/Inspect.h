#ifndef INSPECT_H_INCLUDED
#define INSPECT_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

namespace Inspect{
    enum Orient{
        horizontal  = 1, vertical
    };
    inline void insp_variable(std::string variable)    {std::cout<<"\n"<<variable<<"\n";}
    inline void insp_variable(double variable)         {std::cout<<"\n"<<variable<<"\n";}
    inline void insp_variable(int variable)            {std::cout<<"\n"<<variable<<"\n";}
    inline void insp_variable(unsigned variable)       {std::cout<<"\n"<<variable<<"\n";}
    inline void insp_variable(bool variable)           {std::cout<<"\n"<<variable<<"\n";}

    inline void insp_variable(std::string what,std::string variable)   {std::cout<<"\n"<<what<<" = "<<variable<<"\n";}
    inline void insp_variable(std::string what,double variable)        {std::cout<<"\n"<<what<<" = "<<variable<<"\n";}
    inline void insp_variable(std::string what,int variable)           {std::cout<<"\n"<<what<<" = "<<variable<<"\n";}
    inline void insp_variable(std::string what,unsigned variable)      {std::cout<<"\n"<<what<<" = "<<variable<<"\n";}
    inline void insp_variable(std::string what,bool variable)          {std::cout<<"\n"<<what<<" = "<<variable<<"\n";}

    inline void insp_variable(std::string what,std::string where,std::string variable)   {std::cout<<"\nIn "<<where<<":\n"<<what<<" = "<<variable<<"\n";}
    inline void insp_variable(std::string what,std::string where,double variable)        {std::cout<<"\nIn "<<where<<":\n"<<what<<" = "<<variable<<"\n";}
    inline void insp_variable(std::string what,std::string where,int variable)           {std::cout<<"\nIn "<<where<<":\n"<<what<<" = "<<variable<<"\n";}
    inline void insp_variable(std::string what,std::string where,unsigned variable)      {std::cout<<"\nIn "<<where<<":\n"<<what<<" = "<<variable<<"\n";}
    inline void insp_variable(std::string what,std::string where,bool variable)          {std::cout<<"\nIn "<<where<<":\n"<<what<<" = "<<variable<<"\n";}

    void insp_vector_matrix(std::string what,std::string where, std::vector<std::vector<double> > matrix);
    void insp_vector_matrix(std::string what,std::string where,std::vector<std::string> columnlabels, std::vector<std::vector<double> > matrix);
    void insp_vector_matrix(std::vector<std::string> columnlabels, std::vector<std::vector<double> > matrix);
    void insp_vector_matrix(std::string what,std::string where,std::vector<std::string> rowlabels, std::vector<std::string> columnlabels, std::vector<std::vector<double> > matrix);
    void insp_vector_matrix(std::vector<std::string> rowlabels, std::vector<std::string> columnlabels, std::vector<std::vector<double> > matrix);
    void insp_vector_matrix(std::vector<std::vector<double> > matrix);

    void insp_vector(std::string what,std::string where, std::vector<double> vector_in, Orient orient);
    void insp_vector(std::string what,std::string where, std::vector<unsigned> vector_in, Orient orient);
    void insp_vector(std::string what,std::string where, std::vector<std::string> label, std::vector<double> vector_in, Orient orient);
    void insp_vector(std::vector<std::string> label, std::vector<double> vector_in, Orient orient);
    void insp_vector(std::vector<double> vector_in, Orient orient);
    void insp_vector(std::vector<unsigned> vector_in, Orient orient);
}

inline void Inspect::insp_vector_matrix(std::string what,std::string where, std::vector<std::vector<double> > matrix){
    std::cout<<"\n"<<what<<" in "<<where;
    insp_vector_matrix(matrix);
}
inline void Inspect::insp_vector_matrix(std::string what,std::string where, std::vector<std::string> columnlabels, std::vector<std::vector<double> > matrix){
    std::cout<<"\n"<<what<<" in "<<where;
    insp_vector_matrix(columnlabels,matrix);
}
inline void Inspect::insp_vector_matrix(std::string what,std::string where, std::vector<std::string> rowlabels, std::vector<std::string> columnlabels, std::vector<std::vector<double> > matrix){
    std::cout<<"\n"<<what<<" in "<<where;
    insp_vector_matrix(rowlabels,columnlabels,matrix);
}
inline void Inspect::insp_vector_matrix(std::vector<std::string> columnlabels, std::vector<std::vector<double> > matrix){
    if(columnlabels.size()!=matrix.size()) throw std::runtime_error("ERROR! Wrong size of columnlabels!");
    std::cout<<"\n";
    for(unsigned i = 0;i<columnlabels.size();i++)
        std::cout<<"\t"<<columnlabels[i];
    insp_vector_matrix(matrix);
}
inline void Inspect::insp_vector_matrix(std::vector<std::string> rowlabels, std::vector<std::string> columnlabels, std::vector<std::vector<double> > matrix){
    if(columnlabels.size()!=matrix.size()) throw std::runtime_error("ERROR! Wrong size of columnlabels!");
    std::cout<<"\n";
    for(unsigned i = 0;i<columnlabels.size();i++)
        std::cout<<"\t"<<columnlabels[i];
    if(rowlabels.size()!=matrix[0].size()) throw std::runtime_error("ERROR! Wrong size of rowlabels!");
    for(unsigned j=0;j<matrix[0].size();j++){
        std::cout<<"\n"<<rowlabels[j];
        for(unsigned i=0;i<matrix.size();i++){
            std::cout<<"\t"<<matrix[i][j];
        }
    }
}
inline void Inspect::insp_vector_matrix(std::vector<std::vector<double> > matrix){
    for(unsigned j=0;j<matrix[0].size();j++){
        std::cout<<"\n";
        for(unsigned i=0;i<matrix.size();i++){
            std::cout<<"\t"<<matrix[i][j];
        }
    }
}

inline void Inspect::insp_vector(std::string what, std::string where, std::vector<double> vector_in, Orient orient){
    std::cout<<"\n"<<what<<" in "<<where;
    insp_vector(vector_in,orient);
}
inline void Inspect::insp_vector(std::string what, std::string where, std::vector<unsigned> vector_in, Orient orient){
    std::cout<<"\n"<<what<<" in "<<where;
    insp_vector(vector_in,orient);
}
inline void Inspect::insp_vector(std::string what, std::string where, std::vector<std::string> label, std::vector<double> vector_in, Orient orient){
    std::cout<<"\n"<<what<<" in "<<where;
    insp_vector(label,vector_in,orient);
}
inline void Inspect::insp_vector(std::vector<std::string> label, std::vector<double> vector_in, Orient orient){
    if(label.size()!=vector_in.size())  throw std::runtime_error("ERROR! Wrong size of labels!");
    if(orient==horizontal){
        std::cout<<"\n";
        for(unsigned i = 0; i<label.size();i++)
            std::cout<<"\t"<<label[i];
        std::cout<<"\n";
        for(unsigned i = 0; i<vector_in.size();i++)
            std::cout<<"\t"<<vector_in[i];
    }
    else if(orient==vertical){
        for(unsigned i = 0; i<label.size();i++)
            std::cout<<"\n"<<label[i]<<"\t"<<vector_in[i];
    }
}
inline void Inspect::insp_vector(std::vector<double> vector_in, Orient orient){
    if(orient==horizontal){
        std::cout<<"\n";
        for(unsigned i = 0; i<vector_in.size();i++)
            std::cout<<"\t"<<vector_in[i];
    }
    else if(orient==vertical){
        for(unsigned i = 0; i<vector_in.size();i++)
            std::cout<<"\n\t"<<vector_in[i];
    }
}
inline void Inspect::insp_vector(std::vector<unsigned> vector_in, Orient orient){
    if(orient==horizontal){
        std::cout<<"\n";
        for(unsigned i = 0; i<vector_in.size();i++)
            std::cout<<"\t"<<vector_in[i];
    }
    else if(orient==vertical){
        for(unsigned i = 0; i<vector_in.size();i++)
            std::cout<<"\n\t"<<vector_in[i];
    }
}
#endif // INSPECT_H_INCLUDED

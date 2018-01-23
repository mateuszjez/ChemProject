#include "FormulaReader.h"

void            FormulaReader::getAtomList(std::string path){//plus MassList
    if(AtomList.size()>0) throw std::runtime_error("\nERROR! Empty vector of AtomList excepted.");

    std::string     symbol;
    double          molar_mass;

    std::ifstream in_stream(path.c_str());

    if (!in_stream) throw std::runtime_error("\nERROR! Cannot open AtomList.txt");

    while(in_stream>>symbol>>molar_mass){
            AtomList.push_back(symbol);
            MassList.push_back(molar_mass);
    }

    return;
}
void            FormulaReader::printAtomList(){
    if(AtomList.size()>0){
        for(unsigned i=0;i<AtomList.size();i++){
            std::cout<<AtomList[i]<<"\tM = ";
            std::cout<<MassList[i]<<";\t";
            if(((i+1)%4)==0) std::cout<<"\n";
        }
        return;
    }
    else std::cout<<"Get AtomList first";
    return;
}
std::string     FormulaReader::read_atom(){
    char            ch1,ch2;
    std::string     symbol = "";

    std::cin.get(ch1);
    if(isupper(ch1)){
        symbol = symbol + ch1;
        std::cin.get(ch2);
        if(islower(ch2)){
            symbol = symbol + ch2;
            if(is_atom(symbol))
                return symbol;
        }
        else{
            std::cin.putback(ch2);
            if(is_atom(symbol))
                return symbol;
        }
    }

    throw std::runtime_error("\nERROR! Atom symbol expected.");
}
Element         FormulaReader::read_element(){
    Element   element(read_atom(),1.0);
    char      ch;

    ch = char(std::cin.peek());
    if(!std::isdigit(ch)) return element;

    std::cin>>element.element_index;
    return element;
}
bool            FormulaReader::is_atom(std::string str){
    for(unsigned i=0;i<AtomList.size();i++)
        if(str==AtomList[i]) return true;
    return false;
}
Formula         FormulaReader::read_formula(){
    if(!empty_buffer) throw std::runtime_error("\nERROR! Clear buffer before reading next formula.");

    char     ch;
    double number = 1;

    std::cin.get(ch);
    while(std::isspace(ch)&&ch!='\n') std::cin.get(ch);
    std::cin.putback(ch);
    if(ch=='\n') throw std::runtime_error("\nERROR! Expected alphanumeric or '(' .");

    if(std::isdigit(ch)) std::cin>> number;

    ch = char(std::cin.peek());
    if(!std::isalnum(ch)&&ch!='(') throw std::runtime_error("\nERROR! Expected alphanumeric or '(' .");

    read_formula_recursively();

    ch = char(std::cin.peek());
    if(!are_parentheses(formula_buffer.get_formula())&&ch==')')
        throw std::runtime_error("\nERROR! Parentheses are not balanced.");

    formula_buffer.set_number(number);
    formula_buffer.set_MolarMass(countMolarMass());
    empty_buffer = false;

    return get_formula();
}
Formula         FormulaReader::get_formula(){
    if(!empty_buffer)return formula_buffer;
    throw std::runtime_error("\nERROR! formula_buffer is empty.");
}
Formula         FormulaReader::read_formula_recursively(){
    char     ch;
    Formula  formula;

    while(std::cin.get(ch)){
        if(ch=='('){
            ch = char(std::cin.peek());
            if(ch==')') throw std::runtime_error("\nERROR! Expected content before ')'.");

            Formula     inside_formula = read_formula_recursively();

            std::cin.get(ch);
            if(ch!=')') {std::cin.putback(ch); throw std::runtime_error("\nERROR! Expected ')'.");}

            ch = char(std::cin.peek());
            if(!std::isdigit(ch)) throw std::runtime_error("\nERROR! Expected number index after ')'.");

            int       index = -1;
            std::cin>>index;
            formula = formula + inside_formula*index;
        }
        else{
            if(isalpha(ch)){
                std::cin.putback(ch);
                formula = formula + read_element();
            }
            else if(ch==')'){
                std::cin.putback(ch);
                return formula;
            }
            else if(std::isspace(ch)||ch=='='||ch=='+'){
                std::cin.putback(ch);
                formula_buffer = formula;
                return formula;
            }
            else throw std::runtime_error("ERROR! Expected symbol, white space, '(' or ')'.");
        }
    }

    throw std::runtime_error("ERROR! 'return' not applied in read_formula().");
}
bool            FormulaReader::are_parentheses_balanced(std::string formula) {
    int par_num = 0;
    for(unsigned i=0;i<formula.size();i++){
        if(formula[i]=='(') par_num+=1;
        if(formula[i]==')') par_num-=1;
    }
    return par_num==0;
}
bool            FormulaReader::are_parentheses(std::string formula) {
    for(unsigned i=0;i<formula.size();i++){
        if(formula[i]=='(') return true;
    }
    return false;
}
double          FormulaReader::countMolarMass(){
    double MolarMass = 0;
    for(unsigned i=0;i<formula_buffer.Composition_size();i++)
        for(unsigned j=0;j<MassList.size();j++){
            if(formula_buffer.get_Element_Symbol(i)==AtomList[j]){
                MolarMass += MassList[j]*(double(formula_buffer.get_Element_index(i)));
                break;
            }
        }
    return MolarMass;
}


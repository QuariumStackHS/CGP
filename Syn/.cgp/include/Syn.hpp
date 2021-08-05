#include <vector>
#include <string>
#include <cstdint>
#include <map>
#include <iostream>
using namespace std;
class Value{
public:
    Value(int);
    Value(float);
    Value(string);
    Value(int,string);
    Value(float,string);
    Value(string,string);
int _I;
float _F;
string _S;
};
class Synth_instruction_Set{
public:
    Synth_instruction_Set(string k){
        for(int i=0;i<k.size();i++){
            this->CodeSegm[i]=k[i];
        }
        this->P_M=k.size()-1;
    }
    int32_t P;
    int32_t P_M;
    char CodeSegm[INT_LEAST16_MAX]={0}; 
};
class Keyword{
    public:
        virtual Value* operator()(Synth_instruction_Set*)=0;
        string Key="";
};
class Synth{
    public:
        Synth_instruction_Set*SIS;
        std::map<std::string,Keyword*> Keys=map<std::string,Keyword*>();
        Synth operator+(Keyword*Kly);
        Synth operator[](Synth_instruction_Set*KLy);
        Synth operator()();
        Synth(string Filename);

};

// "func" name (typename Tname,...){}
// Type varname = Value
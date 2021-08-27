#ifndef SynD
#define SynD
#include <vector>
#include <string>
#include <cstdint>
#include <map>
#include <iostream>
using namespace std;
//higher divider = less latency in initialisation but less space to store code segm ; lower divider = more lag in the initialisation but more space to store code segm
#define CodeSegmDivider 20
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
    Synth_instruction_Set(string k);
    std::map<std::string,Value*> DataSegm=map<std::string,Value*>();
    int32_t P;
    int32_t P_M;
    char CodeSegm[INT_LEAST32_MAX/CodeSegmDivider]={0}; 
};
class Type_Rule{
    public:
        Type_Rule(string,string);
        string Typename;
        string name;
};
class Syn_Proc{
    public:
        Syn_Proc(string name,string returntype);
        Syn_Proc operator+(Type_Rule*);
        string name;
        string return_type;
        vector<Type_Rule*>T_R;
        int SYN_P;
};
/*Syn_Proc::Syn_Proc(string a,string b){
    this->name=a;
    this->return_type=b;

}*/
class Synth{
    public:
        class Keyword{
        public:
            virtual Value* operator()(Synth*)=0;
            virtual Value* operator+(Keyword*)=0;
            string Key="";
    };
        Synth_instruction_Set*SIS;
        std::map<std::string,Keyword*> Keys=map<std::string,Keyword*>();
        std::map<std::string,Syn_Proc*> Procedures=map<std::string,Syn_Proc*>();
        Synth operator+(Keyword*Kly);
        Synth operator+(Syn_Proc*Kly);
        Synth operator[](Synth_instruction_Set*KLy);
        Synth operator()();
        Synth(string Filename);

};

// "func" name (typename Tname,...){}
// Type varname = Value
#endif
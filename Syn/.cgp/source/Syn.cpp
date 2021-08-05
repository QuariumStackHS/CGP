#include <Syn.hpp>

Synth Synth::operator+(Keyword *Kly)
{
    this->Keys[Kly->Key] = Kly;
    return *this;
}
Synth Synth::operator[](Synth_instruction_Set *KLy)
{
    this->SIS = KLy;
    return *this;
}
Synth Synth::operator()(){
            string buff="";
            Keyword*Temp=nullptr;
            cout<<"():"<<this->SIS->CodeSegm<<endl;
            for(int i=0; i<this->SIS->P_M;i++){
                buff.push_back(this->SIS->CodeSegm[i]);
                Temp=Keys[buff];
                if(Temp!=nullptr){
                    Temp->operator()(this->SIS);
                    buff="";
                }else
                    
                    cout<<buff<<endl;
                
                
            }
            return *this;
        }
        Synth::Synth(string Filename){

        }
class IF : public virtual Keyword
{
public:
    IF(string k)
    {
        this->Key = k;
    }
    virtual Value *operator()(Synth_instruction_Set *)
    {
        cout << "if (Match)" << endl;
    }
};

class This : public virtual Keyword
{
public:
    This(string k)
    {
        this->Key = k;
    }
    virtual Value *operator()(Synth_instruction_Set *)
    {
        cout << "this (Match)" << endl;
    }
};
int main(int argc, char **argv)
{

    Synth Syn("Test.syn");
    IF *_IF = new IF("if ");
    This *_This = new This("this ");

    Synth_instruction_Set *I = new Synth_instruction_Set("if this is");
    (Syn + _IF);
    Syn + _This;
    cout << Syn.Keys.size() << endl;
    Syn[I];

    Syn();
}
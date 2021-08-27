#include <Syn.hpp>

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while (pos != std::string::npos)
    {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();
}
Value* Resolve_Parentesis(Synth_instruction_Set *Pers){
    
    int is_Solve=0;
    int Parents_Level=0;
    while(is_Solve==0){
        if(Pers->CodeSegm[Pers->P]=='(')
        Parents_Level++;
        if(Pers->CodeSegm[Pers->P]==')')
        Parents_Level--;
        Pers->P++;
    }
    cout<<Pers->CodeSegm[Pers->P]<<endl;
}
string Get_Until_And_Skip_Space(Synth_instruction_Set *Pers, char kl)
{
    char i = -1;
    string name = "";
    while (i != 0)
    {
        i = Pers->CodeSegm[Pers->P++];
        if (i != kl)
        {
            if (i != ' ')
            {
                name += i;
            }
        }
        else
        {
            i = 0;
        }
    }

    return name;
}
class FUNC : public virtual Synth::Keyword
{
public:
    FUNC(string k)
    {
        this->Key = k;
    }
    virtual Value *operator()(Synth *Pdp)
    {
        string FuncName = Get_Until_And_Skip_Space(Pdp->SIS, '(');
        string types = Get_Until_And_Skip_Space(Pdp->SIS, ')');
        string returnType = Get_Until_And_Skip_Space(Pdp->SIS, '{');

        //cout << "Func:" << FuncName << " T:" << types << returnType << endl;
        Syn_Proc *NewDef = new Syn_Proc(FuncName, returnType);
        vector<string> klpd;
        vector<string> TRs;
        split(types, klpd, ',');
        //cout<<klpd[klpd.size()-1]<<endl;

        for (int j = 0; j < klpd.size(); j++)
        {
            //if (strcmp(klpd[j].c_str(), "") != 0)
            //{
            split(klpd[j], TRs, ':');
            //out <<TRs[0]<< TRs[1] << endl;
            Type_Rule *jksl = new Type_Rule(TRs[0], TRs[1]);
            NewDef->T_R.push_back(jksl);
            //cout<<j<<endl;
            //}
        }
        cout << "Func:" << FuncName << " T:" << NewDef->T_R.size() << endl;

        Pdp->Procedures[FuncName] = NewDef;
        
        // NewDef->operator+()
    }
    virtual Value *operator+(Keyword *){};
};
Type_Rule::Type_Rule(string a, string b)
{
    this->name = a;
    this->Typename = b;
}
class INT : public virtual Synth::Keyword
{
public:
    INT(string k)
    {
        this->Key = k;
    }
    virtual Value *operator()(Synth *)
    {
        cout << "this (Match)" << endl;
    }
    virtual Value *operator+(Keyword *){};
};
class Defined_Func : public virtual Synth::Keyword
{
public:
    Defined_Func(string k)
    {
        this->Key = k;
    }
    virtual Value *operator()(Synth *Syn)
    {
        Syn->SIS->P = Syn->Procedures[this->Key]->SYN_P;
        cout << "this (Match)" << endl;
    }
    virtual Value *operator+(Keyword *){};
};
class print : public virtual Synth::Keyword
{
public:
    print(string k)
    {
        this->Key = k;
    }
    virtual Value *operator()(Synth *Pdp)
    {
        cout<<"print"<<endl;
        Resolve_Parentesis(Pdp->SIS);
    }
    virtual Value *operator+(Keyword *){};
};
Syn_Proc::Syn_Proc(string vname, string returntype)
{
    this->name = vname;
    this->return_type = returntype;
}
Syn_Proc Syn_Proc::operator+(Type_Rule *k)
{
    this->T_R.push_back(k);
}
Synth Synth::operator+(Keyword *Kly)
{
    this->Keys[Kly->Key] = Kly;
    return *this;
}
Synth Synth::operator+(Syn_Proc *Kly)
{
    this->Procedures[Kly->name] = Kly;
    return *this;
}
Synth Synth::operator[](Synth_instruction_Set *KLy)
{
    this->SIS = KLy;
    return *this;
}
Synth_instruction_Set::Synth_instruction_Set(string k)
{
    for (int i = 0; i < k.size(); i++)
    {
        this->CodeSegm[i] = k[i];
    }
    this->P_M = k.size() - 1;
}
Synth Synth::operator()()
{
    string buff = "";
    Keyword *Temp = nullptr;
    cout << "():" << this->SIS->CodeSegm << endl;
    for (int i = 0; i < this->SIS->P_M; i++)
    {
        this->SIS->P = i;
        //cout<<(int)this->SIS->CodeSegm[i]<<endl;
        if((this->SIS->CodeSegm[i]!='\n'))
        buff.push_back(this->SIS->CodeSegm[i]);
        Temp = Keys[buff];
        if (Temp != nullptr)
        {
            Temp->operator()(this);
            i = this->SIS->P;
            buff = "";
        }
        else{

        }

            //cout << buff << endl;
    }
    return *this;
}
Synth::Synth(string Filename)
{
}

//virtual FUNC::Value *operator+(Keyword *) = 0;

//virtual Value *operator+(Keyword *) = 0;

int main(int argc, char **argv)
{

    Synth Syn("Test.syn");

    Synth_instruction_Set *I = new Synth_instruction_Set("func main(int:argc, char**:argv)int{\nprint(argv[0])\n}E");
    FUNC *_IF = new FUNC("func ");
    INT *_This = new INT("int ");
    print*_PRint=new print("print");
    Syn + _IF;
    Syn + _This;
    Syn + _PRint;
    //cout << Syn.Keys.size() << endl;
    Syn[I];

    Syn();
}
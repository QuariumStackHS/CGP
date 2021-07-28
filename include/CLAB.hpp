#ifndef CLAB_H
#define CLAB_H

#include <vector>
#include <string>
#include <iostream>
#include <TUI.hpp>

using namespace std;
struct Deskrp{
    View*V=new View();
    int y;
};
template <class WildCard>
class CLAB
{
private:
    struct CallableObj
    {
        void *(*Taddr)(char **, int, WildCard);
        string Name;
        string Desk;
        WildCard wc;
    };
    vector<CallableObj> Switchs;
    /* data */
public:
    CLAB();
    void add_Callable(void *(Taddr)(char **, int, WildCard), string, string, WildCard);
    void run(string, char **, int);
    Deskrp* show_desk(Deskrp* Kp);

    WildCard get_Callable(void *(*Taddr)(char **, int, WildCard));
    WildCard get_Callable(string);
};
class EArg
{
public:
        string _Right;
        string _Left;

        EArg(string R, string L);
};
EArg *Get_arg(char **argb, int argc, string k);
void show_Vec(Deskrp *K){
MasterView* mf=new MasterView(MaxX,MaxY);
mf->addView(K->V);
K->V->render();
mf->clear();
mf->Render();

mf->Display();
}

template <class WildCard>
Deskrp *CLAB<WildCard>::show_desk(Deskrp *Kp)
{
    //cout<<"etrn"<<endl;
    //Deskrp K;
    //MasterView *MF=new MasterView(MaxX,MaxY);
    for (int i = 0; i < this->Switchs.size(); i++){
        //cout<<this->Switchs[i].Name<<endl;
        Kp->V->add_Horizon(to_string(Kp->y),Kp->y,0);
        Kp->V->add_Horizon(GREEN+this->Switchs[i].Name,Kp->y,3);
        Kp->V->add_Horizon(BLUE+this->Switchs[i].Desk+RESET,Kp->y,23);
        Kp->y++;
    }
    //MF->clear();
    //Kp->V->render();
    //MF->Render();
    //MF->Display();
    //delete MF;
    return Kp;
}
template <class WildCard>
void CLAB<WildCard>::add_Callable(void *(Taddr)(char **, int, WildCard), string name, string desk, WildCard wcs)
{
    CallableObj NewObj;
    NewObj.Taddr = Taddr;
    NewObj.Name = name;
    NewObj.Desk = desk;
    NewObj.wc = wcs;
    this->Switchs.push_back(NewObj);
}
template <class WildCard>
void CLAB<WildCard>::run(string name, char **args, int argc)
{
    //cout<<name<<endl;
    for (int i = 0; i < this->Switchs.size(); i++)
    {
        //cout<<Switchs[i].Name<<endl;
        if (strcmp(this->Switchs[i].Name.c_str(), name.c_str()) == 0)
        {

            this->Switchs[i].Taddr(args, argc, this->Switchs[i].wc);
        }
    }
}
template <class WildCard>
CLAB<WildCard>::CLAB()
{
}
#endif
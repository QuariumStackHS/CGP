#include <TUI.hpp>
template <class WildCard>
Deskrp *CLAB<WildCard>::show_desk(Deskrp *Kp)
{
    //cout<<"etrn"<<endl;
    //Deskrp K;
    //MasterView *MF=new MasterView(MaxX,MaxY);
    for (int i = 0; i < this->Switchs.size(); i++)
    {
        //cout<<this->Switchs[i].Name<<endl;
        Kp->V->add_Horizon(to_string(Kp->y), Kp->y, 0);
        Kp->V->add_Horizon(GREEN + this->Switchs[i].Name, Kp->y, 3);
        Kp->V->add_Horizon(BLUE + this->Switchs[i].Desk + RESET, Kp->y, 23);
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
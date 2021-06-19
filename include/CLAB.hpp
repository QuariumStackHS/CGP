#ifndef CLAB_H
#define CLAB_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;


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

    WildCard get_Callable(void *(*Taddr)(char **, int, WildCard));
    WildCard get_Callable(string);
};


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
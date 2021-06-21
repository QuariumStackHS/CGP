#include<iostream>
#include <TUI.hpp>
#include <cstring>
#include <Keys.h>
#include<vector>
using namespace std;
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
inline bool exists(const std::string &name)
{
        if (FILE *file = fopen(name.c_str(), "r"))
        {
                fclose(file);
                return true;
        }
        else
        {
                return false;
        }
}
int main(){
    MasterView *MF=new MasterView(MaxX,MaxY);
    View *Legend = new View();
    string oldins="";
    if(exists("APath")){
        ifstream in("APath",ios::out);
        
        in>>oldins;
        Legend->add_Horizon(oldins,7,2);
    }
    MF->addView(Legend);
    Legend->add_Horizon("| W : ↑ | A : ← | S : ↓ | D : → | Enter : Install | \\ : Back ", 25, 5);
    dropdownlist*Paths=new dropdownlist(2,2);
    vector<string>PATHS;

    split(getenv("PATH"),PATHS,':');

    //cout<<
    for(int i=0;i<PATHS.size();i++){
        string key=PATHS[i];
        if(PATHS[i].size()>=32){
            int fg=32-PATHS[i].size();
            //cout<<fg<<endl;
            PATHS[i].erase(PATHS[i].begin(),PATHS[i].begin()-fg);
            string tempp=((string)YELLOW)+"._"+RESET;
            PATHS[i]=tempp.append(PATHS[i]);
            //cout<<"Shrink"<<endl;
        }
        //cout<<PATHS[i]<<endl;
        MSTS*JSS=new MSTS(key,PATHS[i],"");
        Paths->add_MSTS(JSS,i);
    }
    if(strcmp(oldins.c_str(),"")!=0){
        for(int i=0;i<Paths->EA.size();i++){
            //cout<<oldins<<endl;
            if(strcmp((Paths->EA[i]->_Key+'/').c_str(),oldins.c_str())==0){
                //cout<<i;
                Paths->current_index=i;
            }
        }
    }
    system("stty raw");
MF->addView(Paths);
Paths->Key="install CGP : ";
Paths->Alias="none";

    char ch;
    while (true){
    Paths->clear();
    Paths->render();

        MF->clear();
            MF->Render();
            MF->Display();
        ch=getchar();
        if((ch==Right)&&(Paths->EA.size()-1>Paths->current_index))
            Paths->current_index++;
        else if ((ch==Left)&&(0<Paths->current_index))
        {
            Paths->current_index--;
        }
        else if(ch==13){
            if(Paths->EA[Paths->current_index]->_Key[Paths->EA[Paths->current_index]->_Key.size()-1]!='/')
                Paths->EA[Paths->current_index]->_Key+='/';
            string cmd="sh compile.sh ; sudo cp .cgp/Bin/cgp "+Paths->EA[Paths->current_index]->_Key+"cgp";
            system(cmd.c_str());
            string cmdc="sudo cp .cgp/Bin/AES_Lib.so "+Paths->EA[Paths->current_index]->_Key+"AES_Lib.so";
            system(cmdc.c_str());
            cout<<"Installed cgp to: "<<Paths->EA[Paths->current_index]->_Key<<endl;
            ofstream i("APath",ios::out);
            i<<Paths->EA[Paths->current_index]->_Key<<endl;
            ofstream j("./include/USR.h",ios::out);

            j<<"#define CGP_BIN \""<<Paths->EA[Paths->current_index]->_Key<<"\"";
            j.close();
            i.close();

            system("stty cooked");
            exit(0);
        }
        
    }
    //cout<<Paths->EA[2]->_Value.size()<<endl;



}
#include <iostream>
#include <fstream>
using namespace std;
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
int main()
{
    string oldins;
    if (exists("APath"))
    {
        ifstream in("APath", ios::out);

        in >> oldins;
        //Legend->add_Horizon(oldins,7,2);
    }
    else{
        cout<<"Cant find previous installation Path exiting"<<endl;exit(0);
    }
    string cmd="cgp this --build ; sudo cp .cgp/Bin/cgp "+oldins+"cgp";
            system(cmd.c_str());
            //string cmdc="sudo cp .cgp/Bin/AES_Lib.so "+oldins+"AES_Lib.so";
            //system(cmdc.c_str());
            cout<<"Updated cgp at: "<<oldins<<endl;
            ofstream i("APath",ios::out);
            i<<oldins<<endl;
            i.close();
}
#include <cstring>
#include <map>
#include <iostream>
#include <string>
using namespace std;

class Keywords{
    public:
    struct keyword{
        string Key;
        string Value;
    };
    Keywords(){

    }
    map<string,keyword>Keys;
    void push_back(keyword k){
        this->Keys[k.Key]=k;
    }
    string Replace(string rf){
        bool iswTB=0;
        string buffer="";
        for(int i=0;i<rf.size();i++){
            if((rf[i]=='$')&&(i+1<rf.size())&&(rf[i+1]=='{')){
                iswTB=1;
                i+=2;
            }
            else if(rf[i]=='}'){

            }
            else
            buffer+=rf[i];
        }
        return buffer;
    }
};
Keywords::keyword Keyword(string key,string value){
    struct Keywords::keyword JK;
    JK.Key=key;
    JK.Value=value;
    return JK;
}
#ifndef main
int main(){
    Keywords K=Keywords();
    cout<<K.Replace("${null}")<<endl;
}
#endif
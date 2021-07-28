#include "include/Lib.hpp"
namespace Test{
 Tester::TestNames::TestNames(Wrap w,string s){
     this->Func=w;
     this->name=s;

 }
 Tester::Tester(){

 }
 void *Tester::_Wrap(Wrap w,string s){
this->TSN.push_back(new TestNames(w,s));
 }
 int Tester::Launch(string g,char**ix,int x){
     int ret=-1;
     for(int i=0;i<this->TSN.size();i++){
         if(strcmp(g.c_str(),this->TSN[i]->name.c_str())==0){
             ret=this->TSN[i]->Func(ix,x);
         }
         
     }
     return ret;
 }





};
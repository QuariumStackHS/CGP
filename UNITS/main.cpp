#include <Lib.hpp>
#include "Headers/Main/Main.hpp"
#include <iostream>
using namespace std;
using namespace Test;

int test(char** argv,int argc ){
for(int i=0;i<argc;i++){
    cout<<argv[i]<<endl;
}
}

int main(int a,char**i){
Tester*tester=new Tester();
tester->_Wrap((Wrap)&test,"test1");
tester->Launch("test1",i,a);
}
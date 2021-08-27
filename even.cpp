#include <fstream>
#include <iostream>
using namespace std;
int main(){
    ofstream KL("IsEven.js");
    KL<<"func isEven(number){"<<endl;
    KL<<"if (number===0)return 1"<<endl;
    int range=20000;
    for(int i=0;i<range;i++){
        KL<<"else if(number==="<<to_string(i)<<") return "<<i%2<<endl;
    }
    KL<<"}"<<endl;
    KL.close();
}
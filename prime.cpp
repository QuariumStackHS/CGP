#include <iostream>
using namespace std;
int get_prime(int seed){
    return (24*seed)+1;
}
int main(){
    for(int i=0;i<100;i++){
        cout<<get_prime(i)<<endl;
    }
}
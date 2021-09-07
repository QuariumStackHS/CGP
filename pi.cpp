#include <gmp.h>
#include <iostream>
#include <math.h>
using namespace std;
#define XbaseP 210

long double getPI(int64_t iteration, int64_t Xbase)
{
    long double Ret;
    iteration--;
    if (iteration != 0)
    {
        Xbase += 2;
        Ret = 6 + (Xbase * Xbase) / getPI(iteration, Xbase);
    }
    
    return Ret;
}

long double PI() { return 3 + ((1 * 1) / getPI(99999, 1)); }
/*
π=3+(1^2)/(6+(3^2))/6+(5*2)...
*/
#define pi PI()

int main()
{
    cout.precision(XbaseP - 2);
    cout << "pi: " << pi << endl;
    cout<<getPI(200000,100001);

    return 0;
}
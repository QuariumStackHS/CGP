#include <string>
#include <cstring>
#include <vector>
using namespace std;
namespace Test
{
    typedef int (*Wrap)(char **, int);

    class Tester
    {
    private:
        class TestNames
        {
        public:
            Wrap Func;
            string name;

            TestNames(Wrap,string);
        };
        vector<TestNames*>TSN;
    public:
        Tester();
        void*_Wrap(Wrap,string);
        int Launch(string,char**,int);
    };

};
#include <AES.h>
#include <iostream>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;
class AES_CGPP{

public:
    struct IV_Key{
        char IV[IVlengh];
        char Key[Keylengh];
    };
    IV_Key set;
unsigned char iv[IVlengh];
  unsigned char key[Keylengh];
  AES *aes=new AES(256);
    class AES_Info{
        public:
            AES_Info();
    };
    void Save_Enc(const char*);
    int Load_Enc(const char*);
    void Create_Enc();
    AES_CGPP();
};
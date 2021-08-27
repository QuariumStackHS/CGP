#include <arpa/inet.h>
#include <fstream>
using namespace std;
#include <AES.h>

#include "../AES/include/AES.h"
class AES_Certificate
{

protected:
    unsigned char *Key = new unsigned char[256];
    unsigned char *IV = new unsigned char[256];
    friend class CGP_share;

public:
    bool operator==(AES_Certificate *iAES)
    {
        for (int i = 0; i < 256; i++)
        {
            if (iAES->Key[i] != this->Key[i])
                return 0;
            if (iAES->IV[i] != this->IV[i])
                return 0;
        }
        return 1;
    }
    AES_Certificate(string Server_name = "Cert.AES")
    {
        ifstream AES_Cert(Server_name, ios::binary);
        AES_Cert.read((char *)&this->Key, 256);
        AES_Cert.read((char *)&this->IV, 256);
        AES_Cert.close();
        //cout<<this->Key<<endl;
        //cout<<this->IV<<endl;
    }
    AES_Certificate(unsigned char K[256], unsigned char I[256])
    {
        memcpy(this->Key, K, 256);
        memcpy(this->IV, I, 256);
    }
    bool Save(string Filename = "Cert.AES")
    {
        ofstream AES_Cert(Filename, ios::binary);
        unsigned char total[512] = {0};
        for (int i = 0; i < 256; i++)
        {
            total[i] = Key[i];
        }
        for (int i = 0; i < 256; i++)
        {
            total[i + 256] = IV[i];
        }
        AES_Cert << total;
        AES_Cert.close();
        delete &total;
    }
    ~AES_Certificate()
    {
        delete[] Key;
        delete[] IV;
    }
};
class Virtual_Socket
{
public:
    void *send();
};
class CGP_share
{
public:
    AES_Certificate *AES_Cert = new AES_Certificate();
    AES *Cypher = new AES();
    CGP_share()
    {
    }
    ~CGP_share()
    {
        delete AES_Cert;
        //delete Cypher;
    }
    void send(string str)
    {
        unsigned int Size;
        unsigned char *Enc = this->Cypher->EncryptCFB((unsigned char *)str.c_str(), str.size() - 1, AES_Cert->Key, AES_Cert->IV, Size);
    }
};

inline void gen_IV(unsigned char iv[256])
{

    for (int i = 0; i <= IVlengh - 1; i++)
    {
        iv[i] = rand() % 255 + 1;
    }
}
inline void Gen_Key(unsigned char key[256])
{
    for (int i = 0; i <= (Keylengh - 1); i++)
    {
        key[i] = rand() % 255 + 1;
    }
}
inline AES_Certificate *Create_Cert()
{
    srand(time(NULL));
    unsigned char Key[256] = {0};
    unsigned char IV[256] = {0};
    Gen_Key(Key);
    gen_IV(IV);
    AES_Certificate *AES_C = new AES_Certificate(Key, IV);
    AES_C->Save();
    return AES_C;
}
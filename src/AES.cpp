#include <Aes.hpp>
#include <fstream>
#include <iterator>
#include <vector>

struct Aes_Save{
    char IV[IVlengh+1];
    char endIV=-1;
    char Key[Keylengh+1];
    char endKey=-1;
};
unsigned char *gen_IV(unsigned char iv[16]){

    for(int i=0;i<=IVlengh-1;i++){
        iv[i]=rand() % 255 + 1;
    }
    return iv;
}

unsigned char *Gen_Key(unsigned char key[32]){
    int v;
    for(int i=0;i<=(Keylengh-1);i++){
        v=rand() % 255 + 1;
        key[i]=v;
    }
    return key;
}

AES_CGPP::AES_CGPP(){
    srand (time(NULL));
}
int AES_CGPP::Load_Enc(const char*Filename){

    std::ifstream input( Filename, std::ios::binary|ios::out );
    //char sbuffer[16];
    Aes_Save KIV;
    input.read((char*)&KIV.IV,IVlengh);
    for(int i=0;i<=IVlengh-1;i++)
    this->set.IV[i]=KIV.IV[i];
    input.read((char*)&KIV.Key,Keylengh);
    for(int i=0;i<=Keylengh-1;i++)
    this->set.Key[i]=KIV.Key[i];
    //for(int i=0;i<=15;i++){
    //    this->iv[i]=sbuffer[i];
    //}
    //cout<<buffer<<endl;

}

void AES_CGPP::Save_Enc(const char*Filename){
    Aes_Save KIV;
    for (int i=0;i<=IVlengh-1;i++){
        KIV.IV[i]=this->set.IV[i];
    }
    for (int i=0;i<=Keylengh-1;i++){
        KIV.Key[i]=this->set.Key[i];
    }
    ofstream Save(Filename, ios_base::out|std::ios::binary);
    Save.clear();
    Save.write((char*)&KIV.IV,IVlengh-1);
    Save.write((char*)&KIV.Key,Keylengh-1);
    Save.close();


}
void AES_CGPP::Create_Enc(){
    gen_IV((unsigned char*)&this->set.IV);
    Gen_Key((unsigned char*)&this->set.Key);

}
int test(){
    AES_CGPP*aes=new AES_CGPP();
    unsigned char tt[]="this is a test of AES encryption";
    AES i =AES();
    unsigned int s;
    //aes->Create_Enc();
    //aes->Save_Enc("testfilename");
    aes->Load_Enc("testfilename");
    unsigned char* vf=i.EncryptCBC(tt,sizeof(tt),(unsigned char*)aes->set.Key,(unsigned char*)aes->set.IV,s);
    
    //aes->Create_Enc();
    
    cout<<i.DecryptCBC(vf,s,(unsigned char*)aes->set.Key,(unsigned char*)aes->set.IV)<<endl;
cout<<aes->set.Key<<endl;
    return 0;

}
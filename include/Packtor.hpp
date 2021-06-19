
#include <vector>
using namespace std;
class Packtor{

    public:
        class cyphFile{
            
            public:
            cyphFile();
            u_int64_t filename_Size;
            cyphFile*set_filename(char*filename,u_int64_t Size);
            char*filename;
            cyphFile*set_Data(char*Data,u_int64_t Size);
            u_int64_t DATA_Size;
            char *data;
        };
        class DataPack{
            public:
            DataPack();
            DataPack*set_IV(unsigned char*IV,u_int64_t size);
            u_int64_t IV_Size;
            char*IV;
            u_int64_t FileNBR=0;
            vector<cyphFile*>enc_files;
        };
        DataPack *DP=new DataPack();
        Packtor();
        int add_file(char*filename,int filename_size,char*data,int data_size);
        void set_IV( char*,int);
        int Gen_pack(char*Archive);
        DataPack *Load_pack(char*Archive);


};
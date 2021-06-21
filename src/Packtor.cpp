#include <Packtor.hpp>
#include <iostream>
#include <fstream>
#include <AES.h>
Packtor::cyphFile::cyphFile(){

}
Packtor::DataPack::DataPack(){

}
Packtor::cyphFile*Packtor::cyphFile::set_Data(char*Datal,u_int64_t i){
    this->DATA_Size=i;
    //this->data=
    memcpy(&this->data,&Datal,i);
    //cout<<&this->data<<endl;
    //cout<<<<endl;
    return this;
}
Packtor::cyphFile*Packtor::cyphFile::set_filename(char*Datal,u_int64_t i){
    this->filename_Size=i;
    //this->data=
    memcpy(&this->filename,&Datal,i);
    //cout<<&this->data<<endl;
    //cout<<<<endl;
    return this;
}
Packtor::Packtor()
{
}
void Packtor::set_IV(char *IV, int IV_size)
{
    this->DP->IV = IV;
    this->DP->IV_Size = IV_size;
}
int Packtor::add_file(char *filename, int filename_size, char *Data, int data_size)
{
    //cout << "generating cyph" << endl;
    this->DP->enc_files.push_back(new cyphFile());
    //cout << "generated cyph" << endl;
    this->DP->enc_files[this->DP->FileNBR]->set_Data(Data,data_size);
    this->DP->enc_files[this->DP->FileNBR]->filename = filename;
    this->DP->enc_files[this->DP->FileNBR]->filename_Size = filename_size;
    this->DP->FileNBR++;
}
int Packtor::Gen_pack(char *filename)
{
    ofstream Archive(filename, ios::out | ios::binary);
    //cout << "this" << endl;
    Archive.write((char *)&this->DP->IV_Size, sizeof(this->DP->IV_Size));
    //cout << "gonna write IV" << endl;
    Archive.write((char *)this->DP->IV, this->DP->IV_Size);
    Archive.write((char *)&this->DP->FileNBR, sizeof(this->DP->FileNBR));
    //cout << "gonna write files.." << endl;
    for (int i = 0; i < this->DP->enc_files.size(); i++)
    {
        Archive.write((char *)&this->DP->enc_files[i]->filename_Size, sizeof(this->DP->enc_files[i]->filename_Size));
        Archive.write((char *)this->DP->enc_files[i]->filename, this->DP->enc_files[i]->filename_Size*sizeof(char));
        Archive.write((char *)&this->DP->enc_files[i]->DATA_Size, sizeof(this->DP->enc_files[i]->DATA_Size));
        Archive.write((char *)this->DP->enc_files[i]->data, this->DP->enc_files[i]->DATA_Size*sizeof(char));
    }
    cout<<"end"<<endl;
    Archive.close();
}
Packtor::DataPack *Packtor::Load_pack(char *filename)
{
    DataPack *NewDataPack = new DataPack();
    ifstream Archive(filename, ios::out | ios::binary);
    Archive.read((char *)&NewDataPack->IV_Size, sizeof(NewDataPack->IV_Size));
    //cout << NewDataPack->IV_Size << endl;
    char IV[NewDataPack->IV_Size];
    Archive.read((char *)&IV, NewDataPack->IV_Size);

    NewDataPack->IV = (char *)&IV;
    //cout << (char *)&IV << " | " << NewDataPack->IV << endl;

    Archive.read((char *)&NewDataPack->FileNBR, sizeof(NewDataPack->FileNBR));
    //cout << NewDataPack->FileNBR << endl;
    //exit(0);
    cout<<NewDataPack->IV<<"("<<NewDataPack->IV_Size<<")"<<endl;
    cout<<"Files: "<<NewDataPack->FileNBR<<endl;
    for (int i = 0; i < NewDataPack->FileNBR; i++)
    {
        NewDataPack->enc_files.push_back(new cyphFile());
        //cout << i << endl;
        u_int64_t Filenamesize;
        Archive.read((char *)&Filenamesize, sizeof(Filenamesize));
        //cout<<Filenamesize<<endl;
        //cout << NewDataPack->enc_files[i]->filename_Size << endl;
        char Fname[Filenamesize];
        Archive.read((char *)&Fname, Filenamesize);
        
        NewDataPack->enc_files[i]->set_filename(Fname,Filenamesize);
        //cout << (char *)&Fname << " | " << NewDataPack->enc_files[i]->filename << endl;
        u_int64_t Data_size;
        Archive.read((char *)&Data_size, sizeof(Data_size));
        //cout << NewDataPack->enc_files[i]->DATA_Size << endl;
        char data[Data_size];
        Archive.read((char *)&data, Data_size);
        NewDataPack->enc_files[i]->set_Data(data,Data_size);
        cout<<"Unpacking: "<<NewDataPack->enc_files[i]->filename<<"\n";
        cout<<"\tSize: "<<NewDataPack->enc_files[i]->DATA_Size<<"Chars"<<endl;
        cout<<NewDataPack->enc_files[i]->data<<endl;
        //cout << (char *)data << " | " << NewDataPack->enc_files[i]->data << endl;
    }
    //cout << "readed" << endl;
    //this->DP=NewDataPack;
    //cout<<NewDataPack->IV<<endl;

    //for(int i=0;i<NewDataPack->FileNBR;i++){
        //cout<<NewDataPack->enc_files[i]->filename<<"\n";
        //cout<<"\tchars:"<<NewDataPack->enc_files[i]->DATA_Size<<endl;
    //}
}
unsigned char *gen_IV(unsigned char iv[32]){

    for(int i=0;i<=IVlengh-1;i++){
        iv[i]=rand() % 255 + 1;
    }
    return iv;
}

#include <Prot.hpp>
#include <iostream>
#include <stdint.h>
#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
     
#define TRUE   1 
#define FALSE  0 
//#define int int64_t

#define PORT 8888
struct Server{
    int opt = TRUE;  
    int master_socket , addrlen , new_socket , client_socket[30] , 
          max_clients = 30 , activity, i , valread , sd;  
    int max_sd;  
    struct sockaddr_in address;  
         
    char buffer[1025];  //data buffer of 1K 
         
    //set of socket descriptors 
    fd_set readfds; 
};
int main(int argc,char**argv)
{
    AES_Certificate*Cert=Create_Cert();
    AES_Certificate *AES_C = new AES_Certificate();
    //CGP_share* Share=new CGP_share();
    //struct Server S; 
    delete Cert;
     delete AES_C;
    
    //cout<<Cert->operator==(AES_C)<<endl;
    //delete AES_C;
}

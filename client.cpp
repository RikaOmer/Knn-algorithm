#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

int   main(int length,char** args){

 const int port= atoi(args[2]);
 if (port < 1024 || port > 65535){
    cout<<" invalid port"<<endl;
 }
 const char* ip =(args[1]);
 char num[3];
 int j = 0;
 int newN ;
 if (strlen(ip) > 15){
    cout<<"invalid ip"<<endl;
    return -1; 
 }
  if (!isdigit(ip[0])){
    cout<<"invalid ip"<<endl;
  }
 for(int i =0 ; i < strlen(ip); i++){
    if (isdigit(ip[i])){
        num[j] = ip[i];
        j++;
    }
    else if(isspace(ip[i])){
         cout<<"invalid ip"<<endl;
    }
    else if ( ip[i] == 46 && j > 3){
        cout<<"invalid ip"<<endl;
    }
    else if (j == 3 && ip[i+1]==46){
        newN = atoi(num);
        if(newN>255 || newN<1){
        cout<<"invalid ip"<<endl;
        }else j=0;
    }
    if(ip[i]== 46 && j == 2){
        if (ip[i-1]< 0 || ip [i-2] < 1){
            cout<<" invalid ip"<<endl;
        } else j=0;
    }

    if (ip[i]==46 && j==1){
        if (ip[i-1] < 1) {
             cout<<" invalid ip"<<endl;
        }else j=0;
    }
         
 }
 int sock =  socket(AF_INET, SOCK_DGRAM,0);
 if(sock < 0){
    cout<< "can't create socket"<<endl ;
 }
  struct sockaddr_in sin; 
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = inet_addr(ip);
  sin.sin_port = htons(port);
  int connect =  bind(sock,(struct sockaddr*)&sin, sizeof(sin));
  if (connect < 0){
    cout<<"can't bind the server with the client"<<endl;
      return -1;
}

 string vectorString;
  while (getline(cin, vectorString)) {
     char sendSer[sizeof(vectorString)-1] ;
        int p =0;
        for (char a : vectorString){
            sendSer[p] = a;
            p++;
        }
    int is_sent = send(sock , sendSer , sizeof(vectorString)-1 , 0 );
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<<"vector  message sent to server" <<std::endl;
    }
    }

    char buffer[1024] = {0};
    int valread = read( sock , buffer, 1024);
    std::cout<<buffer<<std::endl;

    close(sock);


    return 0;
    }
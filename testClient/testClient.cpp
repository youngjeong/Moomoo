#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include "../Server/protocol.h"
#define BUF_SIZE 2048
using namespace std;

int main() {
    int sock;
    struct sockaddr_in serv_adr;
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1)
        printf("socker() error");
    memset(&serv_adr, 0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr("13.124.83.116");

    serv_adr.sin_port=htons(atoi("9094"));
    
    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        printf("connect error");
    
    _header header;
    memset(&header,0,sizeof(header));

    
//      S_PROTOCOL_LOBBY_ROOMLIST_REQ body;
//    memset(&body,0,sizeof(body));
//   
//    body.header.protocolID = PROTOCOL_LOBBY_ROOMLIST_REQ;
//    body.header.result = 15;
//    
    //strcpy(body.nickname, "newnick");

    S_PROTOCOL_LOGIN_REQ req;
    memset(&req, 0, sizeof(req));
    req.header.protocolID=PROTOCOL_LOGIN_REQ;
    req.header.result=1;
    
    strcpy(req.id,"test1");
    strcpy(req.password,"1234");
    //strcpy(req.nickname,"dordong");

    
    int body_size = sizeof(req);
    write(sock, &req,body_size);
    
    char buf[BUF_SIZE]={0,};
    read(sock, buf, BUF_SIZE);

    S_PROTOCOL_LOGIN_ACK res;
    memset(&res,0,sizeof(res));
    memcpy(&res,buf,sizeof(res));
    
    printf("res.header.userno : %d\n ",res.header.userno);

    /*body.header.protocolID = PROTOCOL_JOIN_REQ;
    body.header.result = 10;
    strcpy(body.id, "321");
    strcpy(body.password, "456s");
    strcpy(body.nickname, "newnick");
    
<<<<<<< HEAD
    int body_size = sizeof(body);
    write(sock, &body,body_size);
    
    char buf[BUF_SIZE]={0,};
    read(sock, buf, BUF_SIZE);
    S_PROTOCOL_JOIN_ACK ack_msg;
    memcpy(&ack_msg, buf, sizeof(ack_msg));
=======
//    S_PROTOCOL_LOBBY_ROOMLIST_ACK ack_msg;
//    memcpy(&ack_msg, buf, sizeof(ack_msg));
//    printf("%d\n",ack_msg.count);
//    printf("%s\n",ack_msg.rooms[0].roomName);
//    printf("%d\n",ack_msg.rooms[0].room_no);
//    
//    
//    printf("%s\n",ack_msg.rooms[1].roomName);
//    printf("%d\n",ack_msg.rooms[1].room_no);
>>>>>>> 5/30_ej
    
    printf("%d", ack_msg.header.result);*/
        
    return 0;
}
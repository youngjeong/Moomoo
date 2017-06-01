#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include "protocol.h"
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

    serv_adr.sin_port=htons(atoi("9090"));
    
    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        printf("connect error");
    
    _header header;
    memset(&header,0,sizeof(header));

    
    /*
    int myUserKey;
    
     S_PROTOCOL_LOGIN_REQ loginreq;
    memset(&loginreq, 0, sizeof(loginreq));
    loginreq.header.protocolID=PROTOCOL_LOGIN_REQ;
    //strcpy(req.nickname,"dordong");
    strcpy(loginreq.id,"20122472");
    strcpy(loginreq.password,"1234");
    
    int body_size = sizeof(loginreq);
    write(sock, &loginreq,body_size);
    
    char buf[BUF_SIZE]={0,};
    read(sock, buf, BUF_SIZE);

    S_PROTOCOL_LOGIN_ACK res_login;
    memset(&res_login,0,sizeof(res_login));
    memcpy(&res_login,buf,sizeof(res_login));
    
    printf("login request userno  : %d\n",res_login.header.userno);
    myUserKey=res_login.header.userno;    
  
    
    memset(&buf,0,sizeof(buf));
   
    S_PROTOCOL_LOBBY_MAKE_ROOM_REQ req;
    memset(&req, 0, sizeof(req));
    req.header.protocolID=PROTOCOL_LOBBY_MAKE_ROOM_REQ;
    req.header.userno=myUserKey;
    //strcpy(req.nickname,"dordong");
    
    strcpy(req.room_name,"testroom1");
    
    body_size = sizeof(req);
    write(sock, &req,body_size);
    
    buf[BUF_SIZE]={0,};
    read(sock, buf, BUF_SIZE);

    S_PROTOCOL_LOBBY_MAKE_ROOM_ACK res;
    memset(&res,0,sizeof(res));
    memcpy(&res,buf,sizeof(res));
    
    if(res.header.result==ROOM_MAKE_SUCCESSFULLY)
        puts("room made");
    else if(res.header.result==ROOM_ALREADY_EXISTING_NAME)
        puts("already exist name");
        */
   
   // ----------------
   
    
   
     int myUserKey;
    
     S_PROTOCOL_LOGIN_REQ loginreq;
    memset(&loginreq, 0, sizeof(loginreq));
    loginreq.header.protocolID=PROTOCOL_LOGIN_REQ;
    //strcpy(req.nickname,"dordong");
    strcpy(loginreq.id,"20122472");
    strcpy(loginreq.password,"1234");
    
    int body_size = sizeof(loginreq);
    write(sock, &loginreq,body_size);
    
    char buf[BUF_SIZE]={0,};
    read(sock, buf, BUF_SIZE);

    S_PROTOCOL_LOGIN_ACK res_login;
    memset(&res_login,0,sizeof(res_login));
    memcpy(&res_login,buf,sizeof(res_login));
    
    printf("login request userno  : %d\n",res_login.header.userno);
    myUserKey=res_login.header.userno;    
  
    
    memset(&buf,0,sizeof(buf));
    
    S_PROTOCOL_LOBBY_JOIN_TO_ROOM_REQ req1;
    //memset(&req, 0, sizeof(req));
    req1.header.protocolID=PROTOCOL_LOBBY_JOIN_TO_ROOM_REQ;
    
    req1.header.result=1;
    req1.room_no=1;
    //strcpy(req.nickname,"dordong");

    memset(&buf,0,sizeof(buf));
    
    body_size = sizeof(req1);
    write(sock, &req1,body_size);
    
    read(sock, buf, BUF_SIZE);
    
    //
    S_PROTOCOL_LOBBY_JOIN_TO_ROOM_ACK res1;
    memset(&res1,0,sizeof(res1));
    memcpy(&res1,buf,sizeof(res1));
    
    printf("res.result : %d\n",res1.header.result);
    if(res1.header.result==JOIN_TO_ROOM_OK)
        puts("join success");
    else if(res1.header.result==JOIN_TO_ROOM_DENIED)
        puts("join denied");
    
    
    
    //---------------
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
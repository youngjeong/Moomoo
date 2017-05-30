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
    serv_adr.sin_port=htons(atoi("9091"));
    
    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        printf("connect error");
    
    _header header;
    memset(&header,0,sizeof(header));
    S_PROTOCOL_JOIN_REQ body;
    memset(&body,0,sizeof(body));
    body.header.protocolID = PROTOCOL_JOIN_REQ;
    body.header.result = 10;
    strcpy(body.id, "1234");
    strcpy(body.password, "1234");
    strcpy(body.nickname, "1234");
    
    int body_size = sizeof(body);
    write(sock, &body,body_size);
    
    char buf[BUF_SIZE]={0,};
    read(sock, buf, BUF_SIZE);
    S_PROTOCOL_JOIN_ACK ack_msg;
    memcpy(&ack_msg, buf, sizeof(ack_msg));
    
    printf("%d", ack_msg.header.result);
        
    return 0;
}
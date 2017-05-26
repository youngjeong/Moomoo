#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include "protocol.h"

#define BUF_SIZE 2048
#define EPOLL_SIZE 50
void error_handling(char *buf);
int read_body(int fd, char* body_buf, int size);
int join_request(S_PROTOCOL_JOIN_REQ *body_buf);
int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t adr_sz;
    int str_len, i;
    char buf[BUF_SIZE];
    
    struct epoll_event *ep_events;
    struct epoll_event event;
    int epfd, event_cnt;
    
    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    int option;
    socklen_t optlen= sizeof(option);
    option=true;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, optlen);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("bind() error");
    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");
    
    epfd=epoll_create(EPOLL_SIZE);
    ep_events=(struct epoll_event*)malloc(sizeof(struct epoll_event)*EPOLL_SIZE);
    
    event.events=EPOLLIN;
    event.data.fd=serv_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);
    
    while(1)
    {
        event_cnt=epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if(event_cnt==-1){
            puts("epoll_wait() error");
            break;
        }
        
        for(i=0;i<event_cnt;i++)
        {
            if(ep_events[i].data.fd==serv_sock)
            {
                adr_sz=sizeof(clnt_adr);
                clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
                event.events=EPOLLIN;
                event.data.fd=clnt_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
                printf("connected client: %d \n", clnt_sock);
            }
            else
            {
                int recv_len=0;
                _header header_buf;
                int header_size = sizeof(_header);
                int body_size = 0;
                char tmp_buf[4]={0,};
                read(ep_events[i].data.fd, tmp_buf, 4);    
                while(recv_len<header_size)
                {
                    int read_byte=read(ep_events[i].data.fd, &header_buf+recv_len, header_size-recv_len);    
                    recv_len+=read_byte;
                }
                
                switch(header_buf.protocolID){
                    case PROTOCOL_JOIN_REQ:
                    {
                        S_PROTOCOL_JOIN_REQ body_buf;
                //        memcpy(&body_buf+4, &header_buf, header_size);
                        body_buf.header = header_buf;
                        int size = sizeof(body_buf);
                        //body_size = read_body(ep_events[i].data.fd, (char*)&body_buf+header_size, size-header_size);
                        int body_size = size-header_size-4;
                        recv_len=0;
                       
                        while(recv_len < body_size)
                        {
                            int recv_size = read(ep_events[i].data.fd, (_header*)&body_buf+recv_len+header_size+4, body_size-recv_len);
                            recv_len+=recv_size;
                        }
                      
                        join_request(&body_buf);
                        break;
                    }
                    case PROTOCOL_LOGIN_REQ:
                    {
                        S_PROTOCOL_LOGIN_REQ body_buf;
                        memcpy(&body_buf, &header_buf, header_size);
                        int size = sizeof(body_buf);
                        body_size = read_body(ep_events[i].data.fd, (char*)&body_buf+header_size, size-header_size);
                        break;
                        
                    }
                    case PROTOCOL_LOBBY_ROOMLIST_REQ:
                    {
                        S_PROTOCOL_LOBBY_ROOMLIST_REQ body_buf;
                        memcpy(&body_buf, &header_buf, header_size);
                        int size = sizeof(body_buf);
                        body_size = read_body(ep_events[i].data.fd, (char*)&body_buf+header_size, size-header_size);
                        break;
                    }
                    case PROTOCOL_LOBBY_PLAYER_LIST_REQ:
                    {
                        S_PROTOCOL_LOBBY_PLAYER_LIST_REQ body_buf;
                        memcpy(&body_buf, &header_buf, header_size);
                        int size = sizeof(body_buf);
                        body_size = read_body(ep_events[i].data.fd, (char*)&body_buf+header_size, size-header_size);
                        break;
                    }
                    case PROTOCOL_ROOM_SET_READY_STATUS_REQ:
                    {
                        S_PROTOCOL_ROOM_SET_READY_STATUS_REQ body_buf;
                        memcpy(&body_buf, &header_buf, header_size);
                        int size = sizeof(body_buf);
                        body_size = read_body(ep_events[i].data.fd, (char*)&body_buf+header_size, size-header_size);
                        break;
                    }
                    case PROTOCOL_ROOM_PLAYER_LIST_REQ:
                    {
                        S_PROTOCOL_ROOM_PLAYER_LIST_REQ body_buf;
                        memcpy(&body_buf, &header_buf, header_size);
                        int size = sizeof(body_buf);
                        body_size = read_body(ep_events[i].data.fd, (char*)&body_buf+header_size, size-header_size);
                        break;
                    }
                    case PROTOCOL_INGAME_LOADING_COMPLETED:
                    {
                        S_PROTOCOL_INGAME_LOADING_COMPLETED body_buf;
                        memcpy(&body_buf, &header_buf, header_size);
                        int size = sizeof(body_buf);
                        body_size = read_body(ep_events[i].data.fd, (char*)&body_buf+header_size, size-header_size);
                        break;
                    }
                    case PROTOCOL_PLAYER_STATUS_CHANGED_REQ:
                    {
                        S_PROTOCOL_PLAYER_STATUS_CHANGED_REQ body_buf;
                        memcpy(&body_buf, &header_buf, header_size);
                        int size = sizeof(body_buf);
                        body_size = read_body(ep_events[i].data.fd, (char*)&body_buf+header_size, size-header_size);
                        break;
                    }
                    case PROTOCOL_GAME_END_REQ:
                    {
                        S_PROTOCOL_GAME_END_REQ body_buf;
                        memcpy(&body_buf, &header_buf, header_size);
                        int size = sizeof(body_buf);
                        body_size = read_body(ep_events[i].data.fd, (char*)&body_buf+header_size, size-header_size);
                        break;
                    }
                }
                
                if(str_len==0)
                {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd);
                    printf("closed client: %d\n", ep_events[i].data.fd);
                }
                else{
                    write(ep_events[i].data.fd, buf, str_len);
                }
            }
        }
    }
    close(serv_sock);
    close(epfd);
    return 0;
}

void error_handling(char *buf)
{
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}

int read_body(int fd, char* body_buf, int size)
{
    int body_size = size;
    int recv_len=0;
    while(recv_len < body_size)
    {
        int recv_size = read(fd, body_buf+recv_len, body_size-recv_len);
        recv_len+=recv_size;
    }
    return recv_len;
}

int join_request(S_PROTOCOL_JOIN_REQ *body_buf)
{
    printf("Received ID : %s\n", body_buf->id);
    printf("Received PW : %s\n", body_buf->password);
    printf("Received Nick : %s\n", body_buf->nickname);
    return 0;
}
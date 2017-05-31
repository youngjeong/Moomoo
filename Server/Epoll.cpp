#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<algorithm>
#include<vector>
#include "protocol.h"
#include "Communicator.h"

#define BUF_SIZE 2048
#define EPOLL_SIZE 50

using namespace std;

void error_handling(char *buf);
int read_body(int fd, char* body_buf, int size);
void epoll_init(int port)
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t adr_sz;
    int str_len, i;
    char buf[BUF_SIZE];
    
    struct epoll_event *ep_events;
    struct epoll_event event;
    int epfd, event_cnt;
    
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    int option;
    socklen_t optlen= sizeof(option);
    option=true;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, optlen);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(port);
    
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("bind() error");
    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");
    
    epfd=epoll_create(EPOLL_SIZE);
    ep_events=(struct epoll_event*)malloc(sizeof(struct epoll_event)*EPOLL_SIZE);
    
    event.events=EPOLLIN;
    event.data.fd=serv_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);
    vector<int> enabled_fd;
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
                enabled_fd.push_back(clnt_sock);
                printf("connected client: %d \n", clnt_sock);
            }
            else
            {
                if(Communicator::parse(ep_events[i].data.fd) < 0){
                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd);
                    enabled_fd.erase(find(enabled_fd.begin(), enabled_fd.end(), ep_events[i].data.fd));
                    printf("closed client: %d\n", ep_events[i].data.fd);
                }
            }
        }
    }
    close(serv_sock);
    close(epfd);
}

void error_handling( char *buf)
{
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}
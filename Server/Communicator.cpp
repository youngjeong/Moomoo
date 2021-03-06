#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<vector>
#include<map>
#include "errorcode.h"
#include "protocol.h"
#include "Communicator.h"
#include "DBConnect.h"
#include "InLoginController.h"
#include "UserMap.h"
#include "InLobbyController.h"
#include "InRoomController.h"
#include "InGameController.h"

#define BUF_SIZE 2048



// Todo: Test function must be removed
int join_request(S_PROTOCOL_JOIN_REQ *body_buf);
int login_request(S_PROTOCOL_LOGIN_REQ *body_buf);

int Communicator::parse(int sock) {
    int recv_len = 0;
    _header header_buf;
    int header_size = sizeof (_header);
    char body_buf[BUF_SIZE] = {0,};
    int body_size = 0;
    char tmp_buf[4] = {0,};
    read(sock, tmp_buf, 4);
    if (read(sock, &header_buf, header_size) == 0)
        return -1;

    memcpy(body_buf+4, &header_buf, header_size);
    
    switch (header_buf.protocolID) {
        case PROTOCOL_JOIN_REQ:
        {
            Communicator::readBody(sock, body_buf, sizeof (S_PROTOCOL_JOIN_REQ));
            S_PROTOCOL_JOIN_REQ body;
            S_PROTOCOL_JOIN_ACK ack_msg;
            memcpy(&body, body_buf, sizeof (body));
            // Join Request Function
            int join_result = InLoginController::signUpRequest(&body);
            ack_msg.header.result = join_result;
            write(sock, &ack_msg, sizeof (ack_msg)); // Join response
            break;
        }
        case PROTOCOL_LOGIN_REQ:
        {
            S_PROTOCOL_LOGIN_REQ body;
            S_PROTOCOL_LOGIN_ACK ack_msg;
            Communicator::readBody(sock, body_buf, sizeof (body));
            memcpy(&body, body_buf, sizeof (body));
            // Login Request Function
            ack_msg = InLoginController::loginRequest(&body, sock);
            write(sock, &ack_msg, sizeof(ack_msg));
            break;
        }
        case PROTOCOL_CHAT_REQ:
        {
            S_PROTOCOL_CHAT_REQ body;
            S_PROTOCOL_CHAT_ACK ack_msg;
            Communicator::readBody(sock, body_buf, sizeof(body));
            memcpy(&body, body_buf, sizeof(body));
            memcpy(&ack_msg, &body, sizeof(body));
            UserMap* usermap_instance  = UserMap::getInstance();
            auto UserMap = usermap_instance->getMap();
            if(UserMap.find(body.header.userno)->second.getStatus() == INLOBBY){
                strcpy(ack_msg.nickname, UserMap.find(body.header.userno)->second.getNickname());

                for(auto it=UserMap.begin(); it!=UserMap.end();it++){
                    if(it->second.getStatus() == INLOBBY)
                        write(it->second.getSockNum(), &ack_msg, sizeof(ack_msg));
                }
            }
            else if(UserMap.find(body.header.userno)->second.getStatus() == INROOM){
                InRoomController::chatRoom(body);
            }
            break;
        }
        case PROTOCOL_LOBBY_MAKE_ROOM_REQ:
        {
            S_PROTOCOL_LOBBY_MAKE_ROOM_REQ body;
            S_PROTOCOL_LOBBY_MAKE_ROOM_ACK response;
            
            Communicator::readBody(sock,body_buf,sizeof(body));
            memcpy(&body,body_buf,sizeof(body));
            InLobbyController::makeRoom(&body,&response);
            
            write(sock,&response,sizeof(response));
            
        }
        case PROTOCOL_LOBBY_ROOMLIST_REQ:
        {
            printf("communicator : PROTOCOL_LOBBY_ROOMLIST_REQ\n");
            //Todo debugTest must be romoved
            //debugTest : make room for testing
            S_PROTOCOL_LOBBY_ROOMLIST_REQ body;
            S_PROTOCOL_LOBBY_ROOMLIST_ACK response;
            Communicator::readBody(sock,body_buf,sizeof(body));
            memcpy(&body, body_buf, sizeof(body));
//            Room room1(1234,"testRoom1");
//            Room room2(4321,"testRoom2");
//            InLobbyController::debugTest(1234,room1);
//            InLobbyController::debugTest(4321,room2);
            InLobbyController::getAllRooms(&body,&response);
          
            write(sock,&response,sizeof(response));
         
            // Request Room List Function
            break;
        }
        case PROTOCOL_LOBBY_JOIN_TO_ROOM_REQ:
        {
            puts("PROTOCOL_LOBBY_JOIN_TO_ROOM_REQ");
            S_PROTOCOL_LOBBY_JOIN_TO_ROOM_REQ body;
            S_PROTOCOL_LOBBY_JOIN_TO_ROOM_ACK res;
            Communicator::readBody(sock,body_buf,sizeof(body));
            memcpy(&body,body_buf,sizeof(body));
            InLobbyController::joinToRoom(&body, &res);
            write(sock,&res,sizeof(body));
            
            break;
        }
        case PROTOCOL_LOBBY_PLAYER_LIST_REQ:
        {
            S_PROTOCOL_LOBBY_PLAYER_LIST_REQ body;
            Communicator::readBody(sock, body_buf, sizeof (body));
            memcpy(&body, body_buf, sizeof (body));
            // Request Lobby Player List Function
            break;
        }
        case PROTOCOL_PLAYER_CHANGE_READY_STATUS_REQ:
        {
            S_PROTOCOL_PLAYER_CHANGE_READY_STATUS_REQ body;
            Communicator::readBody(sock, body_buf, sizeof (body));
            memcpy(&body, body_buf, sizeof (body));
            
            InRoomController::changeReadyStatus(body.header.userno, body.status);
            // Change Player Status Function
            break;
        }
        case PROTOCOL_ROOM_PLAYER_LIST_REQ:
        {
            S_PROTOCOL_ROOM_PLAYER_LIST_REQ body;
            Communicator::readBody(sock, body_buf, sizeof (body));
            memcpy(&body, body_buf, sizeof (body));
            // Request Room Player List Function
            break;
        }
        case PROTOCOL_INGAME_LOADING_COMPLETED:
        {
            S_PROTOCOL_INGAME_LOADING_COMPLETED body;
            Communicator::readBody(sock, body_buf, sizeof (body));
            memcpy(&body, body_buf, sizeof (body));
            // Change Player Status to Load Complete Function
            break;
        }
        case PROTOCOL_PLAYER_STATUS_CHANGED_REQ:
        {
            S_PROTOCOL_PLAYER_STATUS_CHANGED_REQ body;
            Communicator::readBody(sock, body_buf, sizeof (body));
            memcpy(&body, body_buf, sizeof (body));
            // Change Player Status Function
            break;
        }
        case PROTOCOL_GAME_END_REQ:
        {
            S_PROTOCOL_GAME_END_REQ body;
            Communicator::readBody(sock, body_buf, sizeof (body));
            memcpy(&body, body_buf, sizeof (body));
            // Change Player Status Function
            break;
        }
     
    }
    return 1;
}

void Communicator::readBody(int sock, char* body_buf, int size) {
    int header_size = sizeof (_header);
    int body_size = size - header_size - 4;
    int recv_len = 0;

    while (recv_len < body_size) {
        int recv_size = read(sock, body_buf + recv_len + header_size + 4, body_size - recv_len);
        recv_len += recv_size;
    }
}

void Communicator::writeMultiClient(vector<int> sock_list, T msg)
{
    for(int i=0;i<sock_list.size();i++)
    {
        write(sock_list[i], msg, sizeof(msg));
    }
}
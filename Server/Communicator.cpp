#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include "errorcode.h"
#include "protocol.h"
#include "Communicator.h"
#include "DBConnect.h"
#include "InLoginController.h"

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

    memcpy(body_buf + 4, &header_buf, header_size);
    switch (header_buf.protocolID) {
        case PROTOCOL_JOIN_REQ:
        {
            Communicator::readBody(sock, body_buf, sizeof (S_PROTOCOL_JOIN_REQ));
            S_PROTOCOL_JOIN_REQ body;
            memcpy(&body, body_buf, sizeof (body));
            // Join Request Function
            int join_result = InLoginController::signUpRequest(&body);
            S_PROTOCOL_JOIN_ACK ack_msg;
            ack_msg.header.result = join_result;
            write(sock, &ack_msg, sizeof (ack_msg)); // Join response
            break;
        }
        case PROTOCOL_LOGIN_REQ:
        {
            S_PROTOCOL_LOGIN_REQ body;
            Communicator::readBody(sock, body_buf, sizeof (body));
            memcpy(&body, body_buf, sizeof (body));
            // Login Request Function
            // login_request(&body);
            break;
        }
        case PROTOCOL_LOBBY_ROOMLIST_REQ:
        {
            S_PROTOCOL_LOBBY_ROOMLIST_REQ body;
            Communicator::readBody(sock, body_buf, sizeof (body));
            memcpy(&body, body_buf, sizeof (body));
            // Request Room List Function
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
        case PROTOCOL_ROOM_SET_READY_STATUS_REQ:
        {
            S_PROTOCOL_ROOM_SET_READY_STATUS_REQ body;
            Communicator::readBody(sock, body_buf, sizeof (body));
            memcpy(&body, body_buf, sizeof (body));
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
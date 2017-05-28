#include "protocol.h"
#include "Communicator.h"

#define BUF_SIZE 2048

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
            readBody(sock, body_buf, sizeof (S_PROTOCOL_JOIN_REQ));
            S_PROTOCOL_JOIN_REQ body;
            memcpy(&body, body_buf, sizeof (body));
            // Join Request Function
            // join_request(&body); 
            break;
        }
        case PROTOCOL_LOGIN_REQ:
        {
            S_PROTOCOL_LOGIN_REQ body;
            readBody(sock, body_buf, sizeof (body));
            memcpy(&body, body_buf, sizeof (body));
            // Login Request Function
            // login_request(&body);
            break;
        }
        case PROTOCOL_LOBBY_ROOMLIST_REQ:
        {
            break;
        }
        case PROTOCOL_LOBBY_PLAYER_LIST_REQ:
        {
            break;
        }
        case PROTOCOL_ROOM_SET_READY_STATUS_REQ:
        {
            break;
        }
        case PROTOCOL_ROOM_PLAYER_LIST_REQ:
        {
            break;
        }
        case PROTOCOL_INGAME_LOADING_COMPLETED:
        {
            break;
        }
        case PROTOCOL_PLAYER_STATUS_CHANGED_REQ:
        {
            break;
        }
        case PROTOCOL_GAME_END_REQ:
        {
            break;
        }
    }
    return 1;
}

int Communicator::readBody(int sock, char* body_buf, int size)
{
    int header_size = sizeof(_header);
    int body_size = size-header_size-4;
    int recv_len=0;
                        
    while(recv_len < body_size)
    {
        int recv_size = read(fd, body_buf+recv_len+header_size+4, body_size-recv_len);
        recv_len+=recv_size;
    }
}

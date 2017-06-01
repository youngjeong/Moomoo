#pragma once

enum Protocol {
   PROTOCOL_GENERAL_FAIL = 0x00000000,
   PROTOCOL_GENERAL_SUCESS = 0x00000001,

   PROTOCOL_OUTGAME = 0x000F0000,

   PROTOCOL_JOIN_REQ,
   PROTOCOL_JOIN_ACK,

   PROTOCOL_LOGIN_REQ,
   PROTOCOL_LOGIN_ACK,

   PROTOCOL_LOBBY_JOIN_TO_ROOM_REQ,//protocol added
   PROTOCOL_LOBBY_JOIN_TO_ROOM_ACK,//protocol added
   
   PROTOCOL_LOBBY_MAKE_ROOM_REQ,//protocol added
   PROTOCOL_LOBBY_MAKE_ROOM_ACK,//protocol added
   
   PROTOCOL_LOBBY_CHAT_REQ,
   PROTOCOL_LOBBY_CHAT_ACK,
   
   PROTOCOL_LOBBY_ROOMLIST_REQ,
   PROTOCOL_LOBBY_ROOMLIST_ACK,

   PROTOCOL_LOBBY_PLAYER_LIST_REQ,
   PROTOCOL_LOBBY_PLAYER_LIST_ACK,

   PROTOCOL_ROOM_SET_READY_STATUS_REQ,
   PROTOCOL_ROOM_SET_READY_STATUS_ACK,

   PROTOCOL_ROOM_PLAYER_LIST_REQ,
   PROTOCOL_ROOM_PLAYER_LIST_ACK,

   PROTOCOL_INGAME = 0x00F00000,

   PROTOCOL_INGAME_LOADING_COMPLETED,
   PROTOCOL_INGAME_START_GAME,

   PROTOCOL_PLAYER_STATUS_CHANGED_REQ,
   PROTOCOL_PLAYER_STATUS_CHANGED_ACK,

   PROTOCOL_GAME_END_REQ,
   PROTOCOL_GAME_END_ACK,
};

struct _protocol {
public:
   int getSize(void) { return sizeof(this); }
};

struct _header : _protocol {
   int protocolID;
   int result;
   int userno;
};

typedef struct _PROTOCOL_JOIN_REQ : _protocol {
   _header header;
   char id[16];
   char password[16];
   char nickname[16];

   _PROTOCOL_JOIN_REQ()
   {
      header.protocolID = PROTOCOL_JOIN_REQ;
   }
} S_PROTOCOL_JOIN_REQ;

typedef struct _PROTOCOL_JOIN_ACK : _protocol {
   _header header;

   _PROTOCOL_JOIN_ACK()
   {
      header.protocolID = PROTOCOL_JOIN_ACK;
   }
} S_PROTOCOL_JOIN_ACK;

typedef struct _PROTOCOL_LOGIN_REQ : _protocol {
   _header header;
   char id[16];
   char password[16];

   _PROTOCOL_LOGIN_REQ()
   {
      header.protocolID = PROTOCOL_LOGIN_REQ;
   }
} S_PROTOCOL_LOGIN_REQ;

typedef struct _PROTOCOL_LOGIN_ACK : _protocol {
   _header header;

   _PROTOCOL_LOGIN_ACK()
   {
      header.protocolID = PROTOCOL_LOGIN_ACK;
   }
} S_PROTOCOL_LOGIN_ACK;

struct _room_info {//room_info changed
   int room_no;
   //int current;
   //int total;
   char roomName[50];
};
//
//    char nickname[16];
typedef struct _PROTOCOL_LOBBY_CHAT_REQ : _protocol {
    _header header;
    char nickname[16];
    char message[256];
} S_PROTOCOL_LOBBY_CHAT_REQ, S_PROTOCOL_LOBBY_CHAT_ACK;

typedef struct _PROTOCOL_LOBBY_JOIN_TO_ROOM_REQ : _protocol
{
    _header header;
    int room_no;//room number to join
    _PROTOCOL_LOBBY_JOIN_TO_ROOM_REQ()
    {
        header.protocolID=PROTOCOL_LOBBY_JOIN_TO_ROOM_REQ;
    }  
}S_PROTOCOL_LOBBY_JOIN_TO_ROOM_REQ;


typedef struct _PROTOCOL_LOBBY_JOIN_TO_ROOM_ACK : _protocol
{
    _header header;
   _PROTOCOL_LOBBY_JOIN_TO_ROOM_ACK()
    {
        header.protocolID=PROTOCOL_LOBBY_JOIN_TO_ROOM_ACK;
    }  
}S_PROTOCOL_LOBBY_JOIN_TO_ROOM_ACK;

typedef struct _PROTOCOL_LOBBY_MAKE_ROOM_REQ : _protocol
{ 
    _header header;
   _PROTOCOL_LOBBY_MAKE_ROOM_REQ()
    {
        header.protocolID=PROTOCOL_LOBBY_MAKE_ROOM_REQ;
    }  
}S__PROTOCOL_LOBBY_MAKE_ROOM_REQ;

typedef struct _PROTOCOL_LOBBY_MAKE_ROOM_ACK : _protocol
{
    _header header;
   _PROTOCOL_LOBBY_MAKE_ROOM_ACK()
    {
        header.protocolID=PROTOCOL_LOBBY_MAKE_ROOM_ACK;
    }  
}S_PROTOCOL_LOBBY_MAKE_ROOM_ACK;

typedef struct _PROTOCOL_LOBBY_ROOMLIST_REQ : _protocol {
   _header header;
   _PROTOCOL_LOBBY_ROOMLIST_REQ()
   {
      header.protocolID = PROTOCOL_LOBBY_ROOMLIST_REQ;
   }
} S_PROTOCOL_LOBBY_ROOMLIST_REQ;

typedef struct _PROTOCOL_LOBBY_ROOMLIST_ACK : _protocol {
   _header header;
   int count;
   _room_info rooms[20];

   _PROTOCOL_LOBBY_ROOMLIST_ACK()
   {
      header.protocolID = PROTOCOL_LOBBY_ROOMLIST_ACK;
   }
} S_PROTOCOL_LOBBY_ROOMLIST_ACK;

struct _player_info {
   int win;
   int lose;
   char nickname[10];
};

typedef struct _PROTOCOL_LOBBY_PLAYER_LIST_REQ : _protocol {
   _header header;
   struct _player_info waitPlayers[20];
   _PROTOCOL_LOBBY_PLAYER_LIST_REQ()
   {
      header.protocolID = PROTOCOL_LOBBY_PLAYER_LIST_REQ;
   }
} S_PROTOCOL_LOBBY_PLAYER_LIST_REQ;

typedef struct _PROTOCOL_LOBBY_PLAYER_LIST_ACK : _protocol {
   _header header;
   int count;
   _player_info players[20];

   _PROTOCOL_LOBBY_PLAYER_LIST_ACK()
   {
      header.protocolID = PROTOCOL_LOBBY_PLAYER_LIST_ACK;
   }
} S_PROTOCOL_LOBBY_PLAYER_LIST_ACK;

typedef struct _PROTOCOL_ROOM_SET_READY_STATUS_REQ : _protocol {
   _header header;
   bool status;

   _PROTOCOL_ROOM_SET_READY_STATUS_REQ()
   {
      header.protocolID = PROTOCOL_ROOM_SET_READY_STATUS_REQ;
   }
} S_PROTOCOL_ROOM_SET_READY_STATUS_REQ;

typedef struct _PROTOCOL_ROOM_SET_READY_STATUS_ACK : _protocol {
   _header header;
   bool status;

   _PROTOCOL_ROOM_SET_READY_STATUS_ACK()
   {
      header.protocolID = PROTOCOL_ROOM_SET_READY_STATUS_ACK;
   }
} S_PROTOCOL_ROOM_SET_READY_STATUS_ACK;

typedef struct _PROTOCOL_ROOM_PLAYER_LIST_REQ : _protocol {
   _header header;

   _PROTOCOL_ROOM_PLAYER_LIST_REQ()
   {
      header.protocolID = PROTOCOL_ROOM_PLAYER_LIST_REQ;
   }
} S_PROTOCOL_ROOM_PLAYER_LIST_REQ;

typedef struct _PROTOCOL_ROOM_PLAYER_LIST_ACK : _protocol {
   _header header;
   int count;
   _player_info players[4];

   _PROTOCOL_ROOM_PLAYER_LIST_ACK()
   {
      header.protocolID = PROTOCOL_ROOM_PLAYER_LIST_ACK;
   }
} S_PROTOCOL_ROOM_PLAYER_LIST_ACK;

typedef struct _PROTOCOL_INGAME_LOADING_COMPLETED : _protocol {
   _header header;

   _PROTOCOL_INGAME_LOADING_COMPLETED()
   {
      header.protocolID = PROTOCOL_INGAME_LOADING_COMPLETED;
   }
} S_PROTOCOL_INGAME_LOADING_COMPLETED;

typedef struct _PROTOCOL_INGAME_START_GAME : _protocol {
   _header header;

   _PROTOCOL_INGAME_START_GAME()
   {
      header.protocolID = PROTOCOL_INGAME_START_GAME;
   }
} S_PROTOCOL_INGAME_START_GAME;

typedef struct _PROTOCOL_PLAYER_STATUS_CHANGED_REQ : _protocol {
   _header header;
   int x_coord;
   int y_coord;
   char direction;

   _PROTOCOL_PLAYER_STATUS_CHANGED_REQ()
   {
      header.protocolID = PROTOCOL_PLAYER_STATUS_CHANGED_REQ;
   }
} S_PROTOCOL_PLAYER_STATUS_CHANGED_REQ;

typedef struct _PROTOCOL_PLAYER_STATUS_CHANGED_ACK : _protocol {
   _header header;
   int userID;
   int x_coord;
   int y_coord;
   char direction;

   _PROTOCOL_PLAYER_STATUS_CHANGED_ACK()
   {
      header.protocolID = PROTOCOL_PLAYER_STATUS_CHANGED_ACK;
   }
} S_PROTOCOL_PLAYER_STATUS_CHANGED_ACK;

typedef struct _PROTOCOL_GAME_END_REQ : _protocol {
   _header header;

   _PROTOCOL_GAME_END_REQ()
   {
      header.protocolID = PROTOCOL_GAME_END_REQ;
   }
} S_PROTOCOL_GAME_END_REQ;

typedef struct _PROTOCOL_GAME_END_ACK : _protocol {
   _header header;
   int win_userID;

   _PROTOCOL_GAME_END_ACK()
   {
      header.protocolID = PROTOCOL_GAME_END_ACK;
   }
} S_PROTOCOL_GAME_END_ACK;
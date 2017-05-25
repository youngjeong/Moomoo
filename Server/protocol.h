#pragma once

enum Protocol {
   PROTOCOL_GENERAL_FAIL = 0x00000000,
   PROTOCOL_GENERAL_SUCESS = 0x00000001,

   PROTOCOL_OUTGAME = 0x000F0000,

   PROTOCOL_JOIN_REQ,
   PROTOCOL_JOIN_ACK,

   PROTOCOL_LOGIN_REQ,
   PROTOCOL_LOGIN_ACK,

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
   __int32 protocolD;
   __int32 result;
   char accessToken[16];
};

typedef struct _PROTOCOL_JOIN_REQ : _protocol {
   _header header;
   char id[16];
   char password[16];
   char nickname[16];

   _PROTOCOL_JOIN_REQ()
   {
      header.protocolD = PROTOCOL_JOIN_REQ;
   }
} S_PROTOCOL_JOIN_REQ;

typedef struct _PROTOCOL_JOIN_ACK : _protocol {
   _header header;

   _PROTOCOL_JOIN_ACK()
   {
      header.protocolD = PROTOCOL_JOIN_ACK;
   }
} S_PROTOCOL_JOIN_ACK;

typedef struct _PROTOCOL_LOGIN_REQ : _protocol {
   _header header;
   char id[16];
   char password[16];

   _PROTOCOL_LOGIN_REQ()
   {
      header.protocolD = PROTOCOL_LOGIN_REQ;
   }
} S_PROTOCOL_LOGIN_REQ;

typedef struct _PROTOCOL_LOGIN_ACK : _protocol {
   _header header;
   char accessToken[16];

   _PROTOCOL_LOGIN_ACK()
   {
      header.protocolD = PROTOCOL_LOGIN_ACK;
   }
} S_PROTOCOL_LOGIN_ACK;

struct _room_info {
   __int32 num;
   __int32 current;
   __int32 total;
};

typedef struct _PROTOCOL_LOBBY_ROOMLIST_REQ : _protocol {
   _header header;

   _PROTOCOL_LOBBY_ROOMLIST_REQ()
   {
      header.protocolD = PROTOCOL_LOBBY_ROOMLIST_REQ;
   }
} S_PROTOCOL_LOBBY_ROOMLIST_REQ;

typedef struct _PROTOCOL_LOBBY_ROOMLIST_ACK : _protocol {
   _header header;
   __int32 count;
   _room_info rooms[255];

   _PROTOCOL_LOBBY_ROOMLIST_ACK()
   {
      header.protocolD = PROTOCOL_LOBBY_ROOMLIST_ACK;
   }
} S_PROTOCOL_LOBBY_ROOMLIST_ACK;

struct _player_info {
   __int32 win;
   __int32 lose;
   char nickname[10];
};

typedef struct _PROTOCOL_LOBBY_PLAYER_LIST_REQ : _protocol {
   _header header;

   _PROTOCOL_LOBBY_PLAYER_LIST_REQ()
   {
      header.protocolD = PROTOCOL_LOBBY_PLAYER_LIST_REQ;
   }
} S_PROTOCOL_LOBBY_PLAYER_LIST_REQ;

typedef struct _PROTOCOL_LOBBY_PLAYER_LIST_ACK : _protocol {
   _header header;
   __int32 count;
   _player_info players[255];

   _PROTOCOL_LOBBY_PLAYER_LIST_ACK()
   {
      header.protocolD = PROTOCOL_LOBBY_PLAYER_LIST_ACK;
   }
} S_PROTOCOL_LOBBY_PLAYER_LIST_ACK;

typedef struct _PROTOCOL_ROOM_SET_READY_STATUS_REQ : _protocol {
   _header header;
   bool status;

   _PROTOCOL_ROOM_SET_READY_STATUS_REQ()
   {
      header.protocolD = PROTOCOL_ROOM_SET_READY_STATUS_REQ;
   }
} S_PROTOCOL_ROOM_SET_READY_STATUS_REQ;

typedef struct _PROTOCOL_ROOM_SET_READY_STATUS_ACK : _protocol {
   _header header;
   bool status;

   _PROTOCOL_ROOM_SET_READY_STATUS_ACK()
   {
      header.protocolD = PROTOCOL_ROOM_SET_READY_STATUS_ACK;
   }
} S_PROTOCOL_ROOM_SET_READY_STATUS_ACK;

typedef struct _PROTOCOL_ROOM_PLAYER_LIST_REQ : _protocol {
   _header header;

   _PROTOCOL_ROOM_PLAYER_LIST_REQ()
   {
      header.protocolD = PROTOCOL_ROOM_PLAYER_LIST_REQ;
   }
} S_PROTOCOL_ROOM_PLAYER_LIST_REQ;

typedef struct _PROTOCOL_ROOM_PLAYER_LIST_ACK : _protocol {
   _header header;
   __int32 count;
   _player_info players[4];

   _PROTOCOL_ROOM_PLAYER_LIST_ACK()
   {
      header.protocolD = PROTOCOL_ROOM_PLAYER_LIST_ACK;
   }
} S_PROTOCOL_ROOM_PLAYER_LIST_ACK;

typedef struct _PROTOCOL_INGAME_LOADING_COMPLETED : _protocol {
   _header header;

   _PROTOCOL_INGAME_LOADING_COMPLETED()
   {
      header.protocolD = PROTOCOL_INGAME_LOADING_COMPLETED;
   }
} S_PROTOCOL_INGAME_LOADING_COMPLETED;

typedef struct _PROTOCOL_INGAME_START_GAME : _protocol {
   _header header;

   _PROTOCOL_INGAME_START_GAME()
   {
      header.protocolD = PROTOCOL_INGAME_START_GAME;
   }
} S_PROTOCOL_INGAME_START_GAME;

typedef struct _PROTOCOL_PLAYER_STATUS_CHANGED_REQ : _protocol {
   _header header;
   __int32 x_coord;
   __int32 y_coord;
   __int8 direction;

   _PROTOCOL_PLAYER_STATUS_CHANGED_REQ()
   {
      header.protocolD = PROTOCOL_PLAYER_STATUS_CHANGED_REQ;
   }
} S_PROTOCOL_PLAYER_STATUS_CHANGED_REQ;

typedef struct _PROTOCOL_PLAYER_STATUS_CHANGED_ACK : _protocol {
   _header header;
   __int32 userID;
   __int32 x_coord;
   __int32 y_coord;
   __int8 direction;

   _PROTOCOL_PLAYER_STATUS_CHANGED_ACK()
   {
      header.protocolD = PROTOCOL_PLAYER_STATUS_CHANGED_ACK;
   }
} S_PROTOCOL_PLAYER_STATUS_CHANGED_ACK;

typedef struct _PROTOCOL_GAME_END_REQ : _protocol {
   _header header;

   _PROTOCOL_GAME_END_REQ()
   {
      header.protocolD = PROTOCOL_GAME_END_REQ;
   }
} S_PROTOCOL_GAME_END_REQ;

typedef struct _PROTOCOL_GAME_END_ACK : _protocol {
   _header header;
   __int32 win_userID;

   _PROTOCOL_GAME_END_ACK()
   {
      header.protocolD = PROTOCOL_GAME_END_ACK;
   }
} S_PROTOCOL_GAME_END_ACK;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace PT
{
    enum Protocol
    {
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

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    struct _header
    {
        public int protocolID;
        public int result;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string accessToken;

        public byte[] Serialize()
        {
            // allocate a byte array for the struct data
            var buffer = new byte[Marshal.SizeOf(typeof(_header))];

            // Allocate a GCHandle and get the array pointer
            var gch = GCHandle.Alloc(buffer, GCHandleType.Pinned);
            var pBuffer = gch.AddrOfPinnedObject();

            // copy data from struct to array and unpin the gc pointer
            Marshal.StructureToPtr(this, pBuffer, false);
            gch.Free();

            return buffer;
        }
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    struct S_PROTOCOL_JOIN_REQ
    {
        public _header header;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string id;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string password;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string nickname;

        public byte[] Serialize()
        {
            // allocate a byte array for the struct data
            var buffer = new byte[Marshal.SizeOf(typeof(S_PROTOCOL_JOIN_REQ))];

            // Allocate a GCHandle and get the array pointer
            var gch = GCHandle.Alloc(buffer, GCHandleType.Pinned);
            var pBuffer = gch.AddrOfPinnedObject();

            // copy data from struct to array and unpin the gc pointer
            Marshal.StructureToPtr(this, pBuffer, false);
            gch.Free();

            return buffer;
        }
    }
        
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using PT;

public class Communicator{
    private static Communicator _instance;
    public static Communicator i()
    {
        if (_instance == null) _instance = new Communicator();
        return _instance;
    }

    public void join(string id, string pw, string nickname)
    {
        S_PROTOCOL_JOIN_REQ req = new S_PROTOCOL_JOIN_REQ();
        req.header.protocolID = (int)Protocol.PROTOCOL_JOIN_REQ;
        req.id = id;
        req.password = pw;
        req.nickname = nickname;

        Network.i().send(req.Serialize(), Marshal.SizeOf(req));
    }
    
}

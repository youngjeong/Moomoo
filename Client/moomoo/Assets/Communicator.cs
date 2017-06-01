using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using UnityEngine.SceneManagement;
using PT;
using Utils;

public class Communicator{
    private static Communicator _instance;

    public CircularBuffer<object> cb;

    int userID = 0;

    private Communicator()
    {
        cb = new CircularBuffer<object>(8096);
    }

    public static Communicator I()
    {
        if (_instance == null) _instance = new Communicator();
        return _instance;
    }
    
    public void setUserID(int userID)
    {
        this.userID = userID;
    }

    public void Login(string id, string pw)
    {
        S_PROTOCOL_LOGIN_REQ req = new S_PROTOCOL_LOGIN_REQ();
        req.header.protocolID = (int)Protocol.PROTOCOL_LOGIN_REQ;
        req.id = id;
        req.password = pw;

        Network.i().send(req.Serialize(), Marshal.SizeOf(req));
    }

    public void Join(string id, string pw, string nickname)
    {
        S_PROTOCOL_JOIN_REQ req = new S_PROTOCOL_JOIN_REQ();
        req.header.protocolID = (int)Protocol.PROTOCOL_JOIN_REQ;
        req.id = id;
        req.password = pw;
        req.nickname = nickname;

        Network.i().send(req.Serialize(), Marshal.SizeOf(req));
    }
}

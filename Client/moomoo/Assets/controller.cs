using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using PT;

public class Controller : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        
        if (Communicator.I().cb.GetLength() > 0)
        {
            _header[] recv = new _header[1];
            Communicator.I().cb.Dequeue(recv);

            switch ((Protocol)recv[0].protocolID)
            {
                case Protocol.PROTOCOL_JOIN_ACK:
                    S_PROTOCOL_JOIN_ACK[] join_ack = new S_PROTOCOL_JOIN_ACK[1];
                    Communicator.I().cb.Dequeue(join_ack);
                    break;

                case Protocol.PROTOCOL_LOGIN_ACK:
                    S_PROTOCOL_LOGIN_ACK[] login_ack = new S_PROTOCOL_LOGIN_ACK[1];
                    Communicator.I().cb.Dequeue(login_ack);

                    if (login_ack[0].header.result == 0)
                    {
                        Debug.Log("SUCCESS LOGIN");
                        Communicator.I().setUserID(login_ack[0].userID);
                        SceneManager.LoadScene("Main");
                    }
                    break;
            }
        }
    }
}

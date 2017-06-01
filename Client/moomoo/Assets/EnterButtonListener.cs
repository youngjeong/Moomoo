using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EnterButtonListener: MonoBehaviour {

    public string id;
    public string pw;

    public GameObject joinPopupPanel;

    public void Login()
    {
        Communicator.I().Login(id, pw);
    }
    
    public void OpenJoinPoup()
    {
        joinPopupPanel.SetActive(true);
    }

    public void setID(string tid)
    {
        id = tid;
    }

    public void setPW(string tpw)
    {
        pw = tpw;
    }

    // Use this for initialization
    void Start()
    {
        joinPopupPanel.SetActive(false);
    }

    // Update is called once per frame
    void Update () {

    }

    void OnApplicationQuit()
    {
        Debug.Log("APP QUIT");
        Network.i().terminate();
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class JoinButtonListener: MonoBehaviour {

    public string id;
    public string nn;
    public string pw;

    public GameObject joinPopupPanel;

    public void Join()
    {
        Communicator.I().Join(id, pw, nn);
        joinPopupPanel.SetActive(false);
    }

    public void Close()
    {
        joinPopupPanel.SetActive(false);
    }

    public void setID(string tid)
    {
        id = tid;
    }

    public void setNickName(string tnn)
    {
        nn = tnn;
    }

    public void setPW(string tpw)
    {
        pw = tpw;
    }

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update () {

    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIButtonListener: MonoBehaviour {
    
    public void Login()
    {

    }

    public void Join()
    {
        Communicator.i().join("THISISTEST", "12341234", "FINN");
    }

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}

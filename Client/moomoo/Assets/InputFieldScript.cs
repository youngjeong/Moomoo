using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class InputFieldScript : MonoBehaviour {
    public InputField inputText;

    public void setText(Text text)
    {
        text.text = inputText.text;
    }

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}

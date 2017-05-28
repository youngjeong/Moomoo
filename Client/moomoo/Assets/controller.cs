using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class controller : MonoBehaviour {
    public float speed;
	// Update is called once per frame
	void Update () {
        if (Input.anyKey)
        {
            if (Input.GetKey(KeyCode.W))
            {
                transform.position = transform.position + new Vector3(0, 0, speed);
            }
            else if (Input.GetKey(KeyCode.A))
            {
                transform.position = transform.position + new Vector3(-speed, 0, 0);
            }
            else  if (Input.GetKey(KeyCode.S))
            {
                transform.position = transform.position + new Vector3(0, 0, -speed);
            }
            else if (Input.GetKey(KeyCode.D))
            {
                transform.position = transform.position + new Vector3(speed, 0, 0);
            }
        }
	}
}

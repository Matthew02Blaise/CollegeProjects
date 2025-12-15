using System.Collections;
using System.Collections.Generic;
//using UnityEditor.PackageManager;
using UnityEngine;

public class CamController : MonoBehaviour
{
    //Mouse sensitivity variables
    public float mouseSensX;
    public float mouseSensY;

    //Orientation store
    public Transform orient;

    //rotation stores
    float xRot;
    float yRot;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //Taking input
        float mouseX = Input.GetAxisRaw("Mouse X") * Time.deltaTime * mouseSensX;
        float mouseY = Input.GetAxisRaw("Mouse Y") * Time.deltaTime * mouseSensY;

        //rotating camera
        xRot -= mouseY;
        yRot += mouseX;

        //stop from looking up or down too much
        xRot = Mathf.Clamp(xRot, -90f, 90f);

        //moving camera
        transform.rotation = Quaternion.Euler(xRot, yRot, 0);
        orient.rotation = Quaternion.Euler(0, yRot, 0);
    }
}

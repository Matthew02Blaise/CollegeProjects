using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class DetectCollisions : MonoBehaviour
{
    //private float animalHunger;
   // public TextMeshProUGUI AnimalHunger;
    
    // Start is called before the first frame update
    void Start()
    {
        //SetCountText();
    }

    // Update is called once per frame
    void Update()
    {
        //animalHunger = 0;
    }

    private void OnTriggerEnter(Collider other)
    {
        //animalHunger = animalHunger + 1;
        //SetCountText();

       // if (animalHunger >= 10)
        //{
         //   Destroy(gameObject);
        //}
        Destroy(gameObject);
        Destroy(other.gameObject);
         
    }

    /*void SetCountText()
    {
        //AnimalHunger.text = "Animal Hunger: " + animalHunger.ToString() + "/10";
    }*/
}

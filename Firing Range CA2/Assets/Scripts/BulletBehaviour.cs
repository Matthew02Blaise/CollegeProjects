using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletBehaviour : MonoBehaviour
{
    Rigidbody rb;

    public int damage;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.GetComponent<TargetBehaviour>() != null)
        {
            TargetBehaviour target = collision.gameObject.GetComponent<TargetBehaviour>();

            target.TakeAHit(damage);

            Destroy(gameObject);
        }
    }
}

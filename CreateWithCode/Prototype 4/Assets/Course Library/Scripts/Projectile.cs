using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Projectile : MonoBehaviour
{
    public float projectileLifetime = 3.0f;
    public float speed = 20.0f;

    private void Start()
    {
        Destroy(gameObject, projectileLifetime);
    }

    private void Update()
    {
        transform.Translate(Vector3.forward * speed * Time.deltaTime);
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Enemy"))
        {
            Rigidbody enemyRb = other.GetComponent<Rigidbody>();
            if (enemyRb != null)
            {
                Vector3 awayFromPlayer = (other.transform.position - transform.position).normalized;
                enemyRb.AddForce(awayFromPlayer * 10f, ForceMode.Impulse);
            }

            Destroy(gameObject);
        }
    }
}

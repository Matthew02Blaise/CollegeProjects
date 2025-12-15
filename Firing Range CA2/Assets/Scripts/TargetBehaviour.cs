using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class TargetBehaviour : MonoBehaviour
{
    public int health;

    bool dead;

    private GameManager gameManager;

    public GameObject deathSound;
    public float ClipLength = 1f;

    public ParticleSystem explosionParticle;

    // Start is called before the first frame update
    void Start()
    {
        gameManager = GameObject.Find("Game Manager").GetComponent<GameManager>();
        dead = false;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void TakeAHit(int damage)
    {
        health -= damage;

        if(health < 0)
        {
            dead = true;
        }

        if(dead)
        {
            ParticleSystem explosion = Instantiate(explosionParticle, transform.position, transform.rotation);
            explosion.Play();

            // Destroy the instantiated particle system after it finishes
            Destroy(explosion.gameObject, explosion.main.duration);

            Destroy(gameObject);
            gameManager.UpdateScore(1);
            StartCoroutine(DeathSound());
            
        }
    }

    IEnumerator DeathSound()
    {
        deathSound.SetActive(true);
        yield return new WaitForSeconds(ClipLength);
        deathSound.SetActive(false);
    }
}

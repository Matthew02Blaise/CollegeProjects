using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    //original
    private Rigidbody playerRb;
    public float speed = 5.0f;
    private GameObject focalPoint;
    public bool hasPowerup;
    private float powerupStrength = 15.0f;
    public GameObject powerupIndicator;

    //projectile
    public bool hasProjectilePowerup;
    public GameObject projectilePrefab;
    public float projectileForce = 20.0f;
    public float fireRate = 1.0f;
    private float nextFireTime = 0.0f;

    //smash
    public bool hasSmashPowerup;
    public float smashForce = 200.0f;
    public float smashRadius = 100.0f;
    public float jumpHeight = 30.0f;

    // Start is called before the first frame update
    void Start()
    {
        playerRb = GetComponent<Rigidbody>();
        focalPoint = GameObject.Find("Focal Point");
    }

    // Update is called once per frame
    void Update()
    {
        float forwardInput = Input.GetAxis("Vertical");
        playerRb.AddForce(focalPoint.transform.forward * speed * forwardInput);
        powerupIndicator.transform.position = transform.position + new Vector3(0, -0.5f, 0);

        if (hasProjectilePowerup && Time.time > nextFireTime)
        {
            FireProjectiles();
            nextFireTime = Time.time + fireRate;
        }

        if (hasSmashPowerup && Input.GetKeyDown(KeyCode.Space))
        {
            StartCoroutine(Smash());
        }
    }

    void FireProjectiles()
    {
        GameObject projectile = Instantiate(projectilePrefab, transform.position + focalPoint.transform.forward * 1.5f, Quaternion.identity);

        Rigidbody projectileRb = projectile.GetComponent<Rigidbody>();

        projectileRb.velocity = focalPoint.transform.forward * projectileForce;
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.CompareTag("Powerup"))
        {
            Debug.Log("Powerup collected!");
            hasPowerup = true;
            StartCoroutine(PowerupCountdownRoutine());
            powerupIndicator.gameObject.SetActive(true);
            Destroy(other.gameObject, 0.1f);
        }

        if (other.CompareTag("ProjectilePowerup"))
        {
            Debug.Log("Projectile Powerup collected!");
            hasProjectilePowerup = true;
            StartCoroutine(ProjectilePowerupCountdownRoutine());
            powerupIndicator.gameObject.SetActive(true);
            Destroy(other.gameObject, 0.1f);
        }

        if (other.CompareTag("SmashPowerup"))
        {
            Debug.Log("Smash Powerup collected!");
            hasSmashPowerup = true;
            powerupIndicator.gameObject.SetActive(true);
            Destroy(other.gameObject);
        }
    }

     

    IEnumerator PowerupCountdownRoutine()
    {
        yield return new WaitForSeconds(7);
        hasPowerup = false;
        powerupIndicator.gameObject.SetActive(false);
    }

    IEnumerator ProjectilePowerupCountdownRoutine()
    {
        yield return new WaitForSeconds(7);
        hasProjectilePowerup = false;
    }

    IEnumerator Smash()
    {
        playerRb.AddForce(Vector3.up * jumpHeight, ForceMode.Impulse);

        yield return new WaitForSeconds(0.5f);

        playerRb.AddForce(Vector3.down * smashForce, ForceMode.Impulse);

        Collider[] enemies = Physics.OverlapSphere(transform.position, smashRadius);
        foreach (Collider enemy in enemies)
        {
            if (enemy.CompareTag("Enemy"))
            {
                Rigidbody enemyRb = enemy.GetComponent<Rigidbody>();
                Vector3 awayFromPlayer = (enemy.transform.position - transform.position).normalized;
                float proximity = 10 - (Vector3.Distance(transform.position, enemy.transform.position) / smashRadius);
                float forceToApply = smashForce * proximity;
                enemyRb.AddForce(awayFromPlayer * forceToApply, ForceMode.Impulse);
            }
        }

        hasSmashPowerup = false;
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("Enemy") && hasPowerup)
        {
            Rigidbody enemyRigidbody = collision.gameObject.GetComponent<Rigidbody>();
            Vector3 awayFromPlayer = (collision.gameObject.transform.position - transform.position);
            
            Debug.Log("Collided with" + collision.gameObject.name + " with powerup set to" + hasPowerup);
            enemyRigidbody.AddForce(awayFromPlayer * powerupStrength, ForceMode.Impulse);
        }
    }
}

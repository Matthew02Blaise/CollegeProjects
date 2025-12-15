using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shoot : MonoBehaviour
{
    public Transform cam;
    public Transform shootPoint;
    public GameObject objectToShoot;

    public int ammo;
    public float shootCooldown;

    public KeyCode shootKey = KeyCode.Mouse0;
    public float bulletForce;

    bool readyToShoot;

    //sound
    public float ClipLength = 1f;
    public GameObject AudioClip;

    // Start is called before the first frame update
    void Start()
    {
        readyToShoot = true;

        AudioClip.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(shootKey) && readyToShoot && ammo > 0)
        {
            ShootMethod();
            StartCoroutine(GunSound());
        }
    }

    private void ShootMethod()
    {
        readyToShoot = false;

        GameObject proj = Instantiate(objectToShoot, shootPoint.position, shootPoint.rotation);

        Destroy(proj, 2f);

        Rigidbody projectileRb = proj.GetComponent<Rigidbody>();

        Vector3 forceDirection = cam.transform.forward;

        RaycastHit hit;

        if(Physics.Raycast(cam.position, cam.forward, out hit, 500f))
        {
            forceDirection = (hit.point - shootPoint.position).normalized;
        }

        Vector3 forceToAdd = (forceDirection * bulletForce);

        projectileRb.AddForce(forceToAdd, ForceMode.Impulse);

        ammo--;

        Invoke(nameof(ResetShots), shootCooldown);
    }

    private void ResetShots()
    {
        readyToShoot = true;
    }

    IEnumerator GunSound()
    {
        AudioClip.SetActive (true);
        yield return new WaitForSeconds(ClipLength);
        AudioClip.SetActive(false);
    }
}

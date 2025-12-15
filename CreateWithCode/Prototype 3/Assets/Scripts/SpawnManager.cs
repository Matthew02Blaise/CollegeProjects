using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnManager : MonoBehaviour
{
    public GameObject obstaclePrefab;
    private Vector3 spawnPos = new Vector3 (25, 0, -2);
    public GameObject obstaclePrefab1;
    private Vector3 spawnPos1 = new Vector3(27, 3, -2);
    private float startDelay = 2;
    private float repeatRate = 2;
    private float startDelay1 = 3;
    private float repeatRate1 = 3;
    private PlayerController playerControllerScript;

    // Start is called before the first frame update
    void Start()
    {
        InvokeRepeating("SpawnObstacle", startDelay, repeatRate);
        InvokeRepeating("SpawnObstacle1", startDelay1, repeatRate1);
        playerControllerScript = GameObject.Find("Player").GetComponent<PlayerController>();
    }

    void SpawnObstacle()
    {
        if (playerControllerScript.gameOver == false)
        {
            Instantiate(obstaclePrefab, spawnPos, obstaclePrefab.transform.rotation);
            Instantiate(obstaclePrefab1, spawnPos1, obstaclePrefab1.transform.rotation);
        }
    }

    void SpawnObstacle1()
    {
        if (playerControllerScript.gameOver == false)
        {
            Instantiate(obstaclePrefab1, spawnPos1, obstaclePrefab1.transform.rotation);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}

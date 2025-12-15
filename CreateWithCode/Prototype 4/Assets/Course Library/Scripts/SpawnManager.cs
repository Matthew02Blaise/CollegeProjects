using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnManager : MonoBehaviour
{
    public GameObject enemyPrefab;
    public GameObject enemyStrongPrefab;
    //public GameObject bossPrefab;
    private float spawnRange = 9;
    public int enemyCount;
    public int waveNumber = 1;
    public GameObject powerupPrefab;
    public GameObject projPrefab;
    public GameObject smashPrefab;

    // Start is called before the first frame update
    void Start()
    {
        SpawnEnemyWave(waveNumber);
        Instantiate(powerupPrefab, GenerateSpawnPosition(), powerupPrefab.transform.rotation);
        Instantiate(projPrefab, GenerateSpawnPosition(), powerupPrefab.transform.rotation);
        Instantiate(smashPrefab, GenerateSpawnPosition(), powerupPrefab.transform.rotation);
    }

    void SpawnEnemyWave(int enemiesToSpawn)
    {
        for (int i = 0; i < enemiesToSpawn; i++)
        {
            if (Random.Range(0, 2) == 0)
            {
                Instantiate(enemyPrefab, GenerateSpawnPosition(), enemyPrefab.transform.rotation);
            }
            else
            {
                Instantiate(enemyStrongPrefab, GenerateSpawnPosition(), enemyStrongPrefab.transform.rotation);
            }
        }
    }

    /*IEnumerator SpawnBossWave()
    {
        Instantiate(bossPrefab, GenerateSpawnPosition(), bossPrefab.transform.rotation);
        
        int i = 0;
        while (i < 5)
        {
            yield return new WaitForSeconds(5);

            if (Random.Range(0, 2) == 0)
            {
                Instantiate(enemyPrefab, GenerateSpawnPosition(), enemyPrefab.transform.rotation);
            }
            else
            {
                Instantiate(enemyStrongPrefab, GenerateSpawnPosition(), enemyStrongPrefab.transform.rotation);
            }
            i++;
        }
    }*/

    private Vector3 GenerateSpawnPosition()
    {
        float spawnPosX = Random.Range(-spawnRange, spawnRange);
        float spawnPosZ = Random.Range(-spawnRange, spawnRange);
        Vector3 randomPos = new Vector3(spawnPosX, 0, spawnPosZ);
        return randomPos;
    }

    // Update is called once per frame
    void Update()
    {
        enemyCount = FindObjectsOfType<Enemy>().Length;
        if (enemyCount == 0 /*&& waveNumber < 3*/)
        {
            waveNumber++;
            Instantiate(powerupPrefab, GenerateSpawnPosition(), powerupPrefab.transform.rotation);
            Instantiate(smashPrefab, GenerateSpawnPosition(), powerupPrefab.transform.rotation);
            Instantiate(projPrefab, GenerateSpawnPosition(), powerupPrefab.transform.rotation);
            SpawnEnemyWave(waveNumber);
        }
       // else
       // {
            /*if (waveNumber == 3)
            {
                SpawnBossWave();
                Instantiate(powerupPrefab, GenerateSpawnPosition(), powerupPrefab.transform.rotation);
                Instantiate(smashPrefab, GenerateSpawnPosition(), powerupPrefab.transform.rotation);
                Instantiate(projPrefab, GenerateSpawnPosition(), powerupPrefab.transform.rotation);
            }
        }*/
    }
}

using System.Collections;
using System.Collections.Generic;
using TMPro;
//using UnityEditor.VersionControl;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameManager : MonoBehaviour
{
    //UI
    public TextMeshProUGUI scoreText;
    public TextMeshProUGUI timeText;
    public TextMeshProUGUI winText;
    public TextMeshProUGUI gameOverText;
    public TextMeshProUGUI startText;
    public GameObject titleScreen;
    public GameObject winScreen;
    public GameObject gameOverScreen;
    public GameObject pauseState;
    public Button restartButton;

    //Time variables
    public float gameDuration = 30.0f;
    private float timeRemaining;

    //score variable
    private int score;
    
    //game playing boolean
    public bool isGamePlaying;
    public bool isGamePaused;

    //player
    public GameObject player;
    private Rigidbody playerRb;

    // Start is called before the first frame update

    void Start()
    {
        //Initializing everything
        isGamePlaying = false;
        playerRb = player.GetComponent<Rigidbody>();
    }
    public void StartGame()
    {
        //start the gamepay
        isGamePlaying = true;
        score = 0;
        UpdateScore(0);
        titleScreen.SetActive(false);
        timeRemaining = gameDuration;

        StartCoroutine(StartText());

        //constrain mouse cursor to the game window
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
    }

    // Update is called once per frame
    void Update()
    {
        //checks if game is active
        if (isGamePlaying)
        {
            UpdateTimer();
            if (score == 16)
            {
                WinGame();
            }  
        }

        if (Input.GetKeyDown(KeyCode.Escape))
        {
            TogglePause();
        }
    }

    public void TogglePause()
    {
        isGamePaused = !isGamePaused;

        if(isGamePaused)
        {
            isGamePlaying = false;
            pauseState.SetActive(true);
            //Cursor.lockState = CursorLockMode.None;
            //Cursor.visible = true;
        }
        else
        {
            // Hide pause menu and resume time
            isGamePlaying = true;
            pauseState.SetActive(false);
            //Cursor.lockState = CursorLockMode.Locked;
            //Cursor.visible = false;
        }
    }

    public void WinGame()
    {
        Cursor.lockState = CursorLockMode.None;
        Cursor.visible = true;

        //winScreen set active
        isGamePlaying = false;
        winScreen.SetActive(true);

        //Grown back to normal!!
        Vector3 newPosition = player.transform.position;
        newPosition.y += 15.0f;
        newPosition.x = 0f;
        newPosition.z = 0f;
        player.transform.position = newPosition;
        playerRb.useGravity = false;

    }

    public void UpdateScore(int scoreToAdd)
    {
        //adds to score and outputs
        score += scoreToAdd;
        scoreText.text = "Score: " + score;
    }

    public void GameOver()
    {
        //game over baby
        Cursor.lockState = CursorLockMode.None;
        Cursor.visible = true;

        isGamePlaying = false;
        gameOverScreen.SetActive(true);
        
    }

   

    void UpdateTimer()
    {
        if (timeRemaining > 0)
        {
            timeRemaining -= Time.deltaTime;
            UpdateTimerText();

            if (timeRemaining <= 0)
            {
                GameOver();
            }
        }

        void UpdateTimerText()
        {
            timeText.text = "Time: " + Mathf.Ceil(timeRemaining);
        }
    }

    IEnumerator StartText()
    {
        startText.gameObject.SetActive(true);
        yield return new WaitForSeconds(3);
        startText.gameObject.SetActive(false);
    }
}

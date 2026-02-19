#include "stdafx.h"
#include "Engine.h"
#include "PlayableCharacter.h"

void Engine::input()
{
	

	bool exit_loop = false;
	Event event;
	Event event2;

	while (m_Window.pollEvent(event))
	{

		if (state == State::MAIN_MENU) //Input while in main menu
		{

			if (event.key.code == Keyboard::Num1)
			{
				state = State::CHAR_SELECT; //changes to character selection
			}

			if (event.key.code == Keyboard::Num2)
			{
				state = State::INSTRUCTIONS;; //changes to character selection
			}

			if (event.key.code == Keyboard::Num3)
			{
				state = State::LEADERBOARD;; //changes to character selection
			}

			if (event.key.code == Keyboard::Num4)
			{
				m_Window.close(); //Closes the game
			}
		}

		if (state == State::INSTRUCTIONS) //Input while in paused
		{
			if (event.key.code == Keyboard::Enter)
			{
				state = State::MAIN_MENU; //Returns to main menu

			}
		}

		if (state == State::LEADERBOARD) //Input while in paused
		{
			if (event.key.code == Keyboard::Escape)
			{
				state = State::MAIN_MENU; //Returns to main menu

			}
		}

		if (state == State::CHAR_SELECT) //Input while in character selection
		{
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Z) //Choose Zach
				{
					m_Type = 1;
					event.key.code = Keyboard::Num0;
					startPlaying();
				}

				if (event.key.code == Keyboard::S) //Choose Szymon
				{
					m_Type = 2;
					event.key.code = Keyboard::Num0;
					startPlaying();
				}

				if (event.key.code == Keyboard::M) //Choose Matthew
				{
					m_Type = 3;
					event.key.code = Keyboard::Num0;
					startPlaying();
				}

				if (event.key.code == Keyboard::C) //Choose Corey
				{
					m_Type = 4;
					event.key.code = Keyboard::Num0;
					startPlaying();
				}

				if (event.key.code == Keyboard::Enter) //Return to menu
				{
					event.key.code = Keyboard::Num0;
					state = State::MAIN_MENU;
				}

				if (event.key.code == Keyboard::S) //Debug to enter shop
				{
					state = State::SHOP;
				}
			}
		}

		if (state == State::PAUSED) //Input while in paused
		{

			if (event.key.code == Keyboard::R)
			{

				state = State::PLAYING; //resumes playing
			}

			if (event.key.code == Keyboard::M)
			{
				state = State::MAIN_MENU; //Returns to main menu
				exit_loop = true;

				
			}

		}

		//Shop system WIP************
		if (state == State::SHOP) //Input while in shop menu
		{
			if (event.key.code == Keyboard::Num1 && score >= 10) //Need 10 points to buy
			{
				//Increase the fire rate by 1
				fireRate++;
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num2 && score >= 20) //Need 20 points to buy
			{
				//double the clip size
				clipSize += clipSize;
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num3 && score >= 15) //Need 15 points to buy
			{
				// Increase speed
				m_Player.increaseSpeed();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num6) //Testing debug
			{
				// Increase speed
				m_Player.increaseSpeed();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num4) //continues with no power up
			{
				//exit shop
				state = State::PLAYING;
			}
		}// End lshop

		if (state == State::GAME_OVER) //closes on game over
		{
			// When in GAME_OVER, allow the player to press Enter or Esc.
			if (event.key.code == Keyboard::Return)  // Enter pressed
			{
				state = State::CAPTURE_INITIALS; // Switch to capture initials state
			}
			
		}

		//CAPTURE INISTIALS STATE================================================================
		if (state == State::CAPTURE_INITIALS)
		{
			std::string playerInitials = scoreboard.captureInitials(m_Window, scoreFont);
			if (!playerInitials.empty())
			{
				// Submit the score using the captured initials.
				scoreboard.submitScore(playerInitials, score);

				// Optionally, wait a moment before fetching updated leaderboard data.
				//sf::sleep(sf::seconds(2));

				std::string leaderboardData = scoreboard.getLeaderboardText();
				if (leaderboardData.empty() || leaderboardData == "Error fetching leaderboard!")
					leaderboardText.setString("Leaderboard unavailable. Check connection.");
				else
					leaderboardText.setString(leaderboardData);

				state = State::LEADERBOARD;
			}
		}
		//======================================================================================

		if (state == State::PLAYING) //Hanle gameplay input
		{
			bool joyMenuPressed = sf::Joystick::isButtonPressed(0, 7);

			// Handle the player quitting

				if (event.key.code==(Keyboard::Escape) || joyMenuPressed)
				{
					state = State::MAIN_MENU;
				}
		

			// Handle the player pausing

			if (event.key.code == (Keyboard::Space))
			{
				state = State::PAUSED;
			}

		
			// Reloading
			if (event.key.code == Keyboard::R)
			{
				//updating reload - changed so it reloads only the ammo that is needed, fixed issue where it reloaded double clip size
				int bulletsNeeded = clipSize - bulletsInClip;

				if (bulletsSpare >= bulletsNeeded) {
					bulletsInClip += bulletsNeeded;
					bulletsSpare -= bulletsNeeded;
				}
				else if (bulletsSpare > 0) {
					bulletsInClip += bulletsSpare;
					bulletsSpare = 0;
				}

				reloadSound.play();
				//display ammo count to hud
				std::stringstream ss;
				ss << "Ammo: " << bulletsInClip << "/" << bulletsSpare;
				m_Hud.setAmmo(ss.str());
				
			}

			// Fire a bullet
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				if (m_GameTimeTotal.asMilliseconds()
					- m_LastPressed.asMilliseconds()
					> 1000 / fireRate && bulletsInClip > 0)
				{
					// Pass the centre of the player and the centre of the crosshair
					// to the shoot function
					bullets[currentBullet].shoot(
						m_Player.getCenter().x, m_Player.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);

					currentBullet++;
					if (currentBullet > 99)
					{
						currentBullet = 0;
					}
					m_LastPressed = m_GameTimeTotal;
					shootSound.play();
					bulletsInClip--;

					//update ammo count on screen
					std::stringstream ss;
					ss << "Ammo: " << bulletsInClip << "/" << bulletsSpare;
					m_Hud.setAmmo(ss.str());
				}

			}// End fire a bullet
		}

	}	



	// Handle input specific to Player
	if (m_Player.handleInput())
	{
		// Play a jump sound
	}

}

void Engine::startPlaying()
{
	// Increase fire rate
	m_LM.setCurrentLevel(0);
	m_NewLevelRequired = true;
	state = State::PLAYING;

	//wave = 0;
	score = 0;

	// Prepare the gun and ammo for next game
	currentBullet = 0;
	bulletsSpare = 24;
	bulletsInClip = 6;
	clipSize = 6;
	fireRate = 1;

	// Reset the player's stats
	//player.resetPlayerStats();
}
#include "stdafx.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

using namespace sf;

int score = 0;
int health = 100;
int fuses = 0;


void Engine::update(float dtAsSeconds)
{
	if (m_Character1)
	{
		//Sets the center of the screen to be the player
		m_MainView.setCenter(m_Player.getCenter());
	}
	
	
	//start of a new game we will need a new level
	if (m_NewLevelRequired)
	{
		m_FusesList.clear();
		m_HealthPickupList.clear();
		m_AmmoPickupList.clear();
		loadLevel();
		m_ZombieAlien1.spawn(Vector2f(850, 100), GRAVITY, 5);
		m_ZombieAlien2.spawn(Vector2f(600, 100), GRAVITY, 6);
		m_ZombieAlien3.spawn(Vector2f(400, 100), GRAVITY, 7);
		
	}

	if (state == State::PLAYING) //While game is playing
	{
		//Check if player has died
		if (health <= 0)
		{
			state = State::GAME_OVER;
			health = 100;
			fuses = 0;
			//score = 0;
		}
		
		//Update player
		m_Player.update(dtAsSeconds, m_Type);
		Vector2f playerPosition(m_Player.getCenter());
		FloatRect pr = m_Player.getPosition();

		

		//Update enemy movement
		m_ZombieAlien1.GhostChaseMoveTo(dtAsSeconds, pr, m_ZombieAlien1.getSpeed(), m_ArrayLevel,m_LM.getLevelSize().y, m_LM.getLevelSize().x );
		m_ZombieAlien1.updateSprite(1, dtAsSeconds);

		m_ZombieAlien2.GhostChaseMoveTo(dtAsSeconds, pr, m_ZombieAlien2.getSpeed(), m_ArrayLevel, m_LM.getLevelSize().y, m_LM.getLevelSize().x);
		m_ZombieAlien2.updateSprite(2, dtAsSeconds);

		m_ZombieAlien3.GhostChaseMoveTo(dtAsSeconds, pr, m_ZombieAlien3.getSpeed(), m_ArrayLevel, m_LM.getLevelSize().y, m_LM.getLevelSize().x);
		m_ZombieAlien3.updateSprite(3, dtAsSeconds);

		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when Enemy is touching the home tile
		if  (detectCollisions(m_Player) && m_LM.getCurrentLevel() == 1 && fuses >= 3 || 
			detectCollisions(m_Player) && m_LM.getCurrentLevel() == 2 && fuses >= 6)
		{
			// New level required
			m_NewLevelRequired = true;

		}
		else
		{
			// Run Players and enemies collision detection
			detectCollisions(m_Player);
			if (m_ZombieAlien1.isActive())
			{
				detectCollisions(m_ZombieAlien1);
			}
			if (m_ZombieAlien2.isActive())
			{
				detectCollisions(m_ZombieAlien2);
			}
			if (m_ZombieAlien3.isActive())
			{
				detectCollisions(m_ZombieAlien3);
			}
		}

		//Back to menu when you beat the game
		if (detectCollisions(m_Player) && m_LM.getCurrentLevel() == 3 && fuses >= 9)
		{
			state = State::GAME_OVER;
			fuses = 0;
		}

		//Check if player is invincible
		if (m_Invincible)
		{
			m_InvincibleTime -= dtAsSeconds;
			if (m_InvincibleTime <= 0)
			{
				m_Invincible = false;
				m_InvincibleTime = INVINCIBILITY_DURATION;
			}
		}

		//Check list of fuses to see if they intersect with Pacman
		//if they intersect erase the fuse from the list
		std::list<PlayableCharacter>::iterator it;

		std::list<PlayableCharacter>::iterator itH;

		std::list<PlayableCharacter>::iterator itA;
		
		for (it = m_FusesList.begin(); it != m_FusesList.end();) {  //Update fuses
			if (m_Player.getPosition().intersects ((it)->getPosition()))
			{
				
				//calculate distance d between the 2 points
				//if distance is less than 30 pixels remove the fuse
				int x1 = m_Player.getPosition().left;
				int y1 = m_Player.getPosition().top;
				int x2 = (it)->getPosition().left;
				int y2 = (it)->getPosition().top;
				int xsquared = (x2 - x1) * (x2 - x1);
				int ysquared = (y2 - y1) * (y2 - y1);
				double d = sqrt(xsquared+ysquared);

				if (d < 30)
				{
					//adds fuse to inventory
					m_FusesList.erase(it++);
					fuses++;
					score++;
					cout << fuses << endl;
					std::stringstream ss;
					ss << "Fuses: " << fuses;
					m_Hud.setFuse(ss.str());
				}
				else
				{
					++it;
				}

				pickupSound.play();
			}
			else
			{
				++it;
			}

		}

		for (itH = m_HealthPickupList.begin(); itH != m_HealthPickupList.end();) {  //Update health pickup
			if (m_Player.getPosition().intersects((itH)->getPosition()))
			{

				//calculate distance d between the 2 points
				//if distance is less than 30 pixels remove the fuse
				int x1 = m_Player.getPosition().left;
				int y1 = m_Player.getPosition().top;
				int x2 = (itH)->getPosition().left;
				int y2 = (itH)->getPosition().top;
				int xsquared = (x2 - x1) * (x2 - x1);
				int ysquared = (y2 - y1) * (y2 - y1);
				double d = sqrt(xsquared + ysquared);

				if (d < 30)
				{
					//added health update - refills health by 50
					m_HealthPickupList.erase(itH++);
					if (health > 50)
					{
						health = 100;
						std::stringstream ss;
						ss << "Health: " << health;
						m_Hud.setHealth(ss.str());
					}
					else if (health <= 50)
					{
						health = health + 50;
						std::stringstream ss;
						ss << "Health: " << health;
						m_Hud.setHealth(ss.str());
					}

				}
				else
				{
					++itH;
				}

				pickupSound.play();
			}
			else
			{
				++itH;
			}

		}

		for (auto itA = m_AmmoPickupList.begin(); itA != m_AmmoPickupList.end();) {  //Update ammo pickup
			if (m_Player.getPosition().intersects((itA)->getPosition()))
			{

				//calculate distance d between the 2 points
				//if distance is less than 30 pixels remove the fuse
				int x1 = m_Player.getPosition().left;
				int y1 = m_Player.getPosition().top;
				int x2 = (itA)->getPosition().left;
				int y2 = (itA)->getPosition().top;
				int xsquared = (x2 - x1) * (x2 - x1);
				int ysquared = (y2 - y1) * (y2 - y1);
				double d = sqrt(xsquared + ysquared);

				

				if (d < 50 && !m_Invincible)
				{
					//ammo update on pickup - adds to ammo stockpile
					bulletsSpare = bulletsSpare + 16;
					//debug
					cout << bulletsSpare << endl;

					//update hud element
					std::stringstream ss;
					ss << "Ammo: " << bulletsInClip << "/" << bulletsSpare;
					m_Hud.setAmmo(ss.str());

					m_AmmoPickupList.erase(itA++);
					std::cout << "Pickup erased, iterator advanced." << std::endl;


					m_Invincible = true;
					m_InvincibleTime = INVINCIBILITY_DURATION;
				}
				else
				{
					++itA;
				}

				pickupSound.play();
			}
			else
			{
				++itA;
			}

		}
        //Dec 9th 2021 Desmond's Death Detection code and animation
		if ((m_Player.getPosition().intersects(m_ZombieAlien1.getPosition()) && m_ZombieAlien1.isActive()) || 
			(m_Player.getPosition().intersects(m_ZombieAlien2.getPosition()) && m_ZombieAlien2.isActive()) || 
			(m_Player.getPosition().intersects(m_ZombieAlien3.getPosition())) && m_ZombieAlien3.isActive())
		{
			m_Player.setSpriteFromSheet(sf::IntRect{ 12,622,550,50 });
			m_Player.moveTextureRect(dtAsSeconds);
			health--;
			std::stringstream ss;
			ss << "Health: " << health;
			m_Hud.setHealth(ss.str());

			playerHurtSound.play();
		}

		//BULLET COLLISION WIP**************** - Matthew
		for (int i = 0; i <= 100; i++) 
		{
			//Check if active bullets have collided with enemies
			if (bullets[i].isInFlight()) 
			{
				bullets[i].update(dtAsSeconds);
				if (bullets[i].getPosition().intersects(m_ZombieAlien1.getPosition()) && m_ZombieAlien1.isActive())
				{
					bullets[i].stop();
					score++;
					m_ZombieAlien1.gotShot();
					std::stringstream ss;
					ss << "Score = " << score;
					m_Hud.setScore(ss.str());

					enemyHurtSound.play();
				}
				else if (bullets[i].getPosition().intersects(m_ZombieAlien2.getPosition()) && m_ZombieAlien2.isActive())
				{
					bullets[i].stop();
					score++;
					m_ZombieAlien2.gotShot();
					std::stringstream ss;
					ss << "Score = " << score;
					m_Hud.setScore(ss.str());

					enemyHurtSound.play();
				}
				else if (bullets[i].getPosition().intersects(m_ZombieAlien3.getPosition()) && m_ZombieAlien3.isActive())
				{
					bullets[i].stop();
					score++;
					m_ZombieAlien3.gotShot();
					std::stringstream ss;
					ss << "Score = " << score;
					m_Hud.setScore(ss.str());

					enemyHurtSound.play();
				}
			}
		}

	}// End if playing
	
	//HUD Update
	m_FramesSinceLastHUDUpdate++;

	// Update the HUD every m_TargetFramesPerHUDUpdate frames
	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate)
	{
		// Update game HUD text
		stringstream ssLevel;

		// Update the level text
		ssLevel << "Level:" << m_LM.getCurrentLevel();
		m_Hud.setLevel(ssLevel.str());

		m_FramesSinceLastHUDUpdate = 0;
	}

}
// Pong.cpp : Defines the entry point for the console application.
//

#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
//added for sound*****************88
#include <SFML/Audio.hpp>
#include <iostream>


int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game

	RenderWindow window(vm, "Pong", Style::Fullscreen);

	// MENU BOOLEAN ************************************
	bool menu = true;
	bool highScore = false;
	bool acceptInput = false;
	bool paused = false;

	// MENU TEXT ***************************************
	sf::Text menuText1;
	sf::Text menuText2;
	sf::Text menuText3;
	sf::Text menuText4;

	// LEADERBOARD TEXT ***************************************
	sf::Text leaderboardText1;
	sf::Text leaderboardText2;
	sf::Text leaderboardText3;
	sf::Text leaderboardText4;

	int score = 0;
	int lives = 3;

	// TIME BAR**************************************8
	/*Clock clock;

	RectangleShape timeBar;
	float timeBarStartWidth = 200;
	float timeBarHeight = 60;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
	*/

	// BACKGROUND ADDED **********************************
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/newBackground.jpg");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	// Create a bat
	Bat bat(1920 / 2, 1080 - 20);

	// We will add a ball in the next chapter
	Ball ball(1920 / 2, 0, 800);

	// Create a Text object called HUD
	Text hud;

	// A cool retro-style font
	Font font;
	font.loadFromFile("fonts/DS-DIGI.ttf");

	// FONT FOR MAIN MENU*************************************
	menuText1.setFont(font);
	menuText2.setFont(font);
	menuText3.setFont(font);
	menuText4.setFont(font);

	menuText1.setCharacterSize(100);
	menuText2.setCharacterSize(100);
	menuText3.setCharacterSize(100);
	menuText4.setCharacterSize(100);

	menuText1.setString("Main Menu");
	menuText2.setString("Play Game - Press enter");
	menuText3.setString("Leaderboard - Press 1");
	menuText4.setString("Exit Game - Press escape");

	//LEADERBOARD TEXT************************8
	leaderboardText1.setFont(font);
	leaderboardText2.setFont(font);
	leaderboardText3.setFont(font);
	leaderboardText4.setFont(font);

	leaderboardText1.setCharacterSize(100);
	leaderboardText2.setCharacterSize(100);
	leaderboardText3.setCharacterSize(100);
	leaderboardText4.setCharacterSize(100);

	leaderboardText1.setString("PLACEHOLDER");
	leaderboardText2.setString("PLACEHOLDER");
	leaderboardText3.setString("PLACEHOLDER");
	leaderboardText4.setString("PLACEHOLDER");

	//SOUND******************************
	SoundBuffer ballBuffer;
	ballBuffer.loadFromFile("sound/ball.wav");
	Sound ballSound;
	ballSound.setBuffer(ballBuffer);

	// Set the font to our retro-style
	hud.setFont(font);

	// Make it nice and big
	hud.setCharacterSize(75);

	// Choose a color
	hud.setFillColor(Color::White);

	hud.setPosition(20, 20);

	// Here is our clock for timing everything
	Clock clock;

	while (window.isOpen())
	{
		/*
		Handle the player input
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/

		//SETTING POSITION OF MENU********************************8
		FloatRect textRect = menuText1.getLocalBounds();
		menuText1.setOrigin(textRect.left +
			textRect.width / 2.0f,
			textRect.top +
			textRect.height / 2.0f);

		menuText1.setPosition(1920 / 2.0f, 1080 / 3.0f);

		FloatRect textRect1 = menuText2.getLocalBounds();
		menuText2.setOrigin(textRect.left +
			textRect1.width / 2.0f,
			textRect1.top +
			textRect1.height / 2.0f);

		menuText2.setPosition(1920 / 2.1f, 1080 / 2.2f);

		/*FloatRect textRect2 = menuText3.getLocalBounds();
		menuText3.setOrigin(textRect.left +
			textRect2.width / 2.0f,
			textRect2.top +
			textRect2.height / 2.0f);

		menuText3.setPosition(1920 / 2.1f, 1080 / 1.7f);*/

		FloatRect textRect3 = menuText4.getLocalBounds();
		menuText4.setOrigin(textRect.left +
			textRect3.width / 2.0f,
			textRect3.top +
			textRect3.height / 2.0f);

		menuText4.setPosition(1920 / 2.1f, 1080 / 1.7f);

		//SETTING POSITION OF LEADERBOARD********************************8
		/*FloatRect textRect4 = leaderboardText1.getLocalBounds();
		leaderboardText1.setOrigin(textRect4.left +
			textRect4.width / 2.0f,
			textRect4.top +
			textRect4.height / 2.0f);

		leaderboardText1.setPosition(1920 / 2.0f, 1080 / 3.0f);

		FloatRect textRect5 = leaderboardText2.getLocalBounds();
		leaderboardText2.setOrigin(textRect5.left +
			textRect5.width / 2.0f,
			textRect5.top +
			textRect5.height / 2.0f);

		leaderboardText2.setPosition(1920 / 2.1f, 1080 / 2.2f);

		FloatRect textRect6 = leaderboardText3.getLocalBounds();
		leaderboardText3.setOrigin(textRect6.left +
			textRect6.width / 2.0f,
			textRect6.top +
			textRect6.height / 2.0f);

		leaderboardText3.setPosition(1920 / 2.1f, 1080 / 1.7f);

		FloatRect textRect7 = leaderboardText4.getLocalBounds();
		leaderboardText4.setOrigin(textRect7.left +
			textRect7.width / 2.0f,
			textRect7.top +
			textRect7.height / 2.0f);

		leaderboardText4.setPosition(1920 / 2.1f, 1080 / 1.3f);*/

		//CHANGED EVENT TO MAKE MAIN MENU*************************************8
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;
			}
		}

		if (menu)
		{
			window.draw(menuText1);
			window.draw(menuText2);
			//window.draw(menuText3);
			window.draw(menuText4);

			window.display();
		}

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//LEADERBOARD**********************
		/*if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			highScore = true;
			menu = false;
		}

		if (highScore)
		{
			window.draw(leaderboardText1);
			window.draw(leaderboardText2);
			window.draw(leaderboardText3);
			window.draw(leaderboardText4);

			window.display();
		}*/

		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			menu = false;
			//highScore = false;

			acceptInput = true;
		}

		if (acceptInput)
		{
			//TIME BAR CODE**********************8
			/*timeRemaining = 6;
			timeRemaining += (2 / 1) + .15;
			*/
			
			// Handle the pressing and releasing of the arrow keys
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				bat.moveLeft();
			}
			else
			{
				bat.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				bat.moveRight();
			}
			else
			{
				bat.stopRight();
			}


			/*
			Update the bat, the ball and the HUD
			*********************************************************************
			*********************************************************************
			*********************************************************************
			*/
			// Update the delta time
			Time dt = clock.restart();
			bat.update(dt);
			ball.update(dt);
			// Update the HUD text
			std::stringstream ss;
			ss << "Score:" << score << "    Lives:" << lives;
			hud.setString(ss.str());

			/*
			Time dt1 = clock.restart();

			// Subtract from the amount of time remaining
			timeRemaining -= dt1.asSeconds();
			// size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond *
				timeRemaining, timeBarHeight));
				*/

			// Handle ball hitting the bottom
			if (ball.getPosition().top > window.getSize().y)
			{
				// reverse the ball direction
				ball.reboundBottom();

				// Remove a life
				lives--;

				// Check for zero lives
				if (lives < 1) {
					// reset the score
					score = 0;
					// reset the lives
					lives = 3;

					//clear w
				}

			}

			// Handle ball hitting top
			if (ball.getPosition().top < 0)
			{
				ball.reboundBatOrTop();

				// Add a point to the players score
				score++;

				//sound****************888
				ballSound.play();
			}

			// Handle ball hitting sides
			if (ball.getPosition().left < 0 ||
				ball.getPosition().left + 10 > window.getSize().x)
			{
				ball.reboundSides();

				//sound*******************
				ballSound.play();
			}

			// Has the ball hit the bat?
			if (ball.getPosition().intersects(bat.getPosition()))
			{
				// Hit detected so reverse the ball and score a point
				ball.reboundBatOrTop();

				//sound*******88
				ballSound.play();
			}
		
			/*
			Draw the bat, the ball and the HUD
			*********************************************************************
			*********************************************************************
			*********************************************************************
			*/
			window.clear();
			// DRAW BACKGROUND ADDED ****************
			window.draw(spriteBackground);
			window.draw(hud);
			window.draw(bat.getShape());
			window.draw(ball.getShape());
			//window.draw(timeBar);
			window.display();

		}
	}

	return 0;
}
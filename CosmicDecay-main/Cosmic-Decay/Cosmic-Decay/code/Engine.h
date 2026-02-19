#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureHolder.h"
#include "Enemy.h"
#include "Player.h"
#include "Arm.h"
#include "Bullet.h"
#include "Fuses.h"
#include "HealthPickup.h"
#include "AmmoPickup.h"
#include <list>
#include <math.h>
#include "LevelManager.h"
#include "Arm.h"
#include "HUD.h"
#include "Shuttle.h"
#include "ScoreBoard.h"
#include <iostream>
#include <fstream>
using namespace std;

using namespace sf;

class Engine
{
private:
	//Level manager object
	LevelManager m_levelManager;

	//Score text
	sf::Text scoreText;
	//Score font holder
	sf::Font scoreFont;

	//Variable for score
	int score;          

	//Ammo text and font holder
	sf::Text ammoText;
	sf::Font ammoFont;

	//Sound
	SoundBuffer shootBuffer;
	Sound shootSound;

	SoundBuffer reloadBuffer;
	Sound reloadSound;

	SoundBuffer reachedGoalBuffer;
	Sound reachedGoalSound;

	SoundBuffer pickupBuffer;
	Sound pickupSound;

	SoundBuffer playerHurtBuffer;
	Sound playerHurtSound;

	SoundBuffer enemyHurtBuffer;
	Sound enemyHurtSound;
	

	//Bullet object array and variables for ammo and fire rate
	Bullet bullets[100];
	int currentBullet;
	int bulletsSpare;
	int bulletsInClip;
	int clipSize;
	float fireRate;

	// The texture holder
	TextureHolder th;

	// Enemy and his friend, Player
	Enemy m_ZombieAlien1;
	Player m_Arm;
	Player m_Player;
	Enemy m_ZombieAlien2;
	Enemy m_ZombieAlien3;

	Shuttle m_shuttle;

	int m_Type;

	ScoreBoard scoreboard;

	// A class to manage all the levels
	LevelManager m_LM;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	// The force pushing the characters down
	const int GRAVITY = 0;

	// A regular RenderWindow
	RenderWindow m_Window;

	// The main Views
	View m_MainView;


	// Three views for the background
	View m_BGMainView;


	View m_HudView;

	// Declare a sprite and a Texture for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	Sprite spriteMainMenu;
	Texture textureMainMenu;
	Sprite spriteInstructions;
	Texture textureInstructions;

	//font holder and text objects for menus
	Font font;
	Text mainMenuText;
	Text charSelectText;
	Text pauseMenuText;
	Text leaderboardText;
	Text leaderboardHeadingText;
	Text leaderboardReturnText;
	Text returnMenuText;

	Text shopText;

	// Is the game currently playing?
	bool m_Playing = false;

	// Is character 1 or 2 the current focus?
	bool m_Character1 = true;

	// Start in full screen mode
	bool m_SplitScreen = false;

	// How much time is left in the current level
	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;
	Time m_LastPressed;

	// Is it time for a new/first level?
	bool m_NewLevelRequired = true;

	// The vertex array for the level design
	VertexArray m_VALevel;

	// The 2d array with the map for the level
	// A pointer to a pointer
	int** m_ArrayLevel = NULL;
	int** m_ArraySpawningPointsLevel = NULL;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	Sprite spriteCrosshair;
	Texture textureCrosshair;

	// Is player Invincible
	bool m_Invincible = false;
	//Invincibility timer
	float m_InvincibleTime;
	const float INVINCIBILITY_DURATION = 2.0f;

	//a list of fuses
	std::list<PlayableCharacter> m_FusesList;

	std::list<PlayableCharacter> m_HealthPickupList;

	std::list<PlayableCharacter> m_AmmoPickupList;

	// Texture for the background and the level tiles
	Texture m_TextureTiles;
	
	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();	

	// Load a new level
	void loadLevel();

	// Run will call all the private functions
	bool detectCollisions(PlayableCharacter& character);

	//HUD
	Hud m_Hud;

	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 500;

	
	
public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

	void startPlaying();

	//state holders, orders load order of states
	enum class State { PAUSED, GAME_OVER, PLAYING, MAIN_MENU, CHAR_SELECT, SHOP, LEADERBOARD, CAPTURE_INITIALS, INSTRUCTIONS};
	State state = State::GAME_OVER;

};
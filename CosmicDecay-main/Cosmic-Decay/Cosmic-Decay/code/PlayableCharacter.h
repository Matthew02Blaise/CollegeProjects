#pragma once
#include <SFML/Graphics.hpp>
#include "LevelManager.h"
#include <SFML/Window/Joystick.hpp>
#include <iostream>;


using namespace sf;

class PlayableCharacter
{
protected:
	// Of course we will need a sprite
	Sprite m_Sprite;
	Sprite m_SpriteSheet;

	// How long does a jump last
	float m_JumpDuration;

	// Is character currently jumping or falling
	bool m_IsJumping;
	bool m_IsFalling;

	// Which directions is the character currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;

	//2020 nov 5th up and down movement 
	bool m_UpPressed;
	bool m_DownPressed;

	// How long has this jump lasted so far
	float m_TimeThisJump;

	// Has the player just initialted a jump
	bool m_JustJumped = false;

	// Is the character Active
	bool m_Active;

	//which direction is the character headed? used to see if we need to reset the animation to first frame as we have changed direction
	sf::Vector2f direction{ 0, 1 }; //default value is left

	// What is the gravity
	float m_Gravity;

	// How much health does the character have?
	float m_Health;

	// How fast is the character
	float m_Speed = 400;

	// Where is the player 
	Vector2f m_Position;

	//destination coords
	Vector2f m_Dest_Coords{ 0,0 };

	//moving boolean value
	bool m_Moving = false;

	String m_Name;


	// Where are the characters various body parts?
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	// And a texture
	Texture m_Texture;

	sf::Vector2i sheetCoordinate; // Coordinate on spritesheet
	sf::Vector2i spriteSize;
	bool alive{ true };
	int animation_it_limit; //Max animation iterations
	bool horizontal{ true };
	int ani_counter{};
	int counter{};
	Clock clock;
	float timeElapsed;
	//50 ms for each frame

	float animationTimer=0;

	// Private variables and functions come next
private:


	// All our public functions will come next
public:

	void spawn(Vector2f startPosition, float gravity, int m_type);

	void setSpeed(float value);
	float getSpeed();

	//setSprite to use correct animation cell
	void setSpriteFromSheet(sf::IntRect textureBox);

	//move the rectangle to the next cell in the animation
	void virtual moveTextureRect(float timeElapsed);



	bool virtual handleInput();
	// This class is now abstract and cannot be instanciated

	// Where is the player
	FloatRect getPosition();

	// A rectangle representing the position of different parts of the sprite
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();

	// Send a copy of the sprite to main
	Sprite getSprite();
	Sprite getSpriteFromSheet();

	// Make the character stand firm
	void stopDown(float position);
	void stopUp(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	// Where is the center of the character
	Vector2f getCenter();

	// We will call this function once every frame
	void virtual update(float elapsedTime, int m_type);
	void moveToFR(float elapsedTime, FloatRect playerLocation, float speed, int** map_ArrayLevel);
	void GhostChaseMoveTo(float elapsedTime, FloatRect playerLocation, float speed, int** map_ArrayLevel, int levelRows, int LevelCols);
	void updateLeftRightHeadFeet();
	void setName(String id);
	String getName();
};

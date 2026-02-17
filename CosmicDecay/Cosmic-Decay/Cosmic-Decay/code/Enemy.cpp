#include "stdafx.h"
#include "Enemy.h"
#include "TextureHolder.h"

Enemy::Enemy()
{
	// Associate a texture with the sprite, this will be changed later
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/e1.png"));

	m_JumpDuration = .45;
}

//Sets the sprite for the enemy
void Enemy::setSprite(int e_type)
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/enemy1SpritesheetSmll.png"));
	// Associate a texture with the sprite
	if (e_type == 1)
	{
		//ZombieAlien1
		m_Sprite.setTextureRect(sf::IntRect{ 0, 0, 150, 50 });
	}
	else if (e_type == 2)
	{
		//ZombieAlien2
		m_Sprite.setTextureRect(sf::IntRect{ 0, 50, 150, 50 });
	}
	else if (e_type == 3)
	{
		//ZombieAlien3
		m_Sprite.setTextureRect(sf::IntRect{ 0, 100, 150, 50 });
	}
	else if (e_type == 4)
	{
		//Clyde Orange
		m_Sprite.setTextureRect(sf::IntRect{ 0, 100, 150, 50 });
	}

	m_JumpDuration = .45;
}

//Updates the sprite position and animation
void Enemy::updateSprite(int e_type, float timeElapsed)
{
	int offset=0;
	//up
	if (direction == sf::Vector2f(1, 0))
	{
		offset = 0;
	}

	//down
	if (direction == sf::Vector2f(-1, 0))
	{
		offset = 0;
	}

	//left
	if (direction == sf::Vector2f(0, 1))
	{
		offset = 0;
	}

	//right
	if (direction == sf::Vector2f(0, -1))
	{
		offset = 50;
	}

	if (e_type == 1) //ZombieAlien1
	{

		setSpriteFromSheet(sf::IntRect{ 0+ offset, 0, 150, 50 });
		moveTextureRect(timeElapsed);
	}
	else if (e_type == 2) //ZombieAlien2
	{
		setSpriteFromSheet(sf::IntRect{ 0 + offset, 50, 150, 50 });
		moveTextureRect(timeElapsed);
	}
	else if (e_type == 3) //ZombieAlien3
	{

		setSpriteFromSheet(sf::IntRect{ 0 + offset, 100, 150, 50 });
		moveTextureRect(timeElapsed);
	}
	else
	{
		setSpriteFromSheet(sf::IntRect{ 0 + offset, 0, 150, 50 });
		moveTextureRect(timeElapsed);
	}



	m_Sprite.setPosition(m_Position);
}

//Handles the animation in spritesheet
void Enemy::moveTextureRect(float timeElapsed)
{
	// if the animation counter is greater than the animation limit reset to 0
	if (ani_counter == animation_it_limit)
	{
		ani_counter = 0;
	}

	if (horizontal) {
		// Move the texture rectangle horizontally
		m_Sprite.setTextureRect(sf::IntRect(
			sheetCoordinate.x + ani_counter * spriteSize.x,
			sheetCoordinate.y,
			spriteSize.x,
			spriteSize.y
		));
	}
	else {
		// Move the texture rectangle vertically
		m_Sprite.setTextureRect(sf::IntRect(
			sheetCoordinate.x,
			sheetCoordinate.y + ani_counter * spriteSize.y,
			spriteSize.x,
			spriteSize.y
		));
	}

	//increment animation counter to point to the next frame
	double timePerFrame;
	timePerFrame = 1.0 / 4.0;
	animationTimer = animationTimer + timeElapsed;
	if (animationTimer > timePerFrame)
	{
		ani_counter++;
		animationTimer = 0;
	}

	//cout << "Animation Counter: " << ani_counter << std::endl;
	//cout << "Current Texture Rect: " << m_Sprite.getTextureRect().left << ", " << m_Sprite.getTextureRect().top << std::endl;
}

//Handles the enemy getting shot
void Enemy::gotShot()
{
	//cout << "Shot!" << endl;
	m_Health--;
	//cout << "Health: " << m_Health;
	if (m_Health <= 0)
	{
		m_Active = false;
	}
}

//returns wether enemy is alive.
bool Enemy::isActive()
{
	return m_Active;
}


// A virtual function
bool Enemy::handleInput()
{
	
	m_JustJumped = false;

	return m_JustJumped;

}
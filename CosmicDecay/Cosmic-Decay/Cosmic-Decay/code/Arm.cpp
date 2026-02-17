#include "Arm.h"
#include "Engine.h"
#include "TextureHolder.h"

Arm::Arm()
{

	// Associate a texture with the sprite
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/playerSpriteSheet2.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 0, 0, 0, 0 });

	m_Sprite.setOrigin(0, 0);
}


//returns the position of the sprite
FloatRect Arm::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

//Sets the position of the sprite
void Arm::setPosition(sf::Vector2f position) 
{
	m_Sprite.setPosition(position);
}

//Used to rotate the sprite
void Arm::setRotation(float angle) 
{
	m_Sprite.setRotation(angle);
}


//Finds the mouse and rotates the sprite towards the mouse
void Arm::rotateTowardsMouse(sf::Vector2f playerPosition, sf::RenderWindow& window)
{
	// Get the current mouse position relative to the window
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos);

	// Calculate the angle between the player position and the mouse position
	float dx = mouseWorldPos.x - playerPosition.x;
	float dy = mouseWorldPos.y - playerPosition.y;
	float angle = std::atan2(dy, dx) * 180 / 3.14159f;

	// Rotate the arm sprite
	m_Sprite.setRotation(angle);
}



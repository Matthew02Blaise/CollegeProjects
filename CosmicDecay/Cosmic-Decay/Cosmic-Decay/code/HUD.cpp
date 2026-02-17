#include "Hud.h"

Hud::Hud()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Load the font
	m_Font.loadFromFile("fonts/KOMIKAP_.ttf");

	// Position the text
	FloatRect textRect = m_StartText.getLocalBounds();

	m_StartText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	m_StartText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);

	

	//Ammo
	m_AmmoText.setFont(m_Font);
	m_AmmoText.setCharacterSize(40);
	m_AmmoText.setFillColor(Color::Black);
	m_AmmoText.setPosition(resolution.x - 250, 50);
	m_AmmoText.setString("Ammo: 6/24");

	//Health
	m_HealthText.setFont(m_Font);
	m_HealthText.setCharacterSize(40);
	m_HealthText.setFillColor(Color::Black);
	m_HealthText.setPosition(resolution.x - 250, 0);
	m_HealthText.setString("Health: 100");

	//Fuse
	m_FuseText.setFont(m_Font);
	m_FuseText.setCharacterSize(40);
	m_FuseText.setFillColor(Color::Black);
	m_FuseText.setPosition(resolution.x - 250, 100);
	m_FuseText.setString("Fuses: 0");

	// Level
	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(40);
	m_LevelText.setFillColor(Color::Black);
	m_LevelText.setPosition(resolution.x - 1900, 0);
	m_LevelText.setString("1");

	//Score
	m_ScoreText.setFont(m_Font);
	m_ScoreText.setCharacterSize(40);
	m_ScoreText.setFillColor(Color::Black);
	m_ScoreText.setPosition(resolution.x - 1900, 100);
	m_ScoreText.setString("Score: 0");

	//Background
	hudBackground.setSize(sf::Vector2f(400, 150));
	hudBackground.setPosition(resolution.x - 300, 0);
	hudBackground.setFillColor(sf::Color(255, 255, 255, 120));

	//Background 2
	hudBackground2.setSize(sf::Vector2f(250, 150));
	hudBackground2.setPosition(resolution.x - 1920, 0);
	hudBackground2.setFillColor(sf::Color(255, 255, 255, 120));
}

//Returns the start text
Text Hud::getMessage()
{
	return m_StartText;
}

//Returns the level text
Text Hud::getLevel()
{
	return m_LevelText;
}

//Returns the ammo text
Text Hud::getAmmo()
{
	return m_AmmoText;
}

//Returns the health text
Text Hud::getHealth()
{
	return m_HealthText;
}

//returns score text
Text Hud::getScore()
{
	return m_ScoreText;
}

//Returns fuse text
Text Hud::getFuse()
{
	return m_FuseText;
}

//returns the background hud 1
RectangleShape Hud::getBackground()
{
	return hudBackground;
}

//returns the background hud 2
RectangleShape Hud::getBackground2()
{
	return hudBackground2;
}

//Updates the level text 
void Hud::setLevel(String text)
{
	m_LevelText.setString(text);
}

//Updates the ammo text
void Hud::setAmmo(String text)
{
	m_AmmoText.setString(text);
}

//Updates the health text
void Hud::setHealth(String text)
{
	m_HealthText.setString(text);
}

//Updates the score text
void Hud::setScore(String text)
{
	m_ScoreText.setString(text);
}

//Updates the start text
void Hud::setStart(String text)
{
	m_StartText.setString(text);
}

//Updates the fuse text
void Hud::setFuse(String text)
{
	m_FuseText.setString(text);
}
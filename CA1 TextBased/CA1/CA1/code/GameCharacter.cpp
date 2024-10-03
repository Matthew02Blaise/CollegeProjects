#include "GameCharacter.h"
#include <iostream>

void GameCharacter::spawn(std::string id, int health, int speed, int x, int y)
{
	m_typeID = id;
	m_health = health;
	m_speed = speed;
	m_x = x;
	m_y = y;
}// create an object

void GameCharacter::render()
{
	cout << "Id: " << m_typeID << "\n" << "Position on map: " << m_x << "," << m_y <<endl;
} // print to the screen the typeID and its x and y coords

void GameCharacter::update() {} //virtual function

void GameCharacter::stats()
{
	cout << "Id: " << m_typeID << "\n" << "Health: " << m_health << "\n" << "Speed: " << m_speed << "\n" << "Position: " << m_x << ", " << m_y << endl;
}// print all stats relating to the object

bool GameCharacter::isAlive()
{
	if (m_health > 0)
	{
		return true;
	}
}//return true if its health is greater than 0

//getting position
int GameCharacter::getXPOS()
{
	return m_x;
}

int GameCharacter::getYPOS()
{
	return m_y;
}

//getting hp
int GameCharacter::getHP()
{
	return m_health;
}

//get id
string GameCharacter::getID()
{
	return m_typeID;
}

//set hp (used to kill characters)
void GameCharacter::setHP(int health)
{
	m_health = health;
}
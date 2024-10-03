#pragma once
#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class GameCharacter
{
public:
	void spawn(std::string typeID, int health, int speed, int x, int y); // create an object

	void render(); // print to the screen the typeID and its x and y coords

	virtual void update(); //virtual function

	void stats(); // print all stats relating to the object

	bool isAlive(); //return true if its health is greater than 0

	//new functions
	int getXPOS();

	int getYPOS();

	int getHP();

	string getID();

	void setHP(int health);

protected:
	std::string m_typeID;

	int m_health; // this will be generated randomly (see below)

	int m_speed; // this will be generated randomly (see below)

	int m_x;

	int m_y;
};

#endif
#pragma once
#ifndef	GAME_H
#define GAME_H
#include "GameCharacter.h"
#include "Player.h"
#include "Enemy.h"
#include <list>

class Game
{
protected:
	//creating a list
	list<GameCharacter*> lpGameCharacters;
	//player object
	Player* pPlayer1 = new Player;
	//enemy objects
	Enemy* pEnemy1 = new Enemy();
	Enemy* pEnemy2 = new Enemy();
	Enemy* pEnemy3 = new Enemy();
	Enemy* pEnemy4 = new Enemy();

public:
	void init();
	void render();
	void update();
	void battle();
	void stats();
	void clean();
};
#endif
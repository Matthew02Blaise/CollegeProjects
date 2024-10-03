#include "Game.h"

void Game::init()
{
	srand((int)time(0));

	//player stats
	int playerHP = (rand() % 170) + 140;
	int playerSpeed = (rand() % 4) + 2;
	int playerX = 1;
	int playerY = 1;

	//enemy stats
	int enemyHP[4] = {(rand() % 150) + 90, (rand() % 150) + 90, (rand() % 150) + 90, (rand() % 150) + 90};
	int enemySpeed[4] = { (rand() % 4) + 2,(rand() % 4) + 2 ,(rand() % 4) + 2,(rand() % 4) + 2};
	int enemyX[4] = {2, 8, 4, 9};
	int enemyY[4] = {2,8,4,9};

	//spawing characters
	pPlayer1->spawn("Player", playerHP, playerSpeed, playerX, playerY); 
	pEnemy1->spawn("Enemy1", enemyHP[0], enemySpeed[0], enemyX[0], enemyY[0]); 
	pEnemy2->spawn("Enemy2", enemyHP[1], enemySpeed[1], enemyX[1], enemyY[1]); 
	pEnemy3->spawn("Enemy3", enemyHP[2], enemySpeed[2], enemyX[2], enemyY[2]); 
	pEnemy4->spawn("Enemy4", enemyHP[3], enemySpeed[3], enemyX[3], enemyY[3]);

	//adding player and enemys to the list
	lpGameCharacters.push_back(pPlayer1);
	lpGameCharacters.push_back(pEnemy1);
	lpGameCharacters.push_back(pEnemy2);
	lpGameCharacters.push_back(pEnemy3);
	lpGameCharacters.push_back(pEnemy4);
}

void Game::render()
{
	//running through the list of characters and implementing render function from gamecharacter
	for (GameCharacter* character : lpGameCharacters) 
	{
		character->render();
	}
}

void Game::battle()
{
	for (auto it1 = lpGameCharacters.begin(); it1 != lpGameCharacters.end(); ++it1)//auto sorting through list from start to finish to check which character
	{
		for (auto it2 = next(it1); it2 != lpGameCharacters.end(); ++it2)
		{
			//2 iterators
			GameCharacter* character1 = *it1;
			GameCharacter* character2 = *it2;

			// Ensure characters are either on the same X or Y position but not the same character
			if (((character1->getXPOS() == character2->getXPOS()) || (character1->getYPOS() == character2->getYPOS())) && (character1->getID() != character2->getID()))
			{
				while ((character1->isAlive()) && (character2->isAlive()))//checking if characters are alive as to not battle against dead characters
				{
					if (character1->getHP() > character2->getHP())//comapring characters hp values
					{
						character2->setHP(0); //character is killed and hp set to 0
						cout << character1->getID() << " wins" << endl;
					}
					else if (character2->getHP() > character1->getHP())
					{
						character1->setHP(0);//character is killed and hp set to 0
						cout << character2->getID() << " wins" << endl;
					}
					else
					{
						cout << "It's a draw" << endl;
					}
				}
			}
		}
	}
}

void Game::stats()
{
	//running through the list of characters and implementing stats function from gamecharacter
	for (GameCharacter* character : lpGameCharacters) 
	{
		character->stats();
	}
}

void Game::update()
{
	//running through the list of characters and implementing update function
	for (GameCharacter* character : lpGameCharacters) 
	{
		character->update();
	}
}

void Game::clean()
{
	//use an iterator to go through the list
	for (auto it = lpGameCharacters.begin(); it != lpGameCharacters.end();)//auto determines type, iterator selects first until it gets to the end of the list
	{
		GameCharacter* character = *it;
		if (!character->isAlive())
		{
			delete character; //delete the character object
			it = lpGameCharacters.erase(it); //erase returns the iterator to the next list item
		}
		else
		{
			++it; //only increment the iterator if you didnt erase
		}
	}
}
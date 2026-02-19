#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class LevelManager
{
private:
	//vector variables for the levels
	Vector2i m_LevelSize;
	Vector2i m_LevelSpawningPointsSize;
	Vector2f m_StartPosition;
	
	//variables for timer
	float m_TimeModifier = 1;
	float m_BaseTimeLimit = 0;
	
	//number of levels
	const int NUM_LEVELS = 4;
	std::string levelToLoad;

public:
	//what is the current level
	int m_CurrentLevel = 0;

	//set size of level
	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	//get the time
	float getTimeLimit();

	//get the starting position
	Vector2f getStartPosition();

	//load next level
	int** nextLevel(VertexArray& rVaLevel);
	std::string getLevelToLoad() const;
	int** nextLevelSpawningPoints();

	//get the size and spawning points of levels
	Vector2i getLevelSize();
	Vector2i getLevelSpawningPointsSize();

	//get your current level
	int getCurrentLevel();
	void setCurrentLevel(int levelNum);

};

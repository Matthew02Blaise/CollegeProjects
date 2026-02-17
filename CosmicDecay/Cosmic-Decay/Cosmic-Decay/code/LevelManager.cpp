#include "stdafx.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureHolder.h"
#include <sstream>
#include <fstream>
#include "LevelManager.h"
#include <iostream>

using namespace sf;
using namespace std;

//Finds the next level to load
int** LevelManager::nextLevel(VertexArray& rVaLevel)
{
	m_LevelSize.x = 0;
	m_LevelSize.y = 0;

	// Get the next level
	m_CurrentLevel++;
	if (m_CurrentLevel > NUM_LEVELS)
	{
		m_CurrentLevel = 1;
		m_TimeModifier -= .1f;
	}

	// Load the appropriate level from a text file
	string levelToLoad;
	switch (m_CurrentLevel)
	{
	
	case 1:
		levelToLoad = "levels/level1.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 100;
		m_BaseTimeLimit = 30.0f;
		break;

	case 2:
		levelToLoad = "levels/level2.txt";
		m_StartPosition.x = 100;
		m_StartPosition.y = 3600;
		m_BaseTimeLimit = 100.0f;
		break;

	case 3:
		levelToLoad = "levels/level3.txt";
		m_StartPosition.x = 1250;
		m_StartPosition.y = 0;
		m_BaseTimeLimit = 30.0f;
		break;

	case 4:
		levelToLoad = "levels/level4.txt";
		m_StartPosition.x = 50;
		m_StartPosition.y = 200;
		m_BaseTimeLimit = 50.0f;
		break;


	}

	ifstream inputFile(levelToLoad);
	string s;

	// Count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_LevelSize.y;
	}

	// Store the length of the rows
	m_LevelSize.x = s.length();


	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	// Prepare the 2d array to hold the int values from the file
	int** arrayLevel = new int*[m_LevelSize.y];
	for (int i = 0; i < m_LevelSize.y; ++i)
	{
		// Add a new array into each array element
		arrayLevel[i] = new int[m_LevelSize.x];
	}

	// Loop through the file and store all the values in the 2d array
	string row;
	int i = 0;
	while (inputFile >> row)
	{
		for (int j = 0; j < row.length(); j++) {

			const char val = row[j];
			
			arrayLevel[i][j] = atoi(&val);
		}

		i++;
	}

	// close the file
	inputFile.close();

	// What type of primitive are we using?
	rVaLevel.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVaLevel.resize(m_LevelSize.x * m_LevelSize.y * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int x = 0; x < m_LevelSize.x; x++)
	{
		for (int y = 0; y < m_LevelSize.y; y++)
		{
			// Position each vertex in the current quad
			rVaLevel[currentVertex + 0].position = 
				Vector2f(x * TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 1].position = 
				Vector2f((x * TILE_SIZE) + TILE_SIZE, y * TILE_SIZE);

			rVaLevel[currentVertex + 2].position = 
				Vector2f((x * TILE_SIZE) + TILE_SIZE, (y * TILE_SIZE) + TILE_SIZE);

			rVaLevel[currentVertex + 3].position = 
				Vector2f((x * TILE_SIZE), (y * TILE_SIZE) + TILE_SIZE);

			// Which tile from the sprite sheet should we use
			int verticalOffset = arrayLevel[y][x] * TILE_SIZE;

			rVaLevel[currentVertex + 0].texCoords = 
				Vector2f(0, 0 + verticalOffset);

			rVaLevel[currentVertex + 1].texCoords = 
				Vector2f(TILE_SIZE, 0 + verticalOffset);

			rVaLevel[currentVertex + 2].texCoords = 
				Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

			rVaLevel[currentVertex + 3].texCoords = 
				Vector2f(0, TILE_SIZE + verticalOffset);

			// Position ready for the next four vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return arrayLevel;
}

//returns the level to load
std::string LevelManager::getLevelToLoad() const {
	return levelToLoad;
}

//returns level size
Vector2i LevelManager::getLevelSize()
{
	return m_LevelSize;
}

//returns the spawning points
Vector2i LevelManager::getLevelSpawningPointsSize()
{
	return m_LevelSpawningPointsSize;
}

//returns the current level
int LevelManager::getCurrentLevel()
{
	return m_CurrentLevel;
}

//sest the level number
void LevelManager::setCurrentLevel(int levelNum)
{
	m_CurrentLevel = levelNum;
}

//returns the time limit
float LevelManager::getTimeLimit()
{
	return m_BaseTimeLimit * m_TimeModifier;

}

//returns start positions
Vector2f LevelManager::getStartPosition()
{
	return m_StartPosition;
}

//returns the next spawning points
int** LevelManager::nextLevelSpawningPoints()
{
	m_LevelSpawningPointsSize.x = 0;
	m_LevelSpawningPointsSize.y = 0;

	// use the current level to ensure that correct level artefacts are loaded


	// Load the appropriate level from a text file
	string levelToLoad;
	switch (m_CurrentLevel)
	{

	case 1:
		levelToLoad = "levels/level1Pickups.txt";

		break;

	case 2:
		levelToLoad = "levels/level2Pickups.txt";

		break;

	case 3:
		levelToLoad = "levels/level3Pickups.txt";

		break;

	case 4:
		levelToLoad = "levels/level4.txt";

		break;


	}

	ifstream inputFile(levelToLoad);
	string s;

	// Count the number of rows in the file
	while (getline(inputFile, s))
	{
		++m_LevelSpawningPointsSize.y;
	}

	// Store the length of the rows
	m_LevelSpawningPointsSize.x = s.length();

	// Go back to the start of the file
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	// Prepare the 2d array to hold the int values from the file
	int** arrayLevel = new int* [m_LevelSpawningPointsSize.y];
	for (int i = 0; i < m_LevelSpawningPointsSize.y; ++i)
	{
		// Add a new array into each array element
		arrayLevel[i] = new int[m_LevelSpawningPointsSize.x];
	}

	// Loop through the file and store all the values in the 2d array
	string row;
	int i = 0;
	while (inputFile >> row)
	{
		for (int j = 0; j < row.length(); j++) {

			const char val = row[j];
			arrayLevel[i][j] = atoi(&val);
		}

		i++;
	}

	// close the file
	inputFile.close();

	return arrayLevel;
}

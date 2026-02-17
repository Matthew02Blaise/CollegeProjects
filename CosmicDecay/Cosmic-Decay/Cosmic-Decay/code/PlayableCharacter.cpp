#include "stdafx.h"
#include "PlayableCharacter.h"
#include <random>
using namespace std;
#include <iostream>
#include <cmath>

void PlayableCharacter::spawn(Vector2f startPosition, float gravity, int m_type)
{
	// Place the player at the starting point
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	// Initialize the gravity
	m_Gravity = gravity;

	//Initialise the health

	if (m_type == 0) //Pickup
	{
		
	}
	else if (m_type == 1) //Zach
	{
		m_Health = 100;
	}
	else if (m_type == 2) //Szymon
	{
		m_Health = 100;
	}
	else if (m_type == 3) //Matthew
	{
		m_Health = 100;
	}
	else if (m_type == 4) //Corey
	{
		m_Health = 100;
	}
	else if (m_type == 5) //ZombieAlien1
	{
		m_Health = 3;
	}
	else if (m_type == 6) //ZombieAlien2
	{
		m_Health = 5;
	}
	else if (m_type == 7) //ZombieAlien3
	{
		m_Health = 2;
	}

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);
	//m_SpriteSheet.setPosition(m_Position);

	m_Active = true;

}

//Sets the speed of the character
void PlayableCharacter::setSpeed(float value)
{
	m_Speed = value;
}

//Return the speed
float PlayableCharacter::getSpeed()
{
	return m_Speed;
}

//Move to Float Rectangle !!
//Find out where Pacman is and where the ghost is
//convert to a grid location so we can check the levelmap map_arraylevel
//move in the direction of the player if the cell we want to move to is empty i.e. 0
void PlayableCharacter::moveToFR(float elapsedTime, FloatRect playerLocation, float speed, int** map_ArrayLevel)
{
	/*Dec 2nd 2021 */
	float playerX = playerLocation.left;
	float playerY = playerLocation.top;

	//18 11 2002

	int playerGridLocRow = ((round(playerY) + 50) / 50);

	int playerGridLocCol = ((round(playerX) + 50) / 50);


	int enemyGridLocRow = ((round(m_Position.y) + 50) / 50);
	int enemyGridLocCol = ((round(m_Position.x) + 50) / 50);

	//18 11 2022 2nd row, 2nd col  would have an array index of 1,1
	enemyGridLocRow -= 1;
	enemyGridLocCol -= 1;
	playerGridLocRow -= 1;
	playerGridLocCol -= 1;



	if (playerX > m_Position.x)
	{

		if (map_ArrayLevel[enemyGridLocRow][enemyGridLocCol + 1] == 0)
		{
			m_Position.x = int(m_Position.x + speed * elapsedTime);
			//enemy is moving right 
			direction = sf::Vector2f(0, -1);
		}
	}

	if (playerY > m_Position.y)
	{
		enemyGridLocRow = ((m_Position.y) / 50);

		if (map_ArrayLevel[enemyGridLocRow + 1][enemyGridLocCol] == 0)
		{
			m_Position.y = int(m_Position.y + speed * elapsedTime);
			//enemy is moving down 
			direction = sf::Vector2f(-1, 0);
		}

	}

	if (playerX < m_Position.x)
	{
		if (map_ArrayLevel[enemyGridLocRow][enemyGridLocCol - 1] == 0)
		{
			m_Position.x = int(m_Position.x - speed * elapsedTime);
			//enemy is moving left 
			direction = sf::Vector2f(0, 1);
		}

	}

	if (playerY < m_Position.y)
	{

		if (map_ArrayLevel[enemyGridLocRow - 1][enemyGridLocCol] == 0)
		{
			m_Position.y = int(m_Position.y - speed * elapsedTime);
			//enemy is moving up
			direction = sf::Vector2f(1, 0);
		}
	}

	updateLeftRightHeadFeet();

}

//Ghost AI code
void PlayableCharacter::GhostChaseMoveTo(float elapsedTime, FloatRect playerLocation, float speed, int** map_ArrayLevel, int levelRows, int LevelCols)
{

	float playerX = playerLocation.left;
	float playerY = playerLocation.top;

	int playerGridLocRow = ((round(playerY) + 50) / 50);

	int playerGridLocCol = ((round(playerX) + 50) / 50);


	int enemyGridLocRow = ((round(m_Position.y) + 50) / 50);
	int enemyGridLocCol = ((round(m_Position.x) + 50) / 50);

	//2nd row, 2nd col  would have an array index of 1,1
	enemyGridLocRow -= 1;
	enemyGridLocCol -= 1;
	playerGridLocRow -= 1;
	playerGridLocCol -= 1;

	int x1 = playerX + 25; // center of player
	int y1 = playerY + 25; // center of player
	int x2 = m_Position.x + 25; //centre of the enemy
	int y2 = m_Position.y + 25;//centre of the enemy
	int xsquared = (x2 - x1) * (x2 - x1);
	int ysquared = (y2 - y1) * (y2 - y1);
	double d = sqrt(xsquared + ysquared);
	//Set Up, Down, Left and Right Distances to a max value
	// we will overwrite these values for certain conditions
	// an updated value will be recorded if the square we are checking is empty
	// and the square we are checking is not a reverse in direction
	//https://gameinternals.com/understanding-pac-man-ghost-behavior

	double upDist = 9999999;
	double downDist = 9999999;
	double rightDist = 9999999;
	double leftDist = 9999999;
	//check to see if cell to the right is empty if so calculate distance from proposed new square from player
	if (map_ArrayLevel[enemyGridLocRow][enemyGridLocCol + 1] == 0 || map_ArrayLevel[enemyGridLocRow - 1][enemyGridLocCol] == 4 || map_ArrayLevel[enemyGridLocRow - 1][enemyGridLocCol] == 2)
	{
		x2 = m_Position.x + 50; //location of new square
		x2 = x2 + 25;//measure d from centre of proposed new square
		y2 = m_Position.y + 25;//centre of the ghost
		xsquared = (x2 - x1) * (x2 - x1);
		ysquared = (y2 - y1) * (y2 - y1);
		d = sqrt(xsquared + ysquared);
		rightDist = d;
	}
	//check to see if cell to the left is empty if so calculate distance from proposed new square from player
	if (map_ArrayLevel[enemyGridLocRow][enemyGridLocCol - 1] == 0 || map_ArrayLevel[enemyGridLocRow][enemyGridLocCol - 1] == 4 || map_ArrayLevel[enemyGridLocRow - 1][enemyGridLocCol] == 2)
	{
		x2 = m_Position.x - 50; //location of new square
		x2 = x2 + 25;//measure d from centre of proposed new square
		y2 = m_Position.y + 25;//centre of the enemy

		xsquared = (x2 - x1) * (x2 - x1);
		ysquared = (y2 - y1) * (y2 - y1);
		d = sqrt(xsquared + ysquared);
		leftDist = d;
	}

	//check to see if cell above is empty if so calculate distance from proposed new square from player

	if (map_ArrayLevel[enemyGridLocRow - 1][enemyGridLocCol] == 0 || map_ArrayLevel[enemyGridLocRow - 1][enemyGridLocCol] == 4 || map_ArrayLevel[enemyGridLocRow - 1][enemyGridLocCol] == 2)
	{
		y2 = m_Position.y - 50; //location of new square
		y2 = y2 + 25;//measure d from centre of proposed new square
		x2 = m_Position.x + 25;//centre of the enemy

		xsquared = (x2 - x1) * (x2 - x1);
		ysquared = (y2 - y1) * (y2 - y1);
		d = sqrt(xsquared + ysquared);
		upDist = d;
	}

	//check to see if cell below is empty if so calculate distance from proposed new square from player
	if (map_ArrayLevel[enemyGridLocRow + 1][enemyGridLocCol] == 0 || map_ArrayLevel[enemyGridLocRow - 1][enemyGridLocCol] == 4 || map_ArrayLevel[enemyGridLocRow - 1][enemyGridLocCol] == 2)
	{
		y2 = m_Position.y + 50; //location of new square
		y2 = y2 + 25;//measure d from centre of proposed new square
		x2 = m_Position.x + 25;//centre of the enemy

		xsquared = (x2 - x1) * (x2 - x1);
		ysquared = (y2 - y1) * (y2 - y1);
		d = sqrt(xsquared + ysquared);
		downDist = d;
	}
	//examine the surrounding cells, if a non reversing cell is empty then check the distance from that
	// cell to player
	//identify the non reversing cell with the closest distance and move that way
	//player has to move

	//store current direction
	sf::Vector2f currentDirection = direction;
	//scenario 1 heading right
	if (m_Moving)
	{
		//if heading right then current direction is {0,-1}
		if ((currentDirection.x == 0) && (currentDirection.y == -1))
		{
			//if moving right and the current value of X has not yet reached its target 
			// then continue to increment X

			if (m_Position.x < m_Dest_Coords.x)
			{
				m_Position.x = m_Position.x + speed * elapsedTime;
			}
			else
			{
				m_Position.x = m_Dest_Coords.x;
				m_Moving = false;
			}

		}
		//moving left scenario X is decreasing
		else if ((currentDirection.x == 0) && (currentDirection.y == 1))
		{
			//if moving left and the current value of X has not yet reached its target 
			// then continue to decrement X
			if (m_Position.x > m_Dest_Coords.x)
			{
				m_Position.x = m_Position.x - speed * elapsedTime;
			}
			else
			{
				m_Position.x = m_Dest_Coords.x;
				m_Moving = false;
			}
		}//end of left scenario
			//moving down scenario Y is increasing
		else if ((currentDirection.x == -1) && (currentDirection.y == 0))
		{
			//if moving down and the current value of Y has not yet reached its target 
			// then continue to increment Y
			if (m_Position.y < m_Dest_Coords.y)
			{
				m_Position.y = m_Position.y + speed * elapsedTime;
			}
			else
			{
				m_Position.y = m_Dest_Coords.y;
				m_Moving = false;
			}

		}//end of moving down

		 //moving up scenario Y is decreasing
		else if ((currentDirection.x == 1) && (currentDirection.y == 0))
		{
			//if moving up and the current value of Y has not yet reached its target 
			// then continue to decrement Y
			if (m_Position.y > m_Dest_Coords.y)
			{
				m_Position.y = m_Position.y - speed * elapsedTime;
			}
			else
			{
				m_Position.y = m_Dest_Coords.y;
				m_Moving = false;
			}

		}//end of moving down

	}//end of moving check
		//if heading right then current direction is {0,-1}
	else //we are not moving
	{
		if ((currentDirection.x == 0) && (currentDirection.y == -1))
		{
			//enemy is moving up
			if ((upDist <= rightDist) && (upDist <= downDist))
			{
				direction = sf::Vector2f(1, 0);
			}
			//enemy is moving right
			else if ((rightDist <= upDist) && (rightDist <= downDist))
			{
				direction = sf::Vector2f(0, -1);
			}
			//enemy is moving down
			else if ((downDist <= upDist) && (downDist <= rightDist))
			{
				direction = sf::Vector2f(-1, 0);
			}

		}
		//scenario 2 headling left cannot reverse direction
			//if heading left then current direction is {0,1}
		if ((currentDirection.x == 0) && (currentDirection.y == 1))
		{
			//enemy is moving up
			if ((upDist <= leftDist) && (upDist <= downDist))
			{
				direction = sf::Vector2f(1, 0);
			}
			//enemy is moving right
			else if ((leftDist <= upDist) && (leftDist <= downDist))
			{
				direction = sf::Vector2f(0, 1);
			}
			//enemy is moving down
			else if ((downDist <= upDist) && (downDist <= leftDist))
			{
				direction = sf::Vector2f(-1, 0);
			}

		}
		//scenario 3 heading down
			//if heading down then current direction is {-1,0}
		if ((currentDirection.x == -1) && (currentDirection.y == 0))
		{
			//enemy is moving left
			if ((leftDist <= rightDist) && (leftDist <= downDist))
			{
				direction = sf::Vector2f(0, 1);
			}
			//enemy is moving right
			else if ((rightDist <= leftDist) && (rightDist <= downDist))
			{
				direction = sf::Vector2f(0, -1);
			}
			//enemy is moving down
			else if ((downDist <= leftDist) && (downDist <= rightDist))
			{
				direction = sf::Vector2f(-1, 0);
			}
		}

		//scenario 4 heading up
				//if heading up then current direction is {1,0}
		if ((currentDirection.x == 1) && (currentDirection.y == 0))
		{
			//enemy is moving left
			if ((leftDist <= rightDist) && (leftDist <= upDist))
			{
				direction = sf::Vector2f(0, 1);
			}
			//enemy is moving right
			else if ((rightDist <= leftDist) && (rightDist <= upDist))
			{
				direction = sf::Vector2f(0, -1);
			}
			//enemy is moving up
			else if ((upDist <= leftDist) && (upDist <= rightDist))
			{
				direction = sf::Vector2f(1, 0);
			}

		}
		m_Moving = true;
		//if up calc new destination
		if (direction == sf::Vector2f(1, 0))
		{
			m_Dest_Coords.x = m_Position.x;
			m_Dest_Coords.y = m_Position.y - 50;

		}
		//if down calc new destination
		else if (direction == sf::Vector2f(-1, 0))
		{
			m_Dest_Coords.x = m_Position.x;
			m_Dest_Coords.y = m_Position.y + 50;
		}
		//if left calc new destination
		else if (direction == sf::Vector2f(0, 1))
		{
			m_Dest_Coords.x = m_Position.x - 50;
			m_Dest_Coords.y = m_Position.y;
		}
		//if right calc new destination
		if (direction == sf::Vector2f(0, -1))
		{
			m_Dest_Coords.x = m_Position.x + 50;
			m_Dest_Coords.y = m_Position.y;
		}

	}// end of not moving section


	updateLeftRightHeadFeet();

}

void PlayableCharacter::updateLeftRightHeadFeet()
{
	FloatRect r = getPosition();


	// Feet
	m_Feet.left = r.left + 7;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 14;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left + 7;
	m_Head.top = r.top;
	m_Head.width = r.width - 14;
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + r.width - 1;
	m_Right.top = r.top + r.height * .3;
	m_Right.width = 1;
	m_Right.height = r.height * .3;

	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .3;
	m_Left.width = 1;
	m_Left.height = r.height * .3;

}


void PlayableCharacter::update(float elapsedTime, int m_type)
{



	// Handle Jumping
	if (m_IsJumping)
	{
		// Update how long the jump has been going
		m_TimeThisJump += elapsedTime;

		// Is the jump going upwards
		if (m_TimeThisJump < m_JumpDuration)
		{
			// Move up at twice gravity
			m_Position.y -= m_Gravity * 2 * elapsedTime;
		}
		else
		{
			m_IsJumping = false;
			m_IsFalling = true;
		}

	}

	// Apply gravity
	if (m_IsFalling)
	{
		m_Position.y += m_Gravity * elapsedTime;
	}

	updateLeftRightHeadFeet();

	// Move the sprite into position
	m_Sprite.setPosition(m_Position);

}

//Return the position
FloatRect PlayableCharacter::getPosition()
{

	return m_Sprite.getGlobalBounds();
}

//Return the center
Vector2f PlayableCharacter::getCenter()
{
	LevelManager l;
	return Vector2f(
		m_Position.x + (l.TILE_SIZE / 2),
		m_Position.y + (l.TILE_SIZE / 2));
}

//Return the feet
FloatRect PlayableCharacter::getFeet()
{
	return m_Feet;
}

//Return the head
FloatRect PlayableCharacter::getHead()
{
	return m_Head;
}

//Return the left of the character
FloatRect PlayableCharacter::getLeft()
{
	return m_Left;
}

//Return the right of the character
FloatRect PlayableCharacter::getRight()
{
	return m_Right;
}

//returns sprite
Sprite PlayableCharacter::getSprite()
{
	return m_Sprite;
}

//returns sprite
Sprite PlayableCharacter::getSpriteFromSheet()
{
	return m_Sprite;
}


//Stop the characyer falling
void PlayableCharacter::stopDown(float position)
{
	if (getName() == "PacMan")
	{
		cout << "Stop Down was called \n";
		cout << "m_Position.y before " << m_Position.y << "\n";
	}

	m_Position.y = position - getPosition().height;
	if (getName() == "PacMan")
	{
		cout << "m_Position.y after " << m_Position.y << "\n";
	}
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopUp(float position)
{
	if (getName() == "PacMan")
	{
		cout << "Stop up was called \n";
		cout << "m_Position.y before " << m_Position.y << "\n";
	}

	m_Position.y = position + getPosition().height;
	if (getName() == "PacMan")
	{
		cout << "m_Position.y after " << m_Position.y << "\n";
	}

	m_Sprite.setPosition(m_Position);

}

//Stop the character moving right
void PlayableCharacter::stopRight(float position)
//reduce x by the position - m_Sprite.getGlobalBounds().width;
{
	m_Position.x = position - getPosition().width;
	m_Sprite.setPosition(m_Position);
}

//stop the character moving left
void PlayableCharacter::stopLeft(float position)
//increment X by the width of the sprite
{
	m_Position.x = position + getPosition().width;
	m_Sprite.setPosition(m_Position);
}

//Stop jumping
void PlayableCharacter::stopJump()
{
	// Stop a jump early 
	m_IsJumping = false;
	m_IsFalling = true;
}

//Set the sprite from the sprite sheet
void PlayableCharacter::setSpriteFromSheet(sf::IntRect textureBox)
{
	LevelManager l;
	int tile_size = l.TILE_SIZE;
	sheetCoordinate = sf::Vector2i(textureBox.left, textureBox.top);
	spriteSize = sf::Vector2i(tile_size, tile_size);
	if (textureBox.width > tile_size)
	{
		animation_it_limit = (textureBox.width / tile_size) - 1;

		horizontal = true;
	}
	else if (textureBox.height > tile_size)
	{
		animation_it_limit = (textureBox.height / tile_size) - 1;
		horizontal = false;
	}
	else
		throw std::logic_error("Animation bounding box must contain multiply sprites, setSprite(sf::IntRect )\n");
	m_Sprite.setTextureRect(sf::IntRect{ sheetCoordinate, spriteSize });

}

//Set the name of the character
void PlayableCharacter::setName(String id)
{
	m_Name = id;
}

//return the name
String PlayableCharacter::getName()
{
	return m_Name;
}

//Handles the input of the character
bool PlayableCharacter::handleInput()
{
	return true;
}

//Move the animation rectangle
void PlayableCharacter::moveTextureRect(float timeElapsed)
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

	cout << "Animation Counter: " << ani_counter << std::endl;
	cout << "Current Texture Rect: " << m_Sprite.getTextureRect().left << ", " << m_Sprite.getTextureRect().top << std::endl;
}




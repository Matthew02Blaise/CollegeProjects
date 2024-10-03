#include "Player.h"

void Player::update()
{
	//variables for loop and player input
	int loop = 0;
	char location;

	//do while loop for player input
	do
	{
		cout << "Do you want to move to the north, south, east or west?" << endl;
		cin >> location;

		if (location == 'N')
		{
			++m_x;
			cout << "Player is moving to the North" << endl;
			if (m_x > 10)
			{
				cout << "Player hit a wall" << endl;

				m_health -= (m_speed * 2);

				cout << "Player took damage and turned around." << endl;
				m_x = 10;
			}
			loop = 1;
		}
		else if (location == 'S')
		{
			--m_x;
			cout << "Player is moving to the South" << endl;
			if (m_x < 1)
			{
				cout << "Player hit a wall" << endl;

				m_health -= (m_speed * 2);

				cout << "Player took damage and turned around." << endl;
				m_x = 1;
			}
			loop = 1;
		}
		else if (location == 'E')
		{
			++m_y;
			cout << "Player is moving to the East" << endl;
			if (m_y > 10)
			{
				cout << "Player hit a wall" << endl;

				m_health -= (m_speed * 2);

				cout << "Player took damage and turned around." << endl;
				m_y = 10;
			}
			loop = 1;
		}
		else if (location == 'W')
		{
			--m_y;
			cout << "Player is moving to the West" << endl;
			if (m_y < 1)
			{
				cout << "Player hit a wall" << endl;

				m_health -= (m_speed * 2);

				cout << "Player took damage and turned around." << endl;
				m_y = 1;
			}
			loop = 1;
		}
		else
		{
			cout << "Invalid Input." << endl;
		}
	} while (loop == 0);
}
#include "Enemy.h";

void Enemy::update()
{
	srand((int)time(0));

	//random for if the enemy moves or not
	int movement = (rand() % 2);

	//implementing enemy movement
	if (movement <= 1)
	{
		++m_y;//increments movement
		int moving = (rand() % 9) + 1;

		if (moving > 0 && moving <= 8)
		{
			cout << "Enemy moves up 1 space" << endl;
			if (m_y > 10)
			{
				cout << "Enemy hit a wall" << endl;

				m_health -= (m_speed * 3);

				cout << "Enemy took damage and turned around." << endl;
				m_y = 10;
			}
		}
		else if (moving >= 9)
		{
			cout << "Enemy didnt move" << "/n";
		}
	}
	else
	{
		--m_y;//increments movement
		int moving = (rand() % 9) + 1;

		if (moving > 0 && moving <= 8)
		{
			cout << "Enemy moves down 1 space" << endl;
			if (m_x < 1)
			{
				cout << "Enemy hit a wall" << endl;

				m_health -= (m_speed * 3);

				cout << "Enemy took damage and turned around." << endl;
				m_x = 1;
			}
		}
		else if (moving >= 9)
		{
			cout << "Enemy didnt move" << endl;
		}
	}
}
#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "GameCharacter.h"

class Enemy : public GameCharacter
{
public:
	void update() override; //overriding gamecharacters update function to make it unique
};
#endif 
#pragma once
#ifndef	PLAYER_H
#define PLAYER_H

#include "GameCharacter.h"

class Player : public GameCharacter
{
public:
	void update() override; //overriding gamecharacters update function to make it unique
};
#endif
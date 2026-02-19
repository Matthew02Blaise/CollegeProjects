#pragma once
#include "PlayableCharacter.h"

class Enemy : public PlayableCharacter
{
public:
	// A constructor specific to Enemy
	Enemy();
	void setSprite(int e_type);

	// The overriden input handler for Enemy
	bool virtual handleInput();
	void updateSprite(int e_type, float timeElapsed);
	void virtual moveTextureRect(float timeElapsed);
	void gotShot();
	bool isActive();

};
#pragma once

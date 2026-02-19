#include "stdafx.h"
#include "HealthPickup.h"
#include "TextureHolder.h"
#include <iostream>

HealthPickup::HealthPickup()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/healthPickup.png"));

}
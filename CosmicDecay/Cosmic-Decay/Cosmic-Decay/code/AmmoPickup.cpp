#include "stdafx.h"
#include "AmmoPickup.h"
#include "TextureHolder.h"
#include <iostream>

AmmoPickup::AmmoPickup()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/ammoPickup.png"));

}
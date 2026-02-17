#include "stdafx.h"
#include "Shuttle.h"
#include "TextureHolder.h"
#include <iostream>

Shuttle::Shuttle()
{//Sets the texture of the shuttle
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/Shuttle.png"));

}







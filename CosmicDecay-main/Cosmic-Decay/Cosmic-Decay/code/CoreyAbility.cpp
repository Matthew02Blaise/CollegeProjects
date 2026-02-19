#include "CoreyAbility.h"
#include "PlayableCharacter.h"
#include "Engine.h"
#include <iostream>

CoreyAbility::CoreyAbility(Player& player)
    : Abilities(player), m_Player(player), invulnerable(false) // Initialize m_Player here
{
}

void CoreyAbility::useAbility()
{
    if (!m_Active)
    {
        std::cout << "Corey uses Mask ability!\n";
        m_Active = true;
        invulnerable = true;

        // Grant invulnerability
        m_Player.setInvulnerable(true); // Ensure this method exists in Player class

        // Start the ability timer
        m_Clock.restart();
    }
}

void CoreyAbility::update()
{
    if (m_Active && m_Clock.getElapsedTime().asSeconds() >= 10.0f)
    {
        std::cout << "Corey's Mask ability ended.\n";
        m_Active = false;
        invulnerable = false;

        // Remove invulnerability
        m_Player.setInvulnerable(false); // Ensure this method exists in Player class
    }
}
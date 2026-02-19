#include "SzymonAbility.h"
#include "PlayableCharacter.h"
#include "Engine.h"
#include <iostream>

SzymonAbility::SzymonAbility(Player& player)
    : Abilities(player), m_Player(player), increasedFireRate(false), infiniteAmmo(false)
{
}

void SzymonAbility::useAbility()
{
    if (!m_Active)
    {
        std::cout << "Szymon uses Vlad ability!\n";
        m_Active = true;
        increasedFireRate = true;
        infiniteAmmo = true;

        // Modify fire rate and ammo
        m_Player.setFireRateMultiplier(2.0f);
        m_Player.setInfiniteAmmo(true);

        // Start the ability timer
        m_Clock.restart();
    }
}

void SzymonAbility::update()
{
    if (m_Active && m_Clock.getElapsedTime().asSeconds() >= 5.0f)
    {
        std::cout << "Szymon's Vlad ability ended.\n";
        m_Active = false;
        increasedFireRate = false;
        infiniteAmmo = false;

        // Revert fire rate and ammo
        m_Player.setFireRateMultiplier(1.0f);
        m_Player.setInfiniteAmmo(false);
    }
}
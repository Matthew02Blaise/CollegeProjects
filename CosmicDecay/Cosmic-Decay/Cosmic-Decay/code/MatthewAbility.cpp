#include "MatthewAbility.h"
#include "PlayableCharacter.h"
#include "Engine.h"
#include <iostream>

MatthewAbility::MatthewAbility(Player& player)
    : Abilities(player), m_Player(player), enemiesIgnore(false), canAttack(true) // Initialize m_Player here
{
}

void MatthewAbility::useAbility()
{
    if (!m_Active)
    {
        std::cout << "Matthew uses invRing ability!\n";
        m_Active = true;
        enemiesIgnore = true;
        canAttack = false;

        // Make enemies ignore the player
        m_Player.setEnemiesIgnore(true);

        // Disable player's ability to attack
        m_Player.setCanAttack(false);

        // Start the ability timer
        m_Clock.restart();
    }
}

void MatthewAbility::update()
{
    if (m_Active && m_Clock.getElapsedTime().asSeconds() >= 10.0f)
    {
        std::cout << "Matthew's invRing ability ended.\n";
        m_Active = false;
        enemiesIgnore = false;
        canAttack = true;

        // Re-enable enemy interactions
        m_Player.setEnemiesIgnore(false);

        // Re-enable player's ability to attack
        m_Player.setCanAttack(true);
    }
}
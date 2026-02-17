#pragma once
#include "Abilities.h"


//UNUSED CODE**********
class Player; // Forward declaration

class MatthewAbility : public Abilities
{
public:
    MatthewAbility(Player& player);

    void useAbility() override;
    void update() override;

private:
    Player& m_Player;          // Reference to the Player
    bool m_Active = false;     // Track if the ability is active
    bool enemiesIgnore = false; // Track if enemies ignore the player
    bool canAttack = true;     // Track if the player can attack
    sf::Clock m_Clock;         // Clock to manage ability duration
};
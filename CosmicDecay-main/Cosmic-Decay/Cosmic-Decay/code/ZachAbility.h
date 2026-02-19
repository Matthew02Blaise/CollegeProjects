#pragma once
#include "Abilities.h"


//UNUSED CODE*************
class Player; // Forward declaration

class ZachAbility : public Abilities
{
public:
    ZachAbility(Player& player);

    void useAbility() override;
    void update() override;

private:
    Player& m_Player;              // Reference to the Player
    bool m_Active = false;         // Track if the ability is active
    bool meleeMode = false;        // Track melee mode
    float originalHealth = 0.0f;   // Store original health
    sf::Clock m_Clock;             // Clock to manage ability duration
};
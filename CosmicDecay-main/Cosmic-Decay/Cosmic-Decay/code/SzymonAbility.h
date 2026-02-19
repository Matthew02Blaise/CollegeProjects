#pragma once
#include "Abilities.h"


//UNUSED CODE*************
class Player; // Forward declaration

class SzymonAbility : public Abilities
{
public:
    SzymonAbility(Player& player);

    void useAbility() override;
    void update() override;

private:
    Player& m_Player;
    bool m_Active = false;          // Track if the ability is active
    bool increasedFireRate = false; // Track fire rate increase
    bool infiniteAmmo = false;      // Track infinite ammo status
    sf::Clock m_Clock;              // Clock to manage ability duration
};
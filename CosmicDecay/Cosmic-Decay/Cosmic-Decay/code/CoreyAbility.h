#pragma once
#include "Abilities.h"

//UNUSED CODE**********
class Player; // Forward declaration

class CoreyAbility : public Abilities
{
public:
    CoreyAbility(Player& player);

    void useAbility() override;
    void update() override;

private:
    Player& m_Player;
    bool m_Active = false;          // Track if the ability is active
    bool invulnerable = false;      // Track invulnerability status
    sf::Clock m_Clock;              // Clock to manage ability duration
};
#pragma once
#include <SFML/System/Clock.hpp>

// Forward declaration
class Player;

class Abilities
{
public:
    //UNUSED CODE*************
    Abilities(Player& player) : m_Player(player), m_Active(false) {}
    virtual ~Abilities() = default;

    // Activate the ability
    virtual void useAbility() = 0;

    // Update the ability's state
    virtual void update() = 0;

protected:
    Player& m_Player;
    bool m_Active;
    sf::Clock m_Clock;
};
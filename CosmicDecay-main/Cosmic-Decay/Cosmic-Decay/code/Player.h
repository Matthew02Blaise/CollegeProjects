#pragma once
#include "PlayableCharacter.h"
#include "Bullet.h"
#include "Arm.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player : public PlayableCharacter {
public:
    // Constructor specific to Player
    Player();

    void setSprite(int m_type);

    // Overridden input handler for Player
    bool handleInput() override;

    // Overridden update method for Player
    void update(float elapsedTime, int m_type) override;

    void moveTextureRect(float timeElapsed) override;

    // Draw method for the player and arm
    void draw(sf::RenderWindow& window);

   

    // Where is the player
    FloatRect getPosition();

    // Ability methods
    void switchToMelee();
    void switchToGun();
    void increaseHealthLevel(int amount);
    void setHealth(float health);
    float getMaxHealth() const;
    void setInvulnerable(bool state);
    void setEnemiesIgnore(bool state);
    void setCanAttack(bool state);
    void setFireRateMultiplier(float multiplier);
    void setInfiniteAmmo(bool state);

   

    //for shop
    void increaseHealth();
    void increaseSpeed();

private:
    
    // Member variables
    float m_Speed = 200.0f;
    float m_JumpDuration = 0.25f;
    bool m_JustJumped = false;

    // Input state
    bool m_UpPressed = false;
    bool m_DownPressed = false;
    bool m_LeftPressed = false;
    bool m_RightPressed = false;

    // Health and abilities
    float m_MaxHealth = 100.0f;
    bool m_Invulnerable = false;
    bool m_EnemiesIgnore = false;
    bool m_CanAttack = true;
    float m_FireRateMultiplier = 1.0f;
    bool m_InfiniteAmmo = false;

    //SOUND
    bool isMoving;
    SoundBuffer walkingBuffer;
    Sound walkingSound;
};
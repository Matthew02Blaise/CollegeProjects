#include "Player.h"
#include "TextureHolder.h"
#include <SFML/Audio.hpp>
#include "Arm.h"
#include "Hud.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

Player::Player() {
    // Associate a texture with the sprite
    m_Sprite = sf::Sprite(TextureHolder::GetTexture("graphics/playerSpriteSheet2.png"));
    m_Sprite.setTextureRect(sf::IntRect{ 50, 100, 50, 50 });

    walkingBuffer.loadFromFile("sound/walkingSound.MP3");
    walkingSound.setBuffer(walkingBuffer);
}


//Sets the sprite of the player
void Player::setSprite(int m_type)
{
    m_Sprite = sf::Sprite(TextureHolder::GetTexture("graphics/playerSpriteSheet2.png"));

    if (m_type == 1)
    {
        //Zach
        m_Sprite.setTextureRect(sf::IntRect{ 50, 150, 50, 50 });
    }
    else if (m_type == 2)
    {
        //Szymon
        m_Sprite.setTextureRect(sf::IntRect{ 50, 50, 50, 50 });
    }
    else if (m_type == 3)
    {
        //Matthew
        m_Sprite.setTextureRect(sf::IntRect{ 50, 100, 50, 50 });
    }
    else if (m_type == 4)
    {
        //Corey
        m_Sprite.setTextureRect(sf::IntRect{ 50, 0, 50, 50 });
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(m_Sprite);       // Draw the player sprite
}

//handles the players input
bool Player::handleInput()
{
    

    m_JustJumped = false;

    // Joystick input variables
    float joyOnePovY = 0;
    float joyOnePovX = 0;
    bool joyOneConnected = sf::Joystick::isConnected(0);
    if (joyOneConnected) {
        joyOnePovY = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
        joyOnePovX = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
    }

    //up and down movement
    if (Keyboard::isKeyPressed(Keyboard::W) || (joyOnePovY == 100)) //Moving up
    {
        m_UpPressed = true;

    }
    else
    {
        m_UpPressed = false;
    }


    if (Keyboard::isKeyPressed(Keyboard::S) || (joyOnePovY == -100)) //Moving down
    {
        m_DownPressed = true;

    }
    else
    {
        m_DownPressed = false;
    }
    if (Keyboard::isKeyPressed(Keyboard::A) || (joyOnePovX == -100)) //Moving left
    {
        m_LeftPressed = true;

    }
    else
    {
        m_LeftPressed = false;
    }


    if (Keyboard::isKeyPressed(Keyboard::D) || (joyOnePovX == 100)) //Moving right
    {
        m_RightPressed = true;
    }
    else
    {
        m_RightPressed = false;
    }


    // Determine if the player is moving
    isMoving = m_UpPressed || m_DownPressed || m_LeftPressed || m_RightPressed;

    // Play or stop the walking sound
    if (isMoving && walkingSound.getStatus() != sf::Sound::Playing) {
        walkingSound.play();
    }
    else if (!isMoving && walkingSound.getStatus() == sf::Sound::Playing) {
        walkingSound.stop();
    }

    return m_JustJumped;
}

void Player::update(float elapsedTime, int m_type)
{
    if (m_RightPressed) {  //Update the player when right is pressed
        m_Position.x += m_Speed * elapsedTime;
        if (m_type == 1) //Zach
        {
            setSpriteFromSheet(sf::IntRect(100, 150, 250, 50));
        }
        else if (m_type == 2) //Szymon
        {
            setSpriteFromSheet(sf::IntRect(100, 50, 250, 50));
        }
        else if (m_type == 3)//Matthew
        {
            setSpriteFromSheet(sf::IntRect(100, 100, 250, 50));
        }
        else if (m_type == 4)//Corey
        {
            setSpriteFromSheet(sf::IntRect(100, 0, 250, 50));
        }
        moveTextureRect(elapsedTime);
    }
    else if (m_LeftPressed) { //Update the player when left is pressed
        m_Position.x -= m_Speed * elapsedTime;
        if (m_type == 1) //Zach
        {
            setSpriteFromSheet(sf::IntRect(100, 150, 250, 50));
        }
        else if (m_type == 2)//Szymon
        {
            setSpriteFromSheet(sf::IntRect(100, 50, 250, 50));
        }
        else if (m_type == 3)//Matthew
        {
            setSpriteFromSheet(sf::IntRect(100, 100, 250, 50));
        }
        else if (m_type == 4)//Corey
        {
            setSpriteFromSheet(sf::IntRect(100, 0, 250, 50));
        }
        moveTextureRect(elapsedTime);
    }
    else if (m_UpPressed) { //Update the player when up is pressed
        m_Position.y -= m_Speed * elapsedTime;
        if (m_type == 1) //Zach
        {
            setSpriteFromSheet(sf::IntRect(100, 150, 250, 50));
        }
        else if (m_type == 2)//Szymon
        {
            setSpriteFromSheet(sf::IntRect(100, 50, 250, 50));
        }
        else if (m_type == 3)//Matthew
        {
            setSpriteFromSheet(sf::IntRect(100, 100, 250, 50));
        }
        else if (m_type == 4)//Corey
        {
            setSpriteFromSheet(sf::IntRect(100, 0, 250, 50));
        }
        moveTextureRect(elapsedTime);
    }
    else if (m_DownPressed) { //Update the player when down is pressed
        m_Position.y += m_Speed * elapsedTime;
        if (m_type == 1) //Zach
        {
            setSpriteFromSheet(sf::IntRect(100, 150, 250, 50));
        }
        else if (m_type == 2)//Szymon
        {
            setSpriteFromSheet(sf::IntRect(100, 50, 250, 50));
        }
        else if (m_type == 3)//Matthew
        {
            setSpriteFromSheet(sf::IntRect(100, 100, 250, 50));
        }
        else if (m_type == 4)//Corey
        {
            setSpriteFromSheet(sf::IntRect(100, 0, 250, 50));
        }
        moveTextureRect(elapsedTime);
    }

   

    // Update collision boxes
    sf::FloatRect r = getPosition();

    // Feet
    m_Feet.left = r.left + 3;
    m_Feet.top = r.top + r.height - 1;
    m_Feet.width = r.width - 6;
    m_Feet.height = 1;

    // Head
    m_Head.left = r.left + 3;
    m_Head.top = r.top - 1;
    m_Head.width = r.width - 6;
    m_Head.height = 1;

    // Right
    m_Right.left = r.left + r.width - 1;
    m_Right.top = r.top + r.height * .35;
    m_Right.width = 1;
    m_Right.height = r.height * .3;

    // Left
    m_Left.left = r.left + 1;
    m_Left.top = r.top + r.height * .35;
    m_Left.width = 1;
    m_Left.height = r.height * .3;

    // Move the sprite into position
    updateLeftRightHeadFeet();
    m_Sprite.setPosition(m_Position);
}

void Player::moveTextureRect(float timeElapsed)
{
    // if the animation counter is greater than the animation limit reset to 0
    if (ani_counter == animation_it_limit - 1)
    {
        ani_counter = 0;
    }

    if (horizontal) {
        // Move the texture rectangle horizontally
        m_Sprite.setTextureRect(sf::IntRect(
            sheetCoordinate.x + ani_counter * spriteSize.x,
            sheetCoordinate.y,
            spriteSize.x,
            spriteSize.y
        ));
    }
    else {
        // Move the texture rectangle vertically
        m_Sprite.setTextureRect(sf::IntRect(
            sheetCoordinate.x,
            sheetCoordinate.y + ani_counter * spriteSize.y,
            spriteSize.x,
            spriteSize.y
        ));
    }

    //increment animation counter to point to the next frame
    double timePerFrame;
    timePerFrame = 1.0 / 5.0;
    animationTimer = animationTimer + timeElapsed;
    if (animationTimer > timePerFrame)
    {
        ani_counter++;
        animationTimer = 0;
    }

    //cout << "Animation Counter: " << ani_counter << std::endl;
    //cout << "Current Texture Rect: " << m_Sprite.getTextureRect().left << ", " << m_Sprite.getTextureRect().top << std::endl;
}

//Returns positiom
FloatRect Player::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

// Ability methods
void Player::switchToMelee() {
    // Logic to switch to melee weapon
    std::cout << "Switched to melee weapon.\n";
}

void Player::switchToGun() {
    // Logic to switch to gun weapon
    std::cout << "Switched to gun weapon.\n";
}

void Player::increaseHealthLevel(int amount) {
    // Logic to increase health level
    std::cout << "Health increased by " << amount << ".\n";
}

void Player::setHealth(float health) {
    // Logic to set health
    std::cout << "Health set to " << health << ".\n";
}

//returns the max health
float Player::getMaxHealth() const {
    return m_MaxHealth;
}

//set being invulnerable
void Player::setInvulnerable(bool state) {
    m_Invulnerable = state;
    std::cout << "Invulnerability set to " << (state ? "true" : "false") << ".\n";
}

//stop the enemies following you
void Player::setEnemiesIgnore(bool state) {
    m_EnemiesIgnore = state;
    std::cout << "Enemies ignore set to " << (state ? "true" : "false") << ".\n";
}

//Stops the enemies from attacking
void Player::setCanAttack(bool state) {
    m_CanAttack = state;
    std::cout << "Can attack set to " << (state ? "true" : "false") << ".\n";
}

//Sets multiplier to fire rate
void Player::setFireRateMultiplier(float multiplier) {
    m_FireRateMultiplier = multiplier;
    std::cout << "Fire rate multiplier set to " << multiplier << ".\n";
}

//Sets infinite ammo
void Player::setInfiniteAmmo(bool state) {
    m_InfiniteAmmo = state;
    std::cout << "Infinite ammo set to " << (state ? "true" : "false") << ".\n";
}

//Increases the speed.
void Player::increaseSpeed()
{
    m_Speed = m_Speed + 100;
}
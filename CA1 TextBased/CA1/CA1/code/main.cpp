#include "GameCharacter.h"
#include <list>
#include "Game.h"

int main()
{
    //game object
    Game game;
    //initialising characters
    game.init();

    //game loop
    for (int i = 0; i < 100; ++i) {
        game.render();
        game.update();
        game.battle();
        game.stats();
        game.clean();
    }
    //print stats post game
    game.stats();
    return 0;
}
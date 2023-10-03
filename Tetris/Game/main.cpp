#include "Configuration/Configuration.h"
#include "Game.h"

int main()
{
    Configuration::initialize();
    Game game;
    game.run();
    return 0;
}
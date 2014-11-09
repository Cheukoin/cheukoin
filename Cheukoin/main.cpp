#include <iostream>
#include <memory>

#include "Card.h"
#include "Trick.h"
#include "Game.h"
#include "NetworkManager.h"
#include "ResourcePath.h"
#include "Player.h"
#include "Lobby.h"
#include "Bot.h"
#include "Score.h"

using namespace std;

int main()
{
    Application& app = Application::getInstance();
    app.initWindow();

    app.mainLoop();

    return 0;
}

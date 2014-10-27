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

using namespace std;

int main()
{
    Application& app = Application::getInstance();
    app.initWindow();

    Bot bot1("Bot 1", Position::Top);
    Bot bot2("Bot 2", Position::Left);
    Human human("Human", Position::Bottom);
    Bot bot3("Bot 3", Position::Right);
    std::vector<Player> players = { bot1, bot2, human, bot3 };

    Team teamA("Team A");
    teamA.addPlayer(bot1);
    teamA.addPlayer(human);

    Team teamB("Team B");
    teamB.addPlayer(bot2);
    teamB.addPlayer(bot3);

    Lobby lobby("Test lobby", vector<Team>{ teamA, teamB });

    app.startGame(lobby, GameMode::Offline);
    app.mainLoop();

    return 0;
}

#include <stdio.h>

#include "gtest/gtest.h"
#include "Rules.h"
#include "Card.h"
#include "Application.h"
#include "Player.h"

std::vector<Card> cards()
{
    Card card1(Hearts, King);
    Card card2(Clubs, King);
    Card card3(Hearts, Nine);
    Card card4(Hearts, Eight);
    Card card5(Spades, Ace);
    Card card6(Spades, Ten);
    std::vector<Card> cards = { card1, card2, card3, card4, card5, card6 };
    return cards;
}
TEST(Card, isCardGreater1)
{
    Card ace(Spades, Ace);
    Card ten(Spades, Ten);
    EXPECT_TRUE(ace.isGreaterThan(ten, Spades));
    EXPECT_FALSE(ten.isGreaterThan(ace, Spades));
}

TEST(Card, isCardGreater2)
{
    Card king(Hearts, King);
    Card queen(Clubs, King);
    EXPECT_TRUE(king.isGreaterThan(queen, Hearts));
    EXPECT_FALSE(king.isGreaterThan(queen, Clubs));
}

TEST(Rules, isTrickValid)
{
    Rules hearts(Hearts);
    Rules clubs(Clubs);
    Card king(Hearts, King);
    Card queen(Clubs, King);
    Trick trick;
    trick.addCard(queen);
    trick.addCard(king);
    trick.addCard(queen);
    EXPECT_FALSE(hearts.isTrickValid(trick));
    trick.addCard(king);
    EXPECT_TRUE(hearts.isTrickValid(trick));
}

TEST(Team, computeScore)
{
    Rules hearts(Hearts);
    Application::getInstance().getGame()->setRules(hearts);
    Team team("team1", Application::getInstance().getGame()->getHuman(), Application::getInstance().getGame()->getHuman());

    Trick trick;
    trick.addCard(cards()[0]);
    trick.addCard(cards()[1]);
    int expectedScore = 0;
    EXPECT_EQ(expectedScore, team.computeScore(trick));
    trick.addCard(cards()[2]);
    trick.addCard(cards()[3]);
    expectedScore = 22;
    EXPECT_EQ(expectedScore, team.computeScore(trick));
}

TEST(Player, getPlaybaleCards)
{
    Rules hearts(Hearts);
    Trick trick;
    Application::getInstance().getGame()->setRules(hearts);
    Application::getInstance().getGame()->addTrick(trick);
    std::shared_ptr<Player> human = Application::getInstance().getGame()->getHuman();
    std::vector<Card> Cards = cards();
    human->setCards(Cards);
    std::vector<Card> expectedCards = cards();
    EXPECT_EQ(expectedCards, human->getPlayableCards());
    trick.addCard(cards()[0]);
    Application::getInstance().getGame()->addTrick(trick);
    Cards.erase(Cards.begin());
    expectedCards = { cards()[2] };
    EXPECT_EQ(expectedCards, human->getPlayableCards());
    Trick trick2;
    trick2.addCard(cards()[3]);
    Application::getInstance().getGame()->addTrick(trick2);
    Cards = { cards()[0], cards()[1], cards()[2] };
    expectedCards = { cards()[0], cards()[2] };
    EXPECT_EQ(expectedCards, human->getPlayableCards());
}

TEST(Player, getGlobalBounds)
{
    std::shared_ptr<Player> human = Application::getInstance().getGame()->getHuman();
    cards()[0].setPosition(0, 100);
    cards()[1].setPosition(0, 120);
    human->setCards({ cards()[0], cards()[1] });
    sf::IntRect expectedRect(cards()[0].getGlobalPosition().x, cards()[1].getGlobalPosition().y * 0.9, cards()[0].getGlobalSize().x, cards()[0].getGlobalSize().y);
    EXPECT_EQ(expectedRect, human->getGlobalBounds());
}

TEST(Player, getCards)
{
    Trick trick;
    Application::getInstance().getGame()->setRules(Rules(Hearts));
    Application::getInstance().getGame()->addTrick(trick);
    std::shared_ptr<Player> human = Application::getInstance().getGame()->getHuman();
    human->setCards({ cards()[0], cards()[1] });
    std::vector<Card> card = { cards()[0], cards()[1] };
    human->playCard(cards()[2]);
    EXPECT_EQ(card, human->getCards());
}

TEST(Player, cardsForSuit)
{
    Application::getInstance().getGame()->setRules(Hearts);
    std::shared_ptr<Player> human = Application::getInstance().getGame()->getHuman();
    std::vector<Card> expectedCards = { cards()[0], cards()[2], cards()[3] };
    human->setCards(cards());
    EXPECT_EQ(expectedCards, human->cardsForSuit(Hearts));
    expectedCards = { cards()[1] };
    EXPECT_NE(expectedCards, human->cardsForSuit(Hearts));
}

TEST(Player, hasCard)
{
    Application::getInstance().getGame()->setRules(Hearts);
    std::shared_ptr<Player> human = Application::getInstance().getGame()->getHuman();
    std::vector<Card> card = { cards()[0], cards()[2], cards()[3] };
    human->setCards(card);
    EXPECT_TRUE(human->hasCard(cards()[0]));
    EXPECT_FALSE(human->hasCard(cards()[1]));
}

TEST(Team, getPlayers)
{
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    std::shared_ptr<Player> player3;
    std::shared_ptr<Player> player4;
    Team team1("Team1", player1, player2);
    Team team2("Team2", player3, player4);
    std::vector<std::shared_ptr<Player> > expectedPlayers = { player1, player2 };
    EXPECT_EQ(expectedPlayers, team1.getPlayers());
}


GTEST_API_ int main(int argc, char** argv)
{
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);

    Application& app = Application::getInstance();
    app.initWindow();
    app.initGame();

    return RUN_ALL_TESTS();
}

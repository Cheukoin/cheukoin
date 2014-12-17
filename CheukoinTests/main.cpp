#include <stdio.h>

#include "gtest/gtest.h"
#include "Rules.h"
#include "Card.h"
#include "Application.h"

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
    Application& application = Application::getInstance();
    application.initGame();
    Rules hearts(Hearts);
    Application::getInstance().getGame()->setRules(hearts);
    Team team("team1", Application::getInstance().getGame()->getHuman(), Application::getInstance().getGame()->getHuman());
    Card card1(Hearts, King);
    Card card2(Clubs, King);
    Card card3(Hearts, Nine);
    Card card4(Hearts, Eight);
    Trick trick;
    trick.addCard(card1);
    trick.addCard(card2);
    int expectedScore = 0;
    EXPECT_EQ(expectedScore, team.computeScore(trick));
    trick.addCard(card3);
    trick.addCard(card4);
    expectedScore = 22;
    EXPECT_EQ(expectedScore, team.computeScore(trick));
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

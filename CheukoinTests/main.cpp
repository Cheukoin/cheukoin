#include <stdio.h>

#include "gtest/gtest.h"
#include "Rules.h"
#include "Card.h"

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

GTEST_API_ int main(int argc, char** argv)
{
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);

    Application& app = Application::getInstance();
    app.initWindow();
    app.initGame();

    return RUN_ALL_TESTS();
}

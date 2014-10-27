#include <stdio.h>

#include "gtest/gtest.h"
#include "Rules.h"
#include "Card.h"

TEST(Rules, isCardGreater)
{
    Rules rules(Spades);
    Card ace(Spades, Ace);
    Card ten(Spades, Ten);
    EXPECT_TRUE(rules.isCardGreater(ace, ten));
    EXPECT_FALSE(rules.isCardGreater(ten, ace));
}

TEST(Rules, isCardGreater)
{
    Rules rules(Clubs);
    Card king(Hearts, King);
    Card queen(Clubs, King);
    EXPECT_TRUE(rules.isCardGreater(queen, king));
    EXPECT_FALSE(rules.isCardGreater(king, queen));
}

GTEST_API_ int main(int argc, char** argv)
{
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

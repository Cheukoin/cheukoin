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

GTEST_API_ int main(int argc, char** argv)
{
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

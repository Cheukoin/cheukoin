//
//  Constants.h
//  Cheukoin
//
//  Created by Gabriel Samain on 10/10/2014.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#ifndef __Cheukoin__Constants__
#define __Cheukoin__Constants__

#include <stdio.h>
#include <map>
#include <string>

#define PLAYER_COUNT 4

enum Suit {
    Clubs,
    Hearts,
    Diamonds,
    Spades
};

enum Value {
    Ace,
    King,
    Queen,
    Jack,
    Ten,
    Nine,
    Eight,
    Seven
};

enum GameMode {
    Online,
    Offline
};

std::map<Suit, std::string> const SuitNames = { { Clubs, "clubs" },
                                                { Hearts, "hearts" },
                                                { Diamonds, "diamonds" },
                                                { Spades, "spades" } };

std::map<Value, std::string> const ValueNames = { { Ace, "ace" },
                                                  { King, "king" },
                                                  { Queen, "queen" },
                                                  { Jack, "jack" },
                                                  { Ten, "10" },
                                                  { Nine, "9" },
                                                  { Eight, "8" },
                                                  { Seven, "7" } };

#endif /* defined(__Cheukoin__Constants__) */

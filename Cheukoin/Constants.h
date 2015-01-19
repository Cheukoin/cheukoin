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

#define PLAYER_COUNT 4 // LJ : Préférer une constante à un #define : C'est typé, et c'est respectueux
// LJ : des autres règles du C++ : int const PLAYER_COUNT = 4;
#define END_GAME_SCORE 1000

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

// LJ : Ici, un simple vector suffirait, pusique vous utilisez aussi ailleurs le fait que les enums vont avoir pour valeur 0...3 et 0...7
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

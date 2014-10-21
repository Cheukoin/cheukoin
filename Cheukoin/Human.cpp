//
//  Human.cpp
//  Cheukoin
//
//  Created by Corentin on 10/21/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "Human.h"

using namespace std;

Human::Human(string name, Position position)
    : Player(name, position)
{
}

Human::~Human()
{
}

void Human::initialize()
{
    Player::initialize();
}

void Human::play()
{
// TODO
}
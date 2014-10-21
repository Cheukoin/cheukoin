//
//  Human.h
//  Cheukoin
//
//  Created by Corentin on 10/21/14.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#ifndef __Cheukoin__Human__
#define __Cheukoin__Human__

#include "Player.h"

class Human : public Player {
public:
    Human(std::string name, Position position);
    ~Human();

    void initialize();
    void play();
    void update();
private:
    

};

#endif /* defined(__Cheukoin__Human__) */

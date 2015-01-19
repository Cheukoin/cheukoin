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

    void chooseBid(); // LJ : Il est plus clair de répéter 'virtual' pour les fonctions redéfinis dans les classes dérivées. En C++11,
					  // LJ : le mot clef 'override' est encore plus clair, et permet de s'assurer qu'on ne s'est pas trompé, même si
					  // LJ : la fonction de la classe de base est modifiée par la suite.

    void initialize();
    void play();
    void showLegalCards();
    Card chooseCard();
    void playCard(const Card& card);

private:
};

#endif /* defined(__Cheukoin__Human__) */

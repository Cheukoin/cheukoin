//
//  BidMaker.cpp
//  Cheukoin
//
//  Created by Gabriel Samain on 17/11/2014.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "BidMaker.h"

using namespace std;

BidMaker::BidMaker(string spriteName)
    : AnimatedObject(spriteName, sf::Vector2f(320, 163))
    , _currentBid(Bid(Spades, 0, ""))
    , _text(make_shared<sf::Text>())
    , _font(sf::Font())
{
    if (!_font.loadFromFile(resourcePath("sansation.ttf"))) {
        puts("Font file not loaded");
    }
    _text->setString("");
    _text->setFont(_font);
    _text->setCharacterSize(20);
    _text->setColor(sf::Color::White);
    _text->setPosition(20, 0);
    Application& app = Application::getInstance();
    setPosition(app.getWindow()->getSize().x / 2 - getGlobalSize().x / 2,
                app.getWindow()->getSize().y / 2 - getGlobalSize().y / 2);
}

sf::Text BidMaker::getText()
{
    return *_text;
}

void BidMaker::handleClickAtPosition(sf::Vector2i position)
{
    if (!_shouldStartGame()) {
        for (int column = 0; column < 5; column++) {
            for (int suit = 0; suit < 4; suit++) {
                sf::IntRect rectref = sf::IntRect(
                    getGlobalPosition().x + getGlobalSize().x * column / 5,
                    getGlobalPosition().y + getGlobalSize().y * suit / 4,
                    getGlobalSize().x / 5,
                    getGlobalSize().y / 4);

                if (rectref.contains(position)) {
                    setBid(Suit(suit), 80 + column * 20);
                    return;
                }
            }
        }
    }
}

void BidMaker::setBid(Suit asset, int value)
{
    if (!_shouldStartGame()) {
        shared_ptr<Game> _game = Application::getInstance().getGame();
        string currentBiddingPlayerName = _game->getCurrentBiddingPlayer()->getName();

        if (value > _currentBid.getAmount()) {
            _currentBid = Bid(asset, value, currentBiddingPlayerName);
            cout << currentBiddingPlayerName
                 << " bids "
                 << SuitNames.at(asset)
                 << " "
                 << value
                 << endl;

            _text->setString(_text->getString()
                             + "\n" + currentBiddingPlayerName
                             + " bids " + to_string(value)
                             + " " + SuitNames.at(asset));
        }

        else {
            cout << currentBiddingPlayerName << " skips" << endl;
            _text->setString(_text->getString() + "\n" + currentBiddingPlayerName + " skips ");
        }
        Application::getInstance().getGame()->goToNextBiddingPlayer();
    }
}

Bid BidMaker::getCurrentBid()
{
    return _currentBid;
}

bool BidMaker::_shouldStartGame()
{
	// LJ : Plutôt qu'un singleton, j'aurais préféré que la classe BidMaker possède une référence à la partie à laquelle elle
	// LJ : est liée. Ce qui permettrait par exemple à une évloution du jeu de permettre à un moteur de faire tourner plusieurs
	// LJ : parties en parallèle.

	// LJ : Je ne comprends pas trop le rôle de cette fonction : Elle a un nom qui ressemble à une simple demande d'information, mais on
	// LJ : voit qu'en fait, elle valide l'enchère.
    if (Application::getInstance().getGame()->getCurrentBiddingPlayer()->getName() == _currentBid.getPlayerName()) {
		// LJ : Le code suivant aurait marché : Application::getInstance().getGame()->setBid(make_shared<Bid>(_currentBid));
        Application::getInstance().getGame()->setBid(make_shared<Bid>(
            _currentBid.getSuit(), _currentBid.getAmount(), _currentBid.getPlayerName()));
        return true;
    }
    return false;
}

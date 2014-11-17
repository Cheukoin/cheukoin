//
//  BidMaker.cpp
//  Cheukoin
//
//  Created by Gabriel Samain on 17/11/2014.
//  Copyright (c) 2014 Corentin. All rights reserved.
//

#include "BidMaker.h"

using namespace std;

BidMaker::BidMaker(string spriteName, sf::Vector2f size)
    : AnimatedObject(spriteName, size)
    , _currentBid(Bid(Spades, 0, ""))
{
    Application& app = Application::getInstance();
    setPosition(app.getWindow()->getSize().x / 3, app.getWindow()->getSize().y / 3);
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
            cout << currentBiddingPlayerName << " bids " << asset << " " << value << endl;
        }
        else {
            cout << currentBiddingPlayerName << " skips" << endl;
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
    if (Application::getInstance().getGame()->getCurrentBiddingPlayer()->getName() == _currentBid.getPlayerName()) {
        Application::getInstance().getGame()->setBid(make_shared<Bid>(
            _currentBid.getSuit(), _currentBid.getAmount(), _currentBid.getPlayerName()));
        return true;
    }
    return false;
}

#ifndef __Cheukoin_Game__
#define __Cheukoin_Game__

class Bid;

class Game {
public:
    static Game& getInstance();

    void setCurrentBid(Bid* const& bid);
    Bid* getCurrentBid();

private:
    Game(){};
    Game(Game const&); // Don't Implement
    void operator=(Game const&); // Don't implement\

    Bid* _currentBid;
};

#endif
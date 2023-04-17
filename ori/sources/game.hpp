#pragma once
#include "player.hpp"

namespace ariel{
class Game
{

public:
    Player *p1;
    Player *p2;
    Player* winner;
    vector<Card>drawCards;
    int p1wins;
    int p2wins;
    int Draws;
    string gameLog;
    string lastTurn;
    string log;
    vector<Card> cards;
    Game(Player &, Player &);
    void buildandeal();
    void playTurn();
    Player* getWinner();
    void printStats();
    void printWiner();
    string printLog();
    string printLastTurn();
    void playAll();
};
}
#pragma once
#include <vector>
#include <string>
#include "card.hpp"
using namespace std;
//player class

namespace ariel{
class Player
{
    private:
    int Stacksize;
    string name;
    vector<Card> cards;
    int Takencards;
    vector<Card>Woncards;
    bool isPlaying;

    public:
    Player(string name);
    void getWoncards(vector <Card>&);
    void setCards(vector<Card> &);
    string getName();
    int stacksize();             // return the amount of cards in the stack
    int cardesTaken();           // return the total amount og cards that already took
    Card popCard();
    void addCardsTaken();
    void addMultiCardsTaken(int);
    void addCards(Card card);    //add card to packet
    bool getisPlaying();
    void setisPlaying(bool isPlaying); 
    int cardesTakenokok();



};
}
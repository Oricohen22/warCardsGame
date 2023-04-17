#include "player.hpp"
#include <string>
#include <iostream>

namespace ariel
{
    Player::Player(string name)
    {
        this->name = name;
        this->isPlaying = false;
        this->Takencards = 0;
    }

    Card Player::popCard()
    {
        if (cards.empty())
        {
            throw std::runtime_error("Player's card pack is empty");

        }

    Card card = cards.front();
    cards.erase(cards.begin());
    return card;
}

    string Player::getName()
    {
        return this->name;
    }

    void Player::setCards(vector<Card> &cards)
    {
        this->cards = cards;
    }

    void Player::setisPlaying(bool isPlaying)
    {
        this->isPlaying = isPlaying;
    }

    bool Player::getisPlaying()
    {
        return isPlaying;
    }

    int Player::stacksize()
    {
        return this->cards.size();
    }

     void Player::addCardsTaken(){
        (this)->Takencards++;
    }

    void Player::addMultiCardsTaken(int counter){
        for (size_t i = 0; i < counter; i++)
        {
            (this)->Takencards++;
        }
        
    }


    void Player::addCards(Card card)
    {
        (this)->Stacksize++;
        cards.push_back(card);
    }

    int Player::cardesTaken()
    {
        return Takencards;
    }

    void Player::getWoncards(vector<Card>& vec)
    {
        while (!vec.empty())
        {
            Woncards.push_back(vec.back());
            vec.pop_back();
        }
    }

    int Player::cardesTakenokok()
    {
        return Woncards.capacity();
    }
}

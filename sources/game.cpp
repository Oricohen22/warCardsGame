#include "game.hpp"
#include "card.hpp"
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

namespace ariel
{
    int stay = 1;
    Game::Game(Player &p1_, Player &p2_)
    {
        this->p1_ = &p1_;
        this->p2_ = &p2_;
        this->Draws = 0;
        (this)->winner = nullptr;
        if (p1_.getisPlaying() == true || p2_.getisPlaying() == true)
        {
            throw std::invalid_argument("Player(s) already in game and playing");
        }
        p1_.setisPlaying(true);
        p2_.setisPlaying(true);
        buildandeal();
    }

    void Game::buildandeal()
    {
        string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        string values[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                (this)->cards.push_back(Card(values[j], suits[i]));
            }
        }

        // shuffle the deck
        // srand((unsigned int)time(NULL)); // seed the random number generator with current time
        // random_shuffle((this)->cards.begin(), (this)->cards.end());
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        mt19937 rng(seed); // create a random number generator with the given seed
        shuffle(cards.begin(), cards.end(), rng);

        // deal the cards to the players
        for (int i = 0; i < 26; i++)
        {
            (this)->p1_->addCards((this)->cards.back());
            (this)->cards.pop_back();

            (this)->p2_->addCards((this)->cards.back());
            (this)->cards.pop_back();
        }
    }

    void Game::playTurn()
    {

        if (this->p1_->stacksize() == 0)
        {
            throw runtime_error("the game is Over!");
        }
        if (p1_->getName() == p2_->getName())
        {
            throw runtime_error("there is only one player");
        }
        Card c1_= this->p1_->popCard();
        Card c2_ = this->p2_->popCard();
            drawCards.push_back(c1_);
        drawCards.push_back(c2_);
        string log = p1_->getName() + " played " + c1_.toStringsuit() + c1_.toStringNumber();
        log += " " + p2_->getName() + " played " + c2_.toStringsuit() + c2_.toStringNumber() + ".";

        if ((c1_.getValue() == 2 && c2_.getValue() == 1) || (c1_.getValue() > c2_.getValue()))
        {
            p1wins++;
            p1_->getWoncards(drawCards);
            p1_->addCardsTaken();
            p1_->addCardsTaken();
            this->winner = p1_;
            this->lastTurn = this->p1_->getName() + " Won The Turn\n";
            this->gameLog += this->lastTurn + p2_->getName() + "Won the Turn\n";
        }
        else if ((c2_.getValue() == 1 && c1_.getValue() == 2) || (c2_.getValue() > c1_.getValue()))
        {
            p2wins++;
            p2_->getWoncards(drawCards);
            p2_->addCardsTaken();
            p2_->addCardsTaken();
            this->winner = p2_;
            this->lastTurn = this->p2_->getName() + " Won The Turn\n";
            this->gameLog += this->lastTurn + p2_->getName() + "Won the Turn\n";
        }
        else
        {
            while (c1_.getValue() == c2_.getValue() && stay)
            { // war situation
                cout<<"~~~~~~~~~~~~~WAR~~~~~~~~~~~~~~~`"<<endl;
                Draws++;
               if (p1_->stacksize() < 2)
               {
                p1_->getWoncards(drawCards);
                p2_->getWoncards(drawCards);
                stay = 0;
                break;
               }
               

                else if (p1_->stacksize() > 1)
                {
                    drawCards.push_back(p1_->popCard());
                    drawCards.push_back(p2_->popCard());

                    c1_ = p1_->popCard();
                    c2_ = p2_->popCard();
                    drawCards.push_back(c1_);
                    drawCards.push_back(c2_);
                }
            }
            if ((c1_.getValue() == 2 && c2_.getValue() == 1) || (c1_.getValue() > c2_.getValue()))
            {
                p1wins++;
                int counter = drawCards.size();
                p1_->getWoncards(drawCards);
                p1_->addMultiCardsTaken(counter);
                this->winner = p1_;
                this->lastTurn = this->p1_->getName() + " Won The Turn\n";
                this->gameLog += this->lastTurn + p2_->getName() + "Won the Turn\n";
            }
            else if ((c2_.getValue() == 1 && c1_.getValue() == 2) || (c2_.getValue() > c1_.getValue()))
            {
                p2wins++;
                int counter = drawCards.size();
                p2_->getWoncards(drawCards);
                p2_->addMultiCardsTaken(counter);
                this->winner = p2_;
                this->lastTurn = this->p2_->getName() + " Won The Turn\n";
                this->gameLog += this->lastTurn + p2_->getName() + "Won the Turn\n";
            }
        }
    }

void Game::printWiner()
{
    if (winner)
    {
        std::cout << winner->getName() << std::endl;
    }
    else
    {
        std::cout << "Tie!" << std::endl;
    }
}

Player *Game::getWinner()
{
    return (this)->winner;
}

void Game::playAll()
{
    while (0 < this->p1_->stacksize())
    {
        playTurn();
    }
}

string Game::printLastTurn()
{
    cout << this->lastTurn << endl;
    return lastTurn;
};

string Game::printLog()
{
    cout << this->gameLog << endl;
    return gameLog;
};

void Game::printStats()
{
    cout << "\n"
         << p1_->getName() << ":\n"
         << "win rate: " << ((double)p1wins / (p1wins + p2wins) * 100) << "%\n"
         << "cards won: " << p1_->cardesTaken()
         << endl;

    cout << "\n"
         << p2_->getName() << ":\n"
         << "win rate: " << ((double)p2wins / (p1wins + p2wins) * 100) << "%\n"
         << "cards won: " << p2_->cardesTaken()
         << endl;

    cout << "\ndraw rate: " << ((double)Draws / (p1wins + p2wins)) * 100 << "%\n"
         << "amount of draws: " << Draws
         << endl;
}

}
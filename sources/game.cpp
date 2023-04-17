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

    Game::Game(Player &p1, Player &p2)
    {
        this->p1 = &p1;
        this->p2 = &p2;
        this->Draws = 0;
        (this)->winner = nullptr;
        if (p1.getisPlaying() == true || p2.getisPlaying() == true)
        {
            throw std::invalid_argument("Player(s) already in game and playing");
        }
        p1.setisPlaying(true);
        p2.setisPlaying(true);
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
            (this)->p1->addCards((this)->cards.back());
            (this)->cards.pop_back();

            (this)->p2->addCards((this)->cards.back());
            (this)->cards.pop_back();
        }
    }

    void Game::playTurn()
    {

        if (this->p1->stacksize() == 0)
        {
            throw runtime_error("the game is Over!");
        }
        if (p1->getName() == p2->getName())
        {
            throw runtime_error("there is only one player");
        }
        Card c1 = this->p1->popCard();
        Card c2 = this->p2->popCard();
            drawCards.push_back(c1);
        drawCards.push_back(c2);
        string log = p1->getName() + " played " + c1.toStringsuit() + c1.toStringNumber();
        log += " " + p2->getName() + " played " + c2.toStringsuit() + c2.toStringNumber() + ".";

        if ((c1.getValue() == 2 && c2.getValue() == 1) || (c1.getValue() > c2.getValue()))
        {
            p1wins++;
            p1->getWoncards(drawCards);
            p1->addCardsTaken();
            p1->addCardsTaken();
            this->winner = p1;
            this->lastTurn = this->p1->getName() + " Won The Turn\n";
            this->gameLog += this->lastTurn + p2->getName() + "Won the Turn\n";
        }
        else if ((c2.getValue() == 1 && c1.getValue() == 2) || (c2.getValue() > c1.getValue()))
        {
            p2wins++;
            p2->getWoncards(drawCards);
            p2->addCardsTaken();
            p2->addCardsTaken();
            this->winner = p2;
            this->lastTurn = this->p2->getName() + " Won The Turn\n";
            this->gameLog += this->lastTurn + p2->getName() + "Won the Turn\n";
        }

        else
        {
            while (c1.getValue() == c2.getValue())
            { // war situation
                cout<<"~~~~~~~~~~~~~WAR~~~~~~~~~~~~~~~`"<<endl;
                Draws++;
               if (p1->stacksize() < 2)
               {
                p1->getWoncards(drawCards);
                p2->getWoncards(drawCards);
               }
               

                else if (p1->stacksize() > 1)
                {
                    drawCards.push_back(p1->popCard());
                    drawCards.push_back(p2->popCard());

                    c1 = p1->popCard();
                    c2 = p2->popCard();
                    drawCards.push_back(c1);
                    drawCards.push_back(c2);
                }
            }
            if ((c1.getValue() == 2 && c2.getValue() == 1) || (c1.getValue() > c2.getValue()))
            {
                p1wins++;
                int counter = drawCards.size();
                p1->getWoncards(drawCards);
                p1->addMultiCardsTaken(counter);
                this->winner = p1;
                this->lastTurn = this->p1->getName() + " Won The Turn\n";
                this->gameLog += this->lastTurn + p2->getName() + "Won the Turn\n";
            }
            else if ((c2.getValue() == 1 && c1.getValue() == 2) || (c2.getValue() > c1.getValue()))
            {
                p2wins++;
                int counter = drawCards.size();
                p2->getWoncards(drawCards);
                p2->addMultiCardsTaken(counter);
                this->winner = p2;
                this->lastTurn = this->p2->getName() + " Won The Turn\n";
                this->gameLog += this->lastTurn + p2->getName() + "Won the Turn\n";
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
    while (0 < this->p1->stacksize())
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
         << p1->getName() << ":\n"
         << "win rate: " << ((double)p1wins / (p1wins + p2wins) * 100) << "%\n"
         << "cards won: " << p1->cardesTaken()
         << endl;

    cout << "\n"
         << p2->getName() << ":\n"
         << "win rate: " << ((double)p2wins / (p1wins + p2wins) * 100) << "%\n"
         << "cards won: " << p2->cardesTaken()
         << endl;

    cout << "\ndraw rate: " << ((double)Draws / (p1wins + p2wins)) * 100 << "%\n"
         << "amount of draws: " << Draws
         << endl;
}

}
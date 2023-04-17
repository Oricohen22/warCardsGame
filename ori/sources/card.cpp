#include <string>
#include <iostream>
#include "card.hpp"

namespace ariel
{

    ariel::Card::Card(string number,string suit)
    {
        if (suit.empty() || number.empty())
        {
            // throw runtime_error;
            cout << "ERR" << endl;
        }
        this->number = number;
        this->suit = suit;
    }

    string Card::getnumber()
    {
        return this->number;
    }

    string Card::getsuit()
    {
        return this->suit;
    }

    int Card::getValue()
    {
        std::string values[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        int i = 0;
        while (i < 13)
        {
            if ((this)->number.compare(values[i]) == 0)
            {
                return i + 1;
            }
            i++;
        }
        return -1;
    }

    string Card::toStringsuit()
    {
        return this->suit;
    }

    string Card::toStringNumber()
    {
        return this->number;
    }

}

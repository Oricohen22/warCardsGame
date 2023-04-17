#pragma once
#include <string>
#include <iostream>
using namespace std;

namespace ariel
{

    class Card 
    {
    private:
        string number;
        string suit;

    public:
        Card(string suit, string number);
        string getnumber();
        string getsuit();
        int getValue();
        string toStringNumber();
        string toStringsuit();
    };
}
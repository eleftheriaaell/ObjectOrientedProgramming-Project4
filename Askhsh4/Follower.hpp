#ifndef _FOLLOWER_HPP_
#define _FOLLOWER_HPP_

#include "Card.hpp"

class Follower : public GreenCard{
    private:

    public:
        Follower(string, int);
        ~Follower();
        void print();
        int getType();
};

#endif
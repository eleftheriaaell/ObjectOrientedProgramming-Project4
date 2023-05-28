#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include "Card.hpp"

class Item : public GreenCard{
    private:
        int durability;
    public:
        Item(string S, int i);
        ~Item();

        int get_durability();
		int getType();

		void damageItem();

		void print();
		void print_durability();
};

#endif
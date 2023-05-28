#ifndef _HOLDING_HPP_
#define _HOLDING_HPP_

#include "Card.hpp"

class Holding : public BlackCard{
    private:
        int harvestValue;
        int chainBonus;
        Holding *upperHolding;
        Holding *subHolding;
    public:
        Holding(string , int );
        ~Holding();

        int get_harvestValue();
		int get_chainBonus();
		Holding* get_subHolding();
		Holding* get_upperHolding();
		int getType();

		void set_harvestValue(int);
		virtual void set_chainBonus(int);
		void set_subHolding(Holding*);
		void set_upperHolding(Holding*);

		void Print();
		void Print_Type();
		void Print_harvestValue();
		void Print_NamesubHolding();
		void Print_NameupperHolding();
		void Print_Chainbonus();
};

class StrongHold : public Holding{
    private:
        int honour;
        int money;
        int initialDefence;
    public:
        StrongHold(string, int);
        ~StrongHold();

		int get_honour();
		int get_initialDefence();

		void set_honour(int);
		void set_initialDefence(int);

		void print();
};

#endif
#ifndef _CARD_HPP_
#define _CARD_HPP_

#include <iostream>

using namespace std;

enum { ATTACKER=1, DEFENDER, SHOGUN, CHANCELLOR, CHAMPION};
enum { PLAIN=1, MINE, GOLD_MINE, CRYSTAL_MINE, FARMS, SOLO, STRONGHOLD};
enum { FOOTSOLDIER, ARCHER, SIEGER, CAVALRY, NAVAL, BUSHIDO};
enum { KATANA, SPEAR, BOW, NINJATO, WAKIZASHI};
enum {PERSONALITY = 1, HOLDING ,FOLLOWER, ITEM};


class Card{ 
    private:
        string Name;
        int Cost;
        int Type;
        bool isTapped;
    public:
        Card(string, int);
        virtual ~Card();

        void set_Name(string);
		void set_Cost(int);
		void set_isTapped(bool);        

        string get_Name();
		int get_Cost();
		bool get_isTapped();
		int get_Type();
		int get_Category();
		virtual int getType();

        void Print_Name();
		void Print_Cost();
		void Print_isTapped();
		virtual void Print_Type();
		virtual void Print();

};

class GreenCard : public Card{
    private:
        int attackBonus;
        int defenceBonus;
        int minimumHonour;
        int effectBonus;
        int effectCost;
        string cardText;
        bool bonus;
    public:
        GreenCard(string, int);
        virtual ~GreenCard();
        void set_attack(int);
        void set_defence(int);
        void set_minHon(int);
        void set_fxBonus(int);
        void set_fxCost(int);
        void set_bonus(bool);
//#################################
        int get_attackBonus();
		int get_defenceBonus();
		int get_minimumHonour();
		int get_effectCost();
		int get_effectBonus();
		string get_cardText();
		bool get_bonus();
//#################################
        void Print_attackBonus();
		void Print_defenceBonus();
		void Print_minimumHonour();
		void Print_effectCost();
		void Print_effectBonus();
		void Print_bought();
};

class BlackCard : public Card{
    private:    
        bool isRevealed;
    public:
        BlackCard(string, int);
        virtual ~BlackCard();
//#################################
        void set_isRevealed(bool);
//#################################
        bool get_isRevealed();
};

#endif
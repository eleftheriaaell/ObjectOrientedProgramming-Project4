#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "DeckBuilder.hpp"

class Player{
    private:
        list<GreenCard *> *FateDeck;
        list<BlackCard *> *DynastyDeck;
        list<GreenCard *> *hand;
        list<Holding *> *holdings;
        list<Personality *> *army;
        list<Personality *> battlePhaseArmy;
        list<BlackCard *> *provinces;
        StrongHold *Stats;
        int numberOfProvinces, turn_money;
        string Name;
        TypeConverter Converter;
    public:
        Player(list<GreenCard *> *, list<BlackCard *> *);
        ~Player();

    //Starting Phase
        void untapEverything();
        void drawFateCard();
        void drawDynastyCard();
        void revealProvinces();

    //Equip Phase
        void Harvest_Holdings(int);    
        void equipPersonalities();
    
    //Battle Phase
        void selectArmy();
        Player * selectEnemy(list<Player*> *);
        void attack();
        void defend();
        void printBattleList(list<Personality*> *);
        void retireSoldier(Personality*);
        void decreaseTheirStats(list<Personality*>&);

    //Economy Phase
        void buyProvince();
        void chainMines();
        void setchainBonus();

    //End Phase
        int return_handSize();
        void discardSurplusFateCards(int&);

    //Other
        void initializeMoney();
        char get_Answer();
        bool canBuyCard(int);
        int hand_Min();
        int ProvincesCost();
        int chooseHand();
        int chooseHolding();
        int chooseProvinces();
        int choosePersonality();
        int chooseBattlePersonality();
        int chooseItem(list<Item*>);
        int chooseFollower(list<Follower *>);
        void EquipItem(int);
        Holding *UpperHolding(int);
        Holding *SubHolding(int);
        void Buy_Item_Follower(Personality *, GreenCard *);
        string return_Name();
        int calculateAttackPoints();
        int calculateDefencePoints(int);
        int getInitialDefense();
        void loseProvince(int);
        int getNumberOfProvinces();
        void loseArmy(int, int);
        int getHonour();
        int getArmySize();

    //prints
        void printHand();
        void printProvinces();
        void printArmy();
        void printHoldings();
        void printGameStatistics();
        void printName();
};

#endif
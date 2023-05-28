#ifndef _PERSONALITY_HPP_
#define _PERSONALITY_HPP_

#include <list>
#include "Card.hpp"
#include "Follower.hpp"
#include "Item.hpp"

#define ItemsLimit  4
#define FollowersLimit  4

class Personality : public BlackCard{
    private:
        int attack;
        int defence;
        int honour;
        bool isDead;
        list<Follower *> FollowersList;
        list<Item *> ItemsList;
    public:
        Personality(string, int);
        ~Personality();
        int get_attack();
		int get_defence();
		int get_honour();
		bool get_isDead();
		int getType();
		int getNumberOfItems();
		int getNumberOfFollowers();
		void performSeppuku();
		int getFollowersAttack(list<Follower*>::iterator);
		list<Item *> getItemsList();
		list<Follower *> getFollowersList();
		void DestroyAll();
		void checkForDetach(int);
		void detach(Item *);
		void detach(Follower *);
		void set_attack(int);
		void set_defence(int);
		void set_honour(int);
		void set_isDead(bool);
		int equipItem(Item*);
        int equipFollower(Follower*);
        int disarmFollower(Follower*);
        int disarmItem(Item*);
        int IncreaseStats();
        int	DecreaseStats();
		void reduceItemsDurability();
		void reduceHonour();

		void print();
		void printFollowers();
		void printItems();
		void print_type();
		void print_attack();
		void print_defence();
		void print_honour();
		void print_isDead();
		void print_itemlimit();
		void print_followerlimit();
		void print_Honour();
		void print_numberOfFollowers();
		void print_numberOfItems();
};

#endif
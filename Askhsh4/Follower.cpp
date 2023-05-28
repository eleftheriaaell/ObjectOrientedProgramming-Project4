#include "Follower.hpp"

Follower::Follower(string Name, int Type)
:GreenCard(Name, Type){
    switch (Type){
    case FOOTSOLDIER:
        set_Cost(0); set_attack(2); set_defence(0); set_minHon(1); set_fxBonus(2); set_fxCost(1);
        break;
    case ARCHER:
        set_Cost(0); set_attack(0); set_defence(2); set_minHon(1); set_fxBonus(2); set_fxCost(1);
        break;
    case SIEGER:
        set_Cost(5); set_attack(3); set_defence(3); set_minHon(2); set_fxBonus(3); set_fxCost(2);
        break;
    case CAVALRY:
        set_Cost(3); set_attack(4); set_defence(2); set_minHon(3); set_fxBonus(4); set_fxCost(3);
        break;
    case NAVAL:
        set_Cost(3); set_attack(2); set_defence(4); set_minHon(3); set_fxBonus(4); set_fxCost(3);
        break;
    case BUSHIDO:
        set_Cost(8); set_attack(8); set_defence(8); set_minHon(6); set_fxBonus(8); set_fxCost(3);
        break;
    }
}

Follower::~Follower(){
	cout << get_Name() << " has just been destroyed" << endl;
}

int Follower::getType(){
	return FOLLOWER;
}

void Follower::print(){
	cout << endl << get_Name() << endl <<"Cost : " << get_Cost() << endl << "Attack Bonus : " << get_attackBonus()
         << endl <<"Defense Bonus : " << get_defenceBonus() << endl <<"Minimum Honor : " << get_minimumHonour() 
		 << endl<< "Effect Bonus : " << get_effectCost() << endl << "Effect Cost : " << get_effectBonus()
		 << endl << "Card Text : "<< get_cardText() << endl;
}
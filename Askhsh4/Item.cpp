#include "Item.hpp"

Item::Item(std::string Name,int Type)
:GreenCard(Name,Type){
	switch (Type) {
    	case(KATANA):
            set_Cost(5); set_attack(3); set_defence(3); set_minHon(1); 
            set_fxBonus(6); set_fxCost(5); durability= 4;  
            break;
    	case(SPEAR): 
            set_Cost(5); set_attack(3); set_defence(2); set_minHon(1); 
            set_fxBonus(6); set_fxCost(4); durability = 4;
            break;
    	case(BOW):
            set_Cost(10); set_attack(4); set_defence(4); set_minHon(2); 
            set_fxBonus(10); set_fxCost(4); durability = 6;
            break;
    	case(NINJATO):
            set_Cost(15); set_attack(6); set_defence(6); set_minHon(3); 
            set_fxBonus(10); set_fxCost(6); durability = 8;
            break;
    	case(WAKIZASHI):
            set_Cost(20); set_attack(8); set_defence(8); set_minHon(6); 
            set_fxBonus(15); set_fxCost(8); durability= 10; 
            break;
    }
}
Item::~Item(){
	std::cout << get_Name() << " has just been destroyed " << endl;
}

int Item::get_durability(){
	return durability;
}

int Item::getType(){
	return ITEM;
}

void Item::damageItem(){
	durability--;
}

void Item::print(){
	cout << "\n" << get_Name() << endl << "Cost : " << get_Cost() << endl << "Attack Bonus : " << get_attackBonus()
	<< endl << "Defense Bonus : " << get_defenceBonus() << endl << "Minimum Honor : " << get_minimumHonour ()
	<< endl << "Effect Bonus : " << get_effectCost() << endl <<"Effect Cost: " << get_effectBonus() 
	<< endl << "Durability	: " << durability << endl << "Card Text : " << get_cardText() <<endl;
}

void Item::print_durability(){
	cout << durability;
}

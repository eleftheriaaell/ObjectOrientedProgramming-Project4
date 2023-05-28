#include "Holding.hpp"

Holding::Holding(string Name,int Type)
: BlackCard(Name,Type){
	chainBonus = 0;
	subHolding = NULL;
	upperHolding = NULL;
	switch (Type){
    case(PLAIN):
       set_Cost(2);  harvestValue = 2;
        break;
    case(MINE):
        set_Cost(5);  harvestValue = 3;
        break;
    case(GOLD_MINE):
        set_Cost(7);  harvestValue = 5;
        break;
    case(CRYSTAL_MINE):
        set_Cost(12); harvestValue = 6;
        break;
    case(FARMS):
        set_Cost(3);  harvestValue = 4;
        break;
	case(SOLO):
        set_Cost(2);  harvestValue = 2;
        break;
    case(STRONGHOLD):
        set_Cost(0);  harvestValue = 5;
        break;
    }
}

Holding::~Holding(){
    cout << get_Name() << " has just been destroyed" << endl;
}

int Holding::get_harvestValue(){
	return harvestValue;
}

int Holding::get_chainBonus(){
	return chainBonus;
}

Holding* Holding::get_subHolding(){
	return subHolding;
}

Holding* Holding::get_upperHolding(){
	return upperHolding;
}

int Holding::getType(){
	return HOLDING;
}

void Holding::set_harvestValue(int New_harvestValue){
	harvestValue = New_harvestValue;
}

void Holding::set_chainBonus(int New_chainBonus){
	chainBonus = New_chainBonus;
}

void Holding::set_subHolding(Holding* New_subHolding){
	subHolding = New_subHolding;
}

void Holding::set_upperHolding(Holding* New_upperHolding){
	upperHolding = New_upperHolding;
}

void Holding::Print(){
	cout << get_Name() << endl <<"Cost : " << get_Cost() << endl<< "HarvestValue : " << harvestValue << endl;
}

void Holding::Print_Type(){
		switch(get_Type()) {
    		case(PLAIN):
                cout << "PLAIN" << endl;
                break;
    		case(MINE):
                cout << "MINE" << endl;
                break;
    		case(GOLD_MINE):
                cout << "GOLD_MINE" << endl;
                break;
    		case(CRYSTAL_MINE):
                cout << "CRYSTAL_MINE" << endl;
                break;
    		case(FARMS):
                cout << "FARMS" << endl;
                break;
			case(SOLO):
                cout << "SOLO" << endl;
                break;
    		case(STRONGHOLD):
                cout << "STRONGHOLD" << endl;
                break;
    	}
}
void Holding::Print_harvestValue(){
	cout << harvestValue << endl;
}

void Holding::Print_NamesubHolding(){
	subHolding->Print_Name();
}

void Holding::Print_NameupperHolding(){
	upperHolding->Print_Name();
}

void Holding::Print_Chainbonus(){
	cout << chainBonus << endl;
}

/////////////////////////////////////////////////////////////////////////


StrongHold::StrongHold(string Name,int Type)
:Holding(Name,Type){
    set_isRevealed(true);
	cout << endl << "Player: " << Name << " has entered the Gameboard!" << endl;

	honour = 5;
	cout << "Player: " << Name << " has " << honour << " honour points!" << endl;

	initialDefence = 5;
	cout << "Player: " << Name << " has " << initialDefence << " initialDefence!" << endl;

	money = 5;
	cout << "Player: " << Name << " has " << money << " gold!" << endl << endl;
}

StrongHold::~StrongHold(){}

int StrongHold::get_honour(){
	return honour;
}

int StrongHold::get_initialDefence(){
	return initialDefence;
}

void StrongHold::set_honour(int New_honour){
	honour = New_honour;
}

void StrongHold::set_initialDefence(int New_initialDefence){
	initialDefence = New_initialDefence;
}
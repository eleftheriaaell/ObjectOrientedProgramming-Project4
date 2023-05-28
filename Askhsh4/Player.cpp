#include "Player.hpp"
#include <cstdio>

Player::Player(list<GreenCard*>* GreenDeck, list<BlackCard*>* BlackDeck)
:FateDeck(GreenDeck) , DynastyDeck(BlackDeck){
	int i;
	cout << "Player's Username: ";
	cin >> Name;
	cout << endl;
	hand = new list<GreenCard*>();
	provinces = new list<BlackCard*>();
	army = new list<Personality*>();
	holdings = new list<Holding*>();
	Stats = new StrongHold(Name,STRONGHOLD);
	for (i = 0; i < 5; i++)
		this->drawFateCard();
	for (i = 0; i < 4; i++)
		this->drawDynastyCard();

	initializeMoney();
	numberOfProvinces = 4 ;
}

Player::~Player(){
	delete hand;
	delete provinces;
	delete army;
	delete holdings;
    delete Stats;
	delete FateDeck;
	delete DynastyDeck;
	delete Stats;
}

//Starting Phase

void Player::untapEverything(){
	list<BlackCard*>::iterator t_provinces;
	list<Holding*>::iterator t_holding;
	list<Personality*>::iterator t_personality;

	if (provinces->size() > 0) {
		for(t_provinces = provinces->begin(); t_provinces != provinces->end(); t_provinces++)
			(*t_provinces)->set_isTapped(false);
	}
	if (holdings->size() > 0){
		for(t_holding = holdings->begin(); t_holding != holdings->end(); t_holding++)
			(*t_holding)->set_isTapped(false);
	}
	if (army->size() > 0) {
		for(t_personality = army->begin(); t_personality != army->end(); t_personality++)
			(*t_personality)->set_isTapped(false);
	}
	Stats->set_isTapped(false);
	cout << "Everything was untapped." << endl;
}

void Player::drawFateCard(){
	if(DynastyDeck->size() > 0){
		hand->push_back(FateDeck->front());
		FateDeck->pop_front();
	}
	else
		cout << "You have zero Fate Cards!" << endl;
}

void Player::drawDynastyCard(){
	if(DynastyDeck->size() > 0){
		provinces->push_back(DynastyDeck->front());
		DynastyDeck->pop_front();
	}
	else
		cout << "You have zero Dynasty Cards!" << endl;
}

void Player::revealProvinces(){
	list<BlackCard *> ::iterator t_provinces;
	if(provinces->size() != 0)
	for(t_provinces = provinces->begin(); t_provinces != provinces->end(); t_provinces++)
		(*t_provinces)->set_isRevealed(true);
}

//Equip Phase

void Player::Harvest_Holdings(int money_needed){
	if(holdings->size() == 0){
		cout << "You have no Holdings" << endl;
		return;
	}
	list<Holding*> ::iterator t_Holding = holdings->begin();
	int choice;

	this->printHoldings();
	cout << "Select Holding to harvest: (press 0 to cancel)" << endl;
	choice = chooseHolding();
	if(choice == - 1)
		return;

	advance(t_Holding, chooseHolding());
	while((*t_Holding)->get_isTapped()){
		cout << "This Holding is tapped choose another one or press 0 to exit" << endl;
		choice = chooseHolding();
		if(choice == - 1)
			return;
		t_Holding = holdings->begin();
		advance(t_Holding, choice);
	}
	(*t_Holding)->set_isTapped(true);
	turn_money += (*t_Holding)->get_harvestValue() + (*t_Holding)->get_chainBonus();
	if (canBuyCard(money_needed)){
		cout << "You still dont have enough money" << endl;
		Harvest_Holdings(money_needed);
	}
	else
		cout << "You have collected enough money!" << endl;
}

void Player::equipPersonalities(){
	int choice;
	list<GreenCard*>::iterator t_Card = hand->begin();

	if(army->size() != 0){
		cout << "Do you want to equip items to your Personalities?(y/n)" << endl;
		if(get_Answer() == 'n')
			return;
		while(hand->size()){
			printArmy();
			printHand();
			cout << "Select an item or follower to equip." << endl;
			choice = chooseHand();
			t_Card = hand->begin();
			advance(t_Card,choice);

			if(canBuyCard((*t_Card)->get_Cost())) //here
				EquipItem(choice);
			else{
				cout << "Not enough money" << endl;
				if(canBuyCard((*t_Card)->get_Cost()) == true)
					cout << "Do you want to harvest money from Holdings? (y/n)" <<endl;
					if(get_Answer() == 'y'){
						Harvest_Holdings((*t_Card)->get_Cost());
						EquipItem(choice);
					}
			}
			cout << "Do you want to buy another Item or Follower? (y/n)" << endl;
			if(get_Answer() == 'n')
				break;
		}
	}
}

//Battle Phase

void Player::selectArmy(){
	int choice;

	list<Personality *>::iterator t_Personality = army->begin();
	battlePhaseArmy.clear();
	printArmy();
	cout << "Press 0 to finish: ";
	choice = choosePersonality();
	cout << endl;
	while (choice >= 0){
		advance(t_Personality,choice);
		if(!(*t_Personality)->get_isTapped()){
			battlePhaseArmy.push_back(*t_Personality);
			(*t_Personality)->set_isTapped(true);
		}
		cout << "Choose another troop or press 0 to finish." << endl;
		choice = choosePersonality();
	}
	cout << "Your army is :";
	printArmy();
}

Player *Player::selectEnemy(list<Player *> *Players){
	string choice;
	list<Player *>::iterator t_Player;
	do{
		cin >> choice;
		while(choice == this->return_Name()){
			cout << "You've tried to attack yourself, choose again another one:" << endl;
			cin >> choice;
		}
		for(t_Player = Players->begin(); t_Player != Players->end(); t_Player++)
			if(choice == (*t_Player)->return_Name()){
				(*t_Player)->printName(); cout << " Select troops to defend from "; this->printName(); cout << endl;
				(*t_Player)->selectArmy();
				return *t_Player;
			}
		cout << "Invalid Name choose a correct one" << endl;
	}while(choice != (*t_Player)->return_Name());
}


void Player::printBattleList(list<Personality*> *battlelist){
	list<Personality*>::iterator temp;
	temp = battlelist->begin();
	for( ; temp != battlelist->end(); temp++)
		(*temp)->Print_Name();
}

void Player::retireSoldier(Personality* soldier){
    list <Personality*>::iterator t_P;

	for (t_P = army->begin(); t_P != army->end(); t_P++) {
        if ((*t_P) == soldier){
            army->erase(t_P);
            soldier->performSeppuku();
	    	break; //Kane seg gt meta dn uparxei o itP kai kanei ++
        }
    }
}

void Player::decreaseTheirStats(list<Personality*>& Army){
	list<Personality*>::iterator t;

	if(!Army.size())
		return;

	for(t = Army.begin(); t != Army.end(); t++)
		if(((*t)->getNumberOfItems() > 0) || (((*t)->getNumberOfFollowers() > 0)))
            (*t)->DecreaseStats();
}

//Economy Phase
void Player::buyProvince(){
	list<BlackCard*>::iterator t_Province;
	Holding* t_Holding;
	Personality* t_Personality;

	int money_needed, type;
	char answer;

    cout << "Select a province to buy: (1 - 4)" << endl;
	t_Province = provinces->begin();
	advance(t_Province, chooseProvinces());

	money_needed = (*t_Province)->get_Cost();
	if (canBuyCard(money_needed) == false)
		cout << "Not enough money to purchase this province!" << endl;
	else {
       	if (turn_money >= money_needed) {
			turn_money -= money_needed;
       		cout << "Just purchased a province!" <<endl;
       		type = (*t_Province)->getType();
     		Converter.getCorrectType(*t_Province, &t_Personality, &t_Holding);
     		if ( type == HOLDING ) {
				t_Holding->set_isTapped(true);
       			t_Holding->set_isRevealed(true);
       			holdings->push_back(t_Holding);
       		}
			else if (type == PERSONALITY){
       			t_Personality->set_isRevealed(true);
       			army->push_back(t_Personality);
			}
     		provinces->erase(t_Province);
        	drawDynastyCard();
    	}
		else {
    		cout << "Do you want to harvest to buy a provience? (y/n) (You have " << turn_money << " gold)" << endl;
           	if (get_Answer() == 'y')
           		Harvest_Holdings(money_needed);
        }
    }
	drawFateCard();
}

void Player::chainMines(){
	list<Holding*>::iterator t_Holding;
	Holding* checkedHolding;
	int flagU = 0;
	int flagS = 0;
	int Type;

	for (t_Holding = holdings->begin(); t_Holding != holdings->end(); t_Holding++) {
		Type = (*t_Holding)->get_Category();

		if((*t_Holding)->get_upperHolding() == NULL){
			checkedHolding = UpperHolding(Type);
			if(checkedHolding != NULL){
				(*t_Holding)->set_upperHolding(checkedHolding);
				checkedHolding->set_subHolding(*t_Holding);
				cout << "Performing a connection with an upper holding!" << endl;
				flagU++;
				if(flagS)
					break;
			}
		}
		if((*t_Holding)->get_subHolding() == NULL){
			checkedHolding = SubHolding(Type);
			if(checkedHolding != NULL){
				(*t_Holding)->set_subHolding(checkedHolding);
				checkedHolding->set_upperHolding(*t_Holding);
				cout << "Performing a connection with a sub holding!" << endl;
				flagS++;
				if(flagU)
					break;
			}
		}
	}
}

void Player::setchainBonus(){
	list<Holding*>::iterator t_Holding;
	Holding* temp;
	Holding* temp2;
	int type,bonus,countChain = 0;

	for (t_Holding = holdings->begin(); t_Holding != holdings->end(); t_Holding++) {
	    countChain = 0;
		type = (*t_Holding)->get_Category();

		temp = (*t_Holding);
		while ((type == MINE) && (temp->get_chainBonus() == 0) ) {
			if( (temp->get_upperHolding() == NULL))
				break;
			countChain++;
			if(countChain == 2){ 			//FULL CHAIN
				bonus = 2;
				(*t_Holding)->set_chainBonus(bonus); 	//MINE
				bonus = 2 * (temp->get_harvestValue());
				temp->set_chainBonus(bonus); 			//GOLD-MINE
				temp2 = temp->get_upperHolding();
				bonus = 3 * (temp2->get_harvestValue());
				temp2->set_chainBonus(bonus); 			//CRYSTAL_MINE
				cout << "MINE-GOLDMINE-CRYSTALMINE created! Mine has ChainBonus: " << (*t_Holding)->get_chainBonus() << endl << "Gold Mine has ChainBonus: " << temp->get_chainBonus()
				<< endl << "Crystal Mine has ChainBonus: " << temp2->get_chainBonus() << endl;
				break;
			}
			temp = temp->get_upperHolding();
			if(temp->get_upperHolding() == NULL){ 	// MNE-GOLDMINE
				bonus = 2;
				(*t_Holding)->set_chainBonus(bonus); 	//MINE
				temp = (*t_Holding)->get_upperHolding();
				bonus = 4;
				temp->set_chainBonus(bonus); 		//GOLD_MINE
				cout << "MINE-GOLDMINE created! Mine has ChainBonus: " << (*t_Holding)->get_chainBonus() << endl << "Gold Mine has ChainBonus: " << temp->get_chainBonus() << endl;
				break;
			}
		}
		if ((type == GOLD_MINE) && ((*t_Holding)->get_chainBonus() == 0) && ((*t_Holding)->get_upperHolding() != NULL) && ((*t_Holding)->get_subHolding() == NULL)) {
			temp = (*t_Holding)->get_upperHolding();
			bonus = 5;
			(*t_Holding)->set_chainBonus(bonus); 	//GOLD_MINE
			bonus = temp->get_harvestValue();
			temp->set_chainBonus(bonus);		 //CRYSTAL-MINE
			cout << "GOLDMINE-CRYSTALMINE created! "<< endl;
		}
	}
}

//End Phase
int Player::return_handSize(){
	return hand->size();
}

void Player::discardSurplusFateCards(int& ch){
	list <GreenCard*>:: iterator t_Hand;
	t_Hand = hand->begin();
	advance(t_Hand , ch);
	hand->erase(t_Hand);
	delete *t_Hand;
}

//Other

void Player::initializeMoney(){
	turn_money = Stats->get_harvestValue();
}

char Player::get_Answer(){
	char input;
	while(input = getchar()){
		if(input == 'y')
			return input;
		else if(input == 'n')
			return input;
	}
}

bool Player::canBuyCard(int money){
	list<Holding *> ::iterator t_holdings;
	int total_money;

	if(money <= total_money)
		return true;
	return false;
}

int Player::hand_Min(){
	list<GreenCard*>::iterator t_H;

	int minCost;
	minCost = (*(hand->begin()))->get_Cost();
	cout << "Min cost is " << minCost << endl;
	for(t_H = hand->begin(); t_H != hand->end(); t_H++){
		if( (*t_H)->get_Cost() < minCost )
			minCost = (*t_H)->get_Cost();
	}
	return minCost;
}

int Player::ProvincesCost(){
	int minCost = 10000;
	list<BlackCard *>::iterator t_Provinces;
	for(t_Provinces = provinces->begin(); t_Provinces != provinces->end(); t_Provinces++){
		if((*t_Provinces)->get_isRevealed())
			if((*t_Provinces)->get_Cost() < minCost)
				minCost = (*t_Provinces)->get_Cost();
	}
}

int Player::chooseHand(){
	int choice;
	cin >> choice;
	while((choice < 1) || (choice > hand->size()))
		cin >> choice;
	return choice - 1;
}

int Player::chooseHolding(){
	int choice;
	cin >> choice;

	while((choice < 0) || (choice > holdings->size())){
		cout << "There is no such holding, try again: " << endl;
		cin >> choice;
	}
	return (choice - 1);
}

int Player::chooseProvinces(){
	list<BlackCard *>::iterator t_Province = provinces->begin();

	int choice;
	cin >> choice;
	while(choice < 1 || choice > 4){
		cout << "Invalid choice, choose another: ";
		cin >> choice;
	}
	advance(t_Province,choice-1);

	while((*t_Province)->get_isRevealed() == false){
		cout << "This province is not revealed! Choose another: ";
		cin >> choice;
		while(choice < 1 || choice > 4){
			cout << "There is no such card, choose another: ";
			cin >> choice;
		}
		t_Province=provinces->begin();
		advance(t_Province,choice-1);
		cout << (*t_Province)->get_Name() << endl;
	}
	cout << endl;
	return choice - 1;
}

int Player::choosePersonality(){
	int choice;
	cin >> choice;
	while((choice < 0) || (choice > army->size())){
		cout << "There is no such thing in your hand, choose again: ";
		cin >> choice;
		cout << endl;
	}
	return choice - 1;
}

int Player::chooseBattlePersonality(){
	int choice;
	cin >> choice;
	while((choice < 0) || (choice > battlePhaseArmy.size())){
		cout << "There is no such personality in your battle armt, choose again: ";
		cin >> choice;
		cout << endl;
	}
	return choice - 1;
}

int Player::chooseItem(list<Item *> t_List){
	int choice;
	cin >> choice;
	while((choice < 0) || (choice >t_List.size())){
		cout << "There is no such item, choose again: ";
		cin >> choice;
		cout << endl;
	}
	return choice - 1;
}

int Player::chooseFollower(list<Follower *> t_List){
	int choice;
	cin >> choice;
	while((choice < 0) || (choice >t_List.size())){
		cout << "There is no such Follower, choose again: ";
		cin >> choice;
		cout << endl;
	}
	return choice - 1;
}


Holding *Player::UpperHolding(int Type){
	if (Type != MINE || Type != GOLD_MINE)
		return NULL;

	list<Holding*>::iterator t_Holding;

	for (t_Holding = holdings->begin(); t_Holding != holdings->end(); t_Holding++)
		if (((*t_Holding)->get_Category() == Type + 1) && ((*t_Holding)->get_subHolding() == NULL))
			return (*t_Holding);
	return NULL;
}

Holding *Player::SubHolding(int Type){
	if (Type != CRYSTAL_MINE || Type != GOLD_MINE)
		return NULL;

	list<Holding*>::iterator t_Holding;

	for (t_Holding = holdings->begin(); t_Holding != holdings->end(); t_Holding++)
		if (((*t_Holding)->get_Category() == Type - 1) && ((*t_Holding)->get_upperHolding() == NULL))
			return (*t_Holding);
	return NULL;
}

void Player::EquipItem(int Item){

    list<Personality*>::iterator t_Personality;
    list<GreenCard*>::iterator t_Card;

    t_Card = hand->begin();
	advance(t_Card,Item);

    int type, choice;
    char answer;
    bool bought = false;

    cout << "Select a Personality to equip (0 to EXIT): " << endl;
    this->printArmy();
    t_Personality = army->begin();
	choice = choosePersonality();

	if (choice == -1)
		return;

	advance(t_Personality,choice);

    if((*t_Card)->get_minimumHonour() < (*t_Personality)->get_honour() ){
        type = (*t_Card)->getType();
        if(type == ITEM){
            if((*t_Personality)->getNumberOfItems() < 4)
                Buy_Item_Follower(*t_Personality ,*t_Card);
            else
                cout << "This Personality is full of Items." << endl;
        }
        else if(type == FOLLOWER) {
            if((*t_Personality)->getNumberOfFollowers() < 4)
                Buy_Item_Follower(*t_Personality , *t_Card);
            else
                cout << "This Personality is full of Followers." << endl;
        }
    }
    else
        cout << "This Personality is not honourable enough." << endl;
    if (!bought){
    	cout << "Do you want to equip this follower to another Personality (y/n)?" << endl;
    	if(get_Answer() == 'y')
        	EquipItem(choice);
	}
}

void Player::Buy_Item_Follower(Personality *t_Personality, GreenCard *t_Card){
    Follower* follower;
	Item* item;

    int type,cost = t_Card->get_Cost() ,effect_cost = t_Card->get_effectCost();
    char answer;

    type = t_Card->getType();
    turn_money -= cost;

    if (canBuyCard(effect_cost)){
        cout << "Would you like to purchase the effectBonus. (y/n)?" << endl;
        if(get_Answer() == 'y') {
            turn_money -= effect_cost;
            t_Card->set_bonus(true);
        }
    }
    Converter.getCorrectType(t_Card, &follower, &item);
    if ( type == ITEM)
        (t_Personality)->equipItem(item);
    else
        (t_Personality)->equipFollower(follower);
    if ((t_Card)->get_bonus() == true)
        cost += effect_cost;
    cout << "(" << cost << " removed)" <<endl;
    hand->remove(t_Card);
	delete t_Card;
}

string Player::return_Name(){
	return Name;
}

int Player::calculateAttackPoints(){
	int totalAttackPoints = 0;
	list<Personality *>::iterator t_Personality;
	for(t_Personality = battlePhaseArmy.begin(); t_Personality != battlePhaseArmy.end(); t_Personality++)
		totalAttackPoints+= (*t_Personality)->get_attack();
	return totalAttackPoints;
}

int Player::calculateDefencePoints(int choice){
	int totalDefencePoints = 0;
	list<Personality *>::iterator t_Personality;
	for(t_Personality = battlePhaseArmy.begin(); t_Personality != battlePhaseArmy.end(); t_Personality++)
		totalDefencePoints+= (*t_Personality)->get_attack();
	return totalDefencePoints;
}

int Player::getInitialDefense(){
	return Stats->get_initialDefence();
}

void Player::loseProvince(int choice){
	list<BlackCard *>::iterator t_Province = provinces->begin();
	provinces->erase(t_Province);
	numberOfProvinces--;
	cout << "Province has been defeated" << endl;
}

int Player::getNumberOfProvinces(){
	return numberOfProvinces;
}

void Player::loseArmy(int Case, int result){
	list<Personality *>::iterator t_Personality;

	switch (Case){
	case 1:

		for(t_Personality = battlePhaseArmy.begin(); t_Personality != battlePhaseArmy.end(); t_Personality++){
			(*t_Personality)->DestroyAll();
			army->erase(t_Personality);
			delete *t_Personality;
		}
		battlePhaseArmy.clear();
		break;
	case 2:
		int attack = 0, choice;
		printBattleList(&battlePhaseArmy);

		for(t_Personality = battlePhaseArmy.begin(); t_Personality != battlePhaseArmy.end(); t_Personality++){
			(*t_Personality)->DecreaseStats();
			if((*t_Personality)->get_honour() == 0){
				battlePhaseArmy.erase(t_Personality);
				army->erase(t_Personality);
				(*t_Personality)->Print_Name();
				cout << " will perform Seppuku!" << endl;
				(*t_Personality)->performSeppuku();

			}
		}

		cout << "Choose which Personality, you want to sucrifice: ";
		while(attack < 10 || battlePhaseArmy.size() > 0){
			choice = chooseBattlePersonality();
			advance(t_Personality,choice);
			cout << "Choose item or '0' to sucrifice whole Personality :";
			choice  = chooseItem((*t_Personality)->getItemsList());
			if(choice == -1){
				attack += (*t_Personality)->get_attack();
				(*t_Personality)->DestroyAll();
				army->erase(t_Personality);
				delete *t_Personality;
				continue;
			}
			else{
				list<Item *> t_List = (*t_Personality)->getItemsList();
				list<Item*>::iterator t_Item = t_List.begin();
				advance(t_Item, choice);
				attack += (*t_Item)->get_attackBonus();
				(*t_Personality)->detach(*t_Item);
			}
			cout << "Choose Follower to sucrifice :";
			choice = chooseFollower((*t_Personality)->getFollowersList());
		
			list<Follower *> t_Flist = (*t_Personality)->getFollowersList();
			list<Follower*>::iterator t_Follower = t_Flist.begin();
			advance(t_Follower, choice);
			attack += (*t_Follower)->get_attackBonus();
			(*t_Personality)->detach(*t_Follower);
		}		
			(*t_Personality)->checkForDetach(result);
		battlePhaseArmy.clear();
		break;
	}
}

int Player::getHonour(){
	return Stats->get_honour();
}

int Player::getArmySize(){
	return army->size();
}

//prints
void Player::printArmy(){
	list<Personality *> ::iterator t_personality;
	if(!army->size()){
		cout<< "You have no troops available!" << endl << endl;
		return;
	}
	for(t_personality = army->begin(); t_personality != army->end(); t_personality++)
		(*t_personality)->print();
}

void Player::printHoldings(){
	list<Holding *> ::iterator t_holding;
	for(t_holding = holdings->begin(); t_holding != holdings->end(); t_holding++)
		(*t_holding)->Print();
}

void Player::printHand(){
	if(hand->size() != 0){
		cout << "Player's Hand: ";
		list<GreenCard *> ::iterator t_hand;
		for(t_hand = hand->begin(); t_hand != hand->end(); t_hand++){
			(*t_hand)->Print_Name();
			cout << "	";
		}
	}
	cout << endl;
}

void Player::printProvinces(){
	if(provinces->size() != 0){
		list<BlackCard *> ::iterator t_provinces;
		cout << "Provinces: ";
		for(t_provinces = provinces->begin(); t_provinces != provinces->end(); t_provinces++){
			if((*t_provinces)->get_isRevealed() == true){
				(*t_provinces)->Print_Name();
				cout << "   ";
			}
			else
				cout << "Province is not revealed!" << endl;
		}
		cout << endl << endl;
	}
	else
		cout << "No provinces left!" << endl;
}

void Player::printGameStatistics(){
	cout << "Name: ";
	printName();
	cout << endl << "Provinces: ";
	printProvinces();
	cout << endl << "Army: ";
	printArmy();
	cout << endl << "Holdings: ";
	printHoldings();
}

void Player::printName(){
	cout << Name;
}

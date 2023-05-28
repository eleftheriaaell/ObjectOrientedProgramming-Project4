#include "Personality.hpp"


Personality::Personality(string Name,int Type)
:BlackCard(Name, Type){
    isDead = true;

	switch (Type) {
    	case(ATTACKER):
            set_Cost(5);  attack = 3;  defence = 2;   honour = 2;  
            break;
    	case(DEFENDER):
            set_Cost(5);  attack = 2;  defence = 3;   honour = 2;  
            break;
    	case(SHOGUN):    
            set_Cost(15); attack = 10; defence = 5;   honour = 8;  
            break;
    	case(CHANCELLOR):    
            set_Cost(15); attack = 5;  defence = 10;  honour = 8;  
            break;
    	case(CHAMPION):    
            set_Cost(30); attack = 20; defence = 20;  honour = 12; 
            break;
    }
}

Personality::~Personality(){
	cout << endl << get_Name() << " has just been destroyed!" << endl << endl;
}

int Personality::get_attack(){
	return attack;
}

int Personality::get_defence(){
	return defence;
}

int Personality::get_honour(){
	return honour;
}

bool Personality::get_isDead(){
	return isDead;
}

int Personality::getType(){
	return PERSONALITY;
}


void Personality::set_attack(int New_attack){
	attack = New_attack;
}

void Personality::set_defence(int New_defence){
	defence = New_defence;
}

void Personality::set_honour(int New_honour){
	honour = New_honour;
}

void Personality::set_isDead(bool New_isDead){
	isDead = New_isDead;
}

int Personality::equipItem(Item* card){
	cout << "Item equipped!" << endl;
	ItemsList.push_back(card);
	return 0;
}

int Personality::equipFollower(Follower* follower){
	cout << "Follower equipped!" << endl;
	FollowersList.push_back(follower);
	return 0;
}

int Personality::getNumberOfFollowers(){
	return FollowersList.size();
}

int Personality::getNumberOfItems(){
	return ItemsList.size();
}

int Personality::disarmItem(Item* item){
	list<Item*>::iterator temp;

	if(ItemsList.size() > 0){
		for(temp = ItemsList.begin(); temp != ItemsList.end(); temp++)
			if(*temp == item) {
				(*temp)->print();
				temp = ItemsList.erase(temp);
				if(*temp != NULL) 
					delete item;
				return 1;
			}
	}
}

int Personality::disarmFollower(Follower *follower){
	list<Follower*>::iterator temp;

	if(FollowersList.size() != 0){
		for(temp = FollowersList.begin(); temp != FollowersList.end(); temp++)
			if(*temp == follower) {
				(*temp)->print();
				temp = FollowersList.erase (temp);
				if(*temp != NULL) delete follower;
				return 1;
			}
	}
}

int Personality::IncreaseStats()
{
	list<Item*> temp (ItemsList);
	Item* itemtemp;
	while (!temp.empty()) {
		itemtemp = temp.front();
		attack = attack + itemtemp->get_attackBonus();
		defence = defence + itemtemp->get_defenceBonus();
		if (itemtemp->get_bonus() == true) {
			attack = attack + itemtemp->get_effectBonus();
			defence = defence + itemtemp->get_effectBonus();
		}
		temp.pop_front();
  	}
	list<Follower*> temp2 (FollowersList);
	Follower* followertemp;
	while (!temp2.empty()) {
		followertemp = temp2.front();
		attack = attack + followertemp->get_attackBonus();
		defence = defence + followertemp->get_defenceBonus();
		if (followertemp->get_bonus() == true) {
			attack = attack + followertemp->get_effectBonus();
			defence = defence + followertemp->get_effectBonus();
		}
		temp2.pop_front();
  	}
	cout << endl << "Increase Stats :" << endl;
	//this->print();
}

int Personality::DecreaseStats(){
	list<Item*> temp (ItemsList);
	Item* itemtemp;
	while (!temp.empty()) {
		itemtemp = temp.front();
		attack = attack - itemtemp->get_attackBonus();
		defence = defence - itemtemp->get_defenceBonus();
		if (itemtemp->get_bonus() == true) {
			attack = attack - itemtemp->get_effectBonus();
			defence = defence - itemtemp->get_effectBonus();
		}
		temp.pop_front();
  	}
	list<Follower*> temp2 (FollowersList);
	Follower* followertemp;
	while (!temp2.empty()) {
		followertemp = temp2.front();
		attack = attack - followertemp->get_attackBonus();
		defence = defence - followertemp->get_defenceBonus();
		if (followertemp->get_bonus() == true) {
			attack = attack - followertemp->get_effectBonus();
			defence = defence - followertemp->get_effectBonus();
		}
		temp2.pop_front();
  	}
	reduceHonour();
}

void Personality::print(){
		cout << endl << get_Name() << endl << "Cost	: " << get_Cost() << endl << "Attack : " << attack
		<< endl << "Defense	 : " << defence << endl <<"Honor : " << honour  << endl <<"Followers : "
		<< FollowersList.size() << endl << "Items : " << endl;
		printItems();
		printFollowers();
}

void Personality::printFollowers(){

	list<Follower*>::iterator follower;

	if(!FollowersList.size()) return;
	cout << get_Name() << " has " << FollowersList.size() << " Followers : "<< endl << endl;
	for(follower = FollowersList.begin(); follower != FollowersList.end(); follower++)
		(*follower)->print();
}

void Personality::printItems(){

	list<Item*>::iterator item;

	if(!ItemsList.size()) return;
	cout << get_Name() << " has " << ItemsList.size() << " Items : "<< endl << endl;
	for(item = ItemsList.begin(); item != ItemsList.end(); item++)
		(*item)->print();
}

void Personality::performSeppuku(){
	delete this;
}

void Personality::reduceHonour(){
	honour--;
}

void Personality::reduceItemsDurability(){
	list<Item*>::iterator t_Item;

	if(ItemsList.size() > 0){
		for(int i = 0; i < ItemsList.size(); i++){
			t_Item = ItemsList.begin();
			advance(t_Item,i);
			(*t_Item)->damageItem();
			if((*t_Item)->get_durability() == 0){
				delete (*t_Item);
				ItemsList.erase(t_Item);
				i--;
				if(ItemsList.size() == 0) 
					break;
			}
		}
	}
}

int Personality::getFollowersAttack(std::list<Follower*>::iterator follower){
	return (*follower)->get_attackBonus();
}

list<Item *> Personality::getItemsList(){
	return ItemsList;
}

list<Follower *> Personality::getFollowersList(){
	return FollowersList;
}


void Personality::DestroyAll(){
	Item *t_Item;
	Follower *t_Follower;
	while(FollowersList.size() != 0){
		t_Follower = FollowersList.front();
		FollowersList.pop_front();
		delete t_Follower;
	}
	while(ItemsList.size() != 0){
		t_Item = ItemsList.front();
		ItemsList.pop_front();
		delete t_Item;
	}
}

void Personality::checkForDetach(int result){
	list<Follower *>::iterator t_Follower;
	list<Item *>::iterator t_Item;

	for(t_Follower = FollowersList.begin(); t_Follower != FollowersList.end(); t_Follower++){
		if(result > (*t_Follower)->get_attackBonus())
			detach(*t_Follower);
		if(result > (*t_Item)->get_attackBonus())
			detach(*t_Item);
	}

}

void Personality::detach(Item *t_Item){
	ItemsList.remove(t_Item);
}

void Personality::detach(Follower *t_Follower){
	FollowersList.remove(t_Follower);
}

void Personality::print_type(){
		switch(get_Type()) {
    		case(ATTACKER) : cout << "ATTACKER" << endl;
    		case(DEFENDER) : cout << "DEFENDER" << endl;
    		case(SHOGUN) : cout << "SHOGUN" << endl;
    		case(CHANCELLOR) : cout << "CHANCELLOR" << endl;
    		case(CHAMPION) : cout << "CHAMPION" << endl;
    	}
}

void Personality::print_attack(){
	cout << attack << endl;
}

void Personality::print_defence(){
	cout << defence << endl;
}

void Personality::print_honour(){
	cout << honour << endl;
}

void Personality::print_isDead(){
	cout << isDead << endl;
}
void Personality::print_itemlimit(){
    cout << ItemsLimit << endl;
}
void Personality::print_followerlimit(){
    cout << FollowersLimit << endl;
}
void Personality::print_Honour(){
	cout << honour << endl;
}
void Personality::print_numberOfFollowers(){
	cout << FollowersList.size();
}
void Personality::print_numberOfItems(){
	cout << ItemsList.size();
}

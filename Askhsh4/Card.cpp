#include "Card.hpp"

Card::Card(string Name, int Type):
Name(Name), Type(Type){
    isTapped = false;
    Cost = 0;
}

Card::~Card(){}

string Card::get_Name(){
	return Name;
}
int Card::get_Cost(){
	return Cost;
}

bool Card::get_isTapped(){
	return isTapped;
}

int Card::get_Type(){
	return Type;
}

int Card::get_Category(){
	return Type;
}

int Card::getType(){}

void Card::Print(){}


void Card::set_Name(string New_Name){
	Name = New_Name;
}

void Card::set_Cost(int New_Cost){
	Cost = New_Cost;
}

void Card::set_isTapped(bool New_isTapped){
	isTapped = New_isTapped;
}

void Card::Print_Name(){
	cout << Name;
}
void Card::Print_Cost(){
	cout << Cost;
}

void Card::Print_isTapped(){
	cout << isTapped;
}

void Card::Print_Type(){
	cout << Type;
}

GreenCard::GreenCard(string Name,int Type)
:Card(Name, Type){
	bonus = false;
}

GreenCard::~GreenCard(){}

int GreenCard::get_attackBonus(){
	return attackBonus;
}
int GreenCard::get_defenceBonus(){
	return defenceBonus;
}

int GreenCard::get_minimumHonour(){
	return minimumHonour;
}

int GreenCard::get_effectCost(){
	return effectCost;
}

int GreenCard::get_effectBonus(){
	return effectBonus;
}

string GreenCard::get_cardText(){
	return cardText;
}

bool GreenCard::get_bonus(){
	return bonus;
}

void GreenCard::set_attack(int attack)
{
	attackBonus =  attack;
}
void GreenCard::set_defence(int defence)
{
	defenceBonus =  defence;
}
void GreenCard::set_minHon(int minHonour)
{
	minimumHonour =  minHonour;
}
void GreenCard::set_fxBonus(int effectB)
{
	effectBonus =  effectB;
}
void GreenCard::set_fxCost(int effectC)
{
	effectCost =  effectC;
}

void GreenCard::set_bonus(bool flag){
    if(flag == true)
        cout << "Just purchased a Bonus Effect" << endl;
	bonus = flag;
}

void GreenCard::Print_attackBonus(){
	cout << attackBonus;
}
void GreenCard::Print_defenceBonus(){
	cout << defenceBonus;
}
void GreenCard::Print_minimumHonour(){
	cout << minimumHonour;
}
void GreenCard::Print_effectCost(){
	cout << effectCost;
}
void GreenCard::Print_effectBonus(){
	cout << effectBonus;
}
void GreenCard::Print_bought()
{
	cout << bonus;
}

BlackCard::BlackCard(string Name,int Type)
: Card(Name, Type){
	isRevealed = false;
}

BlackCard::~BlackCard(){}

bool BlackCard::get_isRevealed(){
	return isRevealed;
}

void BlackCard::set_isRevealed(bool New_isRevealed)
{
	isRevealed = New_isRevealed;
}


#include "GameBoard.hpp"

GameBoard::GameBoard(){
	cout << "~ LEGEND OF THE 5 RINGS ~" << endl;
	
    initializeGameBoard();
}

GameBoard::~GameBoard(){
    cout<<"GameBoard to be destroyed"<<endl;
}

void GameBoard::initializeGameBoard(){
    int Number;
    do{
        cout << endl << "Give number of players (2-4) : ";
        cin >> Number;
        cout << endl;
    }while(Number < 2 || Number > 4);
    Player* player;
    
    list<GreenCard*>* FateDeck;
	list<BlackCard*>* DynastyDeck;
    list<Player *>::iterator t_Player;

    for(int i = 0; i < Number; i++){
        Deck = new DeckBuilder();		
        FateDeck = Deck->createFateDeck();
        DynastyDeck = Deck->createDynastyDeck();
        Deck->deckShuffler(FateDeck);
        Deck->deckShuffler(DynastyDeck);

        player = new Player(FateDeck, DynastyDeck);
        if(Players.size() == 0)
            Players.push_back(player);

        else{
            for(t_Player = Players.begin(); t_Player != Players.end(); t_Player++){
                if(player->getHonour() > (*t_Player)->getHonour()){
                    Players.push_front(player);
                    break;
                }
            }
            if(Players.size() == i){
                Players.push_back(player);
            }
        }   
    }
    printGameStatics();
}

void GameBoard::printGameStatics(){
    list<Player *>::iterator t_Player;
    for(t_Player = Players.begin(); t_Player != Players.end(); t_Player++)
        (*t_Player)->printGameStatistics();
}

void GameBoard::gameplay(){
    startingPhase();
}

void GameBoard::startingPhase(){   
    cout << "~~~~~~~~~~~~~~~ Starting Phase ~~~~~~~~~~~~~~~~~" << endl << endl;
    char answer;
    list<Player*>::iterator player;
    for(player = Players.begin(); player != Players.end(); player++){
        cout << "Player: ";
        (*player)->printName();
        cout << endl;
	    (*player)->untapEverything();
	    (*player)->drawFateCard();
	    (*player)->revealProvinces();
	    (*player)->printHand();
        (*player)->initializeMoney();
        (*player)->printProvinces();
    }

    equipPhase();
}

void GameBoard::equipPhase(){
    cout << "~~~~~~~~~~~~~~~~~ Equip Phase ~~~~~~~~~~~~~~~~~~~" << endl << endl;
    
    list<Player*>::iterator player;
    for(player = Players.begin(); player != Players.end(); player++){
        cout << "Player: ";
        (*player)->printName(); cout << "'s army is :";
        (*player)->printArmy();
        cout << endl;
        (*player)->printHand();
        (*player)->equipPersonalities();
    }
    battlePhase();
}

void GameBoard::battlePhase(){
    cout << "~~~~~~~~~~~~~~~~~ Battle Phase ~~~~~~~~~~~~~~~~~~~" << endl;

    list<Player*>::iterator player;

    for(player = Players.begin(); player != Players.end(); player++){
        if((*player)->getArmySize() == 0){
            (*player)->printName(); cout << " you don't have army to attack!" << endl << endl;
            continue;
        }
        cout << endl;
        (*player)->printName(); cout << " select troops to attack an enemy:" << endl;
        (*player)->selectArmy();
        cout << "Select enemy to attack: ";
        printPlayers();
        cout << endl;
        battle(*player, (*player)->selectEnemy(&Players));
        checkWinningCondition();
    }
    economyPhase();
}

void GameBoard::battle(Player *Attacker, Player*Defender){
    Attacker->printName(); cout << "Select province to attack" << endl;
    Defender->printProvinces();
    int choice = Defender->chooseProvinces();
    cout << "Battle between "; Attacker->printName(); cout << " & "; Defender->printName();
    cout << " BEGINS!!!" << endl << endl;

    int attackPoints = Attacker->calculateAttackPoints();
    int defencePoints = Defender->calculateDefencePoints(choice);

    if(attackPoints > (defencePoints + Defender->getNumberOfProvinces() )){
        Defender->loseProvince(choice);
        CheckPlayers();
    }
    else{
        int result = attackPoints - defencePoints;
        if(result > 0){
            Defender->loseArmy(1, result);
            Attacker->loseArmy(2, result);
        }
        else if(result == 0){
            Defender->loseArmy(1, result);
            Defender->loseArmy(1, result);
        }
        else if(result < 0){
            Defender->loseArmy(2, result);
            Attacker->loseArmy(1, result);
        }
    }
}

void GameBoard::economyPhase(){
    cout << "~~~~~~~~~~~~~~~ economyPhase ~~~~~~~~~~~~~~~" << endl << endl;
    
    list<Player*>::iterator player;
    for(player = Players.begin(); player != Players.end(); player++){
        cout << "Player "; (*player)->printName();
        cout << " would you like to buy any of the following provinces? (y/n)" << endl;
        (*player)->printProvinces();
        while((*player)->get_Answer() == 'y'){
            (*player)->buyProvince();
            (*player)->chainMines();
            (*player)->setchainBonus();
            
            cout << endl << "Player "; (*player)->printName();
            cout << " would you like to buy any of the following provinces? (y/n)" << endl;
            (*player)->printProvinces();
        }
    }
    cout << endl;
    endPhase();
}

void GameBoard::endPhase()
{
	int choice;
    
    cout << "~~~~~~~~~~~~~~ endPhase ~~~~~~~~~~~~~~~" << endl;
    
    list<Player*>::iterator player;
    
    for(player = Players.begin(); player != Players.end(); player++){
	    while((*player)->return_handSize() > 6){
            (*player)->printName();
		    (*player)->printHand();
            cout << endl;
		    do{
			    cout << "Too many Cards in your hand, choose which Card you want to discard: (choose number)" << endl;
			    cin >> choice;
		    }while((choice < 1) || (choice > (*player)->return_handSize()));
		    (*player)->discardSurplusFateCards(choice);
	    }
        cout << "Player: "; (*player)->printName();
	    print(*player);
    }
    cout << endl;
    startingPhase();
}

void GameBoard::print(Player* player){
    cout << endl << "Statistics of Player: " << player->return_Name()  << endl;
    
    player->printGameStatistics();
	player->printHand();	
}

void GameBoard::printPlayers(){
    list<Player *>::iterator t_Player;
    for(t_Player = Players.begin(); t_Player != Players.end(); t_Player++){
        (*t_Player)->printName();
        cout << "  ";
    }
}

void GameBoard::checkWinningCondition(){
    Player *Winner;
    CheckPlayers();
    if(Players.size() == 1)
        winningPhase();
}

void GameBoard::CheckPlayers(){
    list<Player *>::iterator t_Player;
    for(t_Player = Players.begin(); t_Player != Players.end(); t_Player++)
        if((*t_Player)->getNumberOfProvinces() == 0){
            (*t_Player)->printName(); cout << "is out of the game" << endl;
            Players.erase(t_Player);
            delete *t_Player;
        }
}

void GameBoard::winningPhase(){
    list<Player *>::iterator Winner;
    Winner = Players.begin();
    (*Winner)->printName();
    cout << " IS THE WINNER OF THE GAME!!!" << endl;
}
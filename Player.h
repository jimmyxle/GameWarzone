#pragma once
#include "Essentials.h"

class Territory;
class Map;
class Deck;
class Hand;
class Order;
class OrderList;
class Cards;
struct Pair;
class Observer;


class Player
{
private:
	int playerID;
	int numberOfArmies;
	int numberToDeploy;
	std::vector<Player*> listOfAllies;
	std::vector<Territory*> territoriesOwned;
	Hand* playerHand;
	Map* gameMap;
	OrderList* CommandList;
	bool TerritoryConquiredThisTurn;
	std::vector<Observer*> views;
public:
	Player();
	Player(int numberOfArmies);

	~Player();
	void setID(int _ID) { playerID = _ID; }
	int getID() { return playerID; }
	void setNumberOfArmies(int num) { numberOfArmies = num; }
	int getNumberOfArmies() { return numberOfArmies; }
	int getNumberOfTerritories() { return (int)territoriesOwned.size(); }
	int giveArmyUnits(int num) { numberOfArmies += num; return 0; }
	int addAlliance(Player* p);
	int clearAlliances();
	bool checkAlliance(Player* p);
	int addTerritory(Territory* t);
	int removeTerritory(int ID);
	int checkTerritoryOwnedByCurrentPlayer(int ID);
	bool checkTerritoryAvailable(int ID);
	Pair& movementDecision(std::vector<Pair> eligiblePairs, Pair& pair); //helper function to handle player input
	Pair& movementDecision(std::vector<Territory*> eligiblePairs, Pair& pair); //helper function to handle player input
	Player* movementDecision(std::vector<int> eligibleIDs); //helper function to handle player input
	int queryNumberOfUnitsToMove(Territory* sourceTerritory);
	int toAttack();
	//int toAttack(Territory* sourceTerritoryID); //TODO: delete later
	Pair& toAttack(Pair& pair);
	int toDefend();
	Pair& toDefend(Pair& pair);
	Pair& toAirlift(Pair& pair);
	Pair& toBomb(Pair& pair);
	Pair& toBlockade(Pair& pair);
	Player* toNegotiate();
	int getAdvanceArmyUnits(Territory* sourceTerritory);
	std::vector<Territory*> getTerritoriesOwned() { return territoriesOwned; }
	///Order* createDeploy(Player* tPlayer, int army, Territory* tTerritory, Map* _map);
	int setMap(Map* _map) { gameMap = _map; return 0; }
	Map* getMap() { return gameMap; }

	Hand* getPlayerHand() { return playerHand; }
	int readyArmyUnits() { numberToDeploy = numberOfArmies; numberOfArmies = 0; return 0; };//increase number to deploy
	int getNumberToDeploy() { return numberToDeploy; }
	int setNumberToDeploy(int num) { numberToDeploy = num; return 0; }
	void setConquerBool();
	void resetConquerBool();
	bool getConquerBool() { return TerritoryConquiredThisTurn; }


	Order* createCommandFromCard(Cards* card);
	void issueOrder();
	int drawCard(Deck& d);
	bool queryHandAction();
	bool queryIssueAction();
	bool executeNextOrder();
	void attach(Observer* obs) { views.push_back(obs); }
	void notify();


	std::string PlayerMessage;
	std::ostringstream stream;

};
#pragma once
#include "Essentials.h"

#define MAX_SIZE 999
class Player;
class Deck;
class Continent;

class Territory
{
private:
	int ID;
	int numberOfArmies;
	int previewedNumberOfArmies;
	Player* playerOwner;
	int X;
	int Y;
	std::string Name;
	std::vector<Territory*> Neighbors;
	Continent* PartOfContinent; 
public:
	Territory();
	Territory(int _ID, std::string _Name);
	~Territory();
	int getID() { return ID; }
	int getNumberOfArmies() { return numberOfArmies; }
	int setNumberOfArmies(int num);
	Player* getPlayerOwner() { return playerOwner; }
	int setPlayerOwner(Player* p);
	void setXY(int _x, int _y) { X = _x; Y = _y; }
	int getX() { return X; }
	int getY() { return Y; }
	std::vector<Territory*>& getNeighborVector() { return Neighbors; }
	std::string getName() { return Name; }
	bool checkIfNeighbor(Territory* targetTerritory);
	void addNeighbor(Territory* targetTerritory);
	Continent* getContinent() { return PartOfContinent; }
	void setContinent(Continent* c) { PartOfContinent = c; }
	void setPreviewedArmies(int deployed);
	int getPreviewedArmies() { return previewedNumberOfArmies; }
};

class Continent
{
public:
	std::vector<Territory*> Territories;
	std::string Name = "";

	int numberOfTerritories = 0;
	int bonus = 0;
	int color = 0;
	Player* ControlledByPlayer;

	Continent() { ControlledByPlayer = NULL; };
	~Continent() {};
	bool CheckIfAllContinentControl( Player *p);
};

class Map
{
private:
	int MapCounter;
	int numberOfPlayers;

	//std::vector<observer_concrete> obs_list;
	Deck* gameDeck; //TODO: may not need this, remove later if needed
	//OrderList* receiver;
public:
	std::vector<Territory*> ListOfNeighbors[MAX_SIZE]; /* array list */
	std::vector<Territory*> CompleteList;
	std::vector<Continent*> ListOfContinents;
	std::vector<Player*> ListOfPlayers;



	Map();
	~Map();

	Territory* createNode(int ID, std::string name);
	int addEdge(Territory* u, Territory* v);
	int createContinent(std::string _Name, int _Bonus);
	int addToContinent(int index, Territory* u);
	int printBoard();
	int checkConnectedGraph(int index, std::vector<Territory*> vec);
	int checkDuplicateCountries();
	std::set<int> TransferSet(std::vector<Territory*> vec);
	bool validate();
	int BFS(int index, std::vector<bool>& visited);
	int printNeighbors(Territory* t);
	void addPlayer(Player* p);
	Deck* getGameDeck() { return gameDeck; }
	void setGameDeck(Deck* deck) { gameDeck = deck; }

};

struct Pair
{
	Territory* Source;
	Territory* Target;
};

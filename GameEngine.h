#pragma once
#include "Essentials.h"

class Map;
class MapLoader;
class OrderList;

class GameEngine
{
private:
	Map *GameMap;
	MapLoader *GameMapLoader;
	int NumberOfPlayers;
	bool observersActive;
	Deck* GameDeck;
	std::vector<int> orderOfPlay;
	Player* CurrentPlayer;
	std::string CurrentPhase;
	std::string CurrentMessage;
	std::vector<class Observer*> views;


public:
	GameEngine();
	~GameEngine();

	Map* createValidMap(std::string file_location);
	std::string getFileLocation();
	Map* getGameMap() { return GameMap; } //used for testing
	int getNumberOfPlayers();
	bool getObserversActive();
	void startupPhase();
	void reinforcementPhase();
	void issueOrdersPhase();
	void executeOrdersPhase();
	void mainGameLoop();
	void checkIfPlayerEliminated();
	bool checkIfPlayerWon();
	void initObservers();
	void attach(Observer* obs) { views.push_back(obs); }
	void notify();
	Player* getCurrentPlayer() { return CurrentPlayer; }
	std::string getCurrentPhase() { return CurrentPhase; }
	std::string getCurrentMessage() { return CurrentMessage; }
};
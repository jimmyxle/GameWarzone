#pragma once
#include "Essentials.h"
class GameEngine;
class Player;

class Observer
{
protected: 

public:
	Observer();
	~Observer() = default;
	virtual void update() = 0;
};

class PhaseObserver : public Observer
{
protected:
	GameEngine* model;

private: 
	Player* CurrentPlayer;
	std::string CurrentPhase;
	std::string Message;
public:
	PhaseObserver(GameEngine *_model);
	void update();
};

class GameStatsObserver : public Observer
{
protected:
	Player* model;
private:
	int numOfTerritories;
	int totalNumOfTerritoes;
	std::string Message;
public:
	GameStatsObserver(Player* _model);
	void update();
};

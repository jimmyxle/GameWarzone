#pragma once
#include "GameObservers.h"




Observer::Observer(){}

PhaseObserver::PhaseObserver(GameEngine* _model) : Observer ()
{
	model = _model;
	model->attach(this);
	CurrentPlayer = NULL;
	CurrentPhase = "";
	Message = "";
}


void PhaseObserver::update()
{
	Player* playerTemp = model->getCurrentPlayer();
	if(!playerTemp)
	{
		CurrentPhase = model->getCurrentPhase();
		printf("||\t %s\n", CurrentPhase.c_str());
	}
	if (playerTemp != CurrentPlayer)
	{
		CurrentPlayer = playerTemp;
		
		printf("||\t Player [%d]'s ", CurrentPlayer->getID());
		CurrentPhase = model->getCurrentPhase();
		printf("%s\n", CurrentPhase.c_str());
	}
	std::string phaseTemp = model->getCurrentPhase();
	if (phaseTemp != CurrentPhase)
	{
		CurrentPhase = model->getCurrentPhase();
		printf("%s\n", CurrentPhase.c_str());

	}

	std::string tempMessage = model->getCurrentMessage();
	if (tempMessage != Message)
	{
		Message = tempMessage;
		printf("%s\n", Message.c_str());
	}

}

GameStatsObserver::GameStatsObserver(Player* _model) : Observer()
{
	model = _model;
	numOfTerritories = 0;
	totalNumOfTerritoes = 0;
	Message = "";
	model->attach(this);

}

void GameStatsObserver::update()
{
	printf("GameStateObserverStats\n");
	if(totalNumOfTerritoes == 0)
		totalNumOfTerritoes = (int)model->getMap()->CompleteList.size();

	float temp = (float)model->getNumberOfTerritories();
	if (temp != numOfTerritories)
	{
		numOfTerritories = model->getNumberOfTerritories();
		printf("Player %d controls %.2f %% \n", model->getID() ,temp/totalNumOfTerritoes);
	}

	std::string tempMessage = model->PlayerMessage;
	if (tempMessage != Message)
	{
		Message = tempMessage;
		printf("%s\n", Message.c_str());
	}
}
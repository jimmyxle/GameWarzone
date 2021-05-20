#include "GameEngine.h"

GameEngine::GameEngine() 
{
	GameMapLoader = new MapLoader();
	NumberOfPlayers = getNumberOfPlayers();
	if(getObserversActive())
		initObservers();
	std::string location = getFileLocation();

	GameMap = createValidMap(location);
	if (!GameMap)
	{
		printf("GameMap is invalid. Closing the application.\n");
		auto ch = _getch();
		exit(0);
	}

	GameDeck = new Deck();
	GameDeck->shuffle();
	GameMap->setGameDeck(GameDeck);

	for (int p = 0; p < NumberOfPlayers; p++)
	{
		Player* temp = new Player(50-NumberOfPlayers*5);
		GameMap->addPlayer(temp);
	}
	//CommandList = new OrderList();
	CurrentPlayer = NULL;
	CurrentPhase = "Initializing Game.";
	CurrentMessage = "Game successfully initialized.";
	notify();
}

GameEngine::~GameEngine()
{
	delete GameMapLoader;
	delete GameMap;
	delete GameDeck;
	for (int i = 0; i < views.size(); i++)
	{
		delete views[i];
	}
}

Map* GameEngine::createValidMap(std::string file_location = MAPFOLDER CANADA)
{
	GameMapLoader->readMapData(file_location);


	if (GameMapLoader->getMap()->validate())
	{
		printf("Valid Map Loaded.\n");

		GameMapLoader->getMap()->printBoard();
		return GameMapLoader->getMap();
	}
	else
	{
		printf("Failed to load map.\n");
		return NULL;
	}
}

std::string GameEngine::getFileLocation()
{
	std::string location = ""; 
	std::vector<std::string> allMaps;
	for (const auto& entry : std::filesystem::directory_iterator(MAPFOLDER))
	{
		std::string path_string (entry.path().u8string());
		allMaps.push_back(path_string);
	}

	for (int i = 0; i < allMaps.size(); i++)
	{
		size_t findstart = allMaps[i].find_last_of("\\");
		std::string map_name = allMaps[i].substr(findstart + (size_t)1);
		printf("[%d]%s\n",i, map_name.c_str());
	}

	int playerChoice = 0;
	bool invalid = false;

	while (!invalid)
	{
		printf("Please choose a map by entering the number:\n");
		std::cin >> playerChoice;

		if (playerChoice >= 0 && playerChoice < allMaps.size())
		{
			invalid = true;
		}
	}

	for (const auto& entry : std::filesystem::directory_iterator(allMaps[playerChoice]))
	{
		std::string path_string(entry.path().u8string());
		if (path_string.find(".map") != std::string::npos)
		{
			location = path_string;
			break;
		}
	}
	printf("%s\n", location.c_str());
	return location;
}

int GameEngine::getNumberOfPlayers()
{
	int playerChoice = 0;
	bool invalid = false;

	while (!invalid)
	{
		printf("Please enter the number of players [2-5]:\n");
		std::cin >> playerChoice;

		if (playerChoice >= 2 && playerChoice <= 5)
		{
			invalid = true;
		}
	}
	return playerChoice;
}

bool GameEngine::getObserversActive()
{
	int playerChoice = 0;
	bool invalid = false;

	while (!invalid)
	{
		printf("Would you like to enable observers?\n");
		printf("[0] No\n");
		printf("[1] Yes\n");
		std::cin >> playerChoice;

		if (playerChoice == 0 || playerChoice == 1)
		{
			invalid = true;
		}
	}
	return playerChoice;
}

void GameEngine::startupPhase()
{
	/*
	Determine the order of play
	*/
	CurrentPhase = "Start Up Phase";

	srand((unsigned int)time(NULL));
	std::vector<int> playerIndex;
	playerIndex.resize(NumberOfPlayers);
	for(int i = 0; i < NumberOfPlayers; i++)
	{ 
		playerIndex[i] = i;
	}

	int ID = 0, randomIndex = 0;
	while (playerIndex.size() > 0)
	{
		randomIndex = rand() % playerIndex.size();
		ID = playerIndex[randomIndex];
		orderOfPlay.push_back(GameMap->ListOfPlayers[ID]->getID());
		playerIndex.erase(playerIndex.begin() + randomIndex);
	}

	/*
	Give out one territory per player
	*/
	int numberOfTerritories = (int)GameMap->CompleteList.size();
	int addResult = -99;

	for (int i = 0; i < NumberOfPlayers; i++)
	{
		CurrentPlayer = GameMap->ListOfPlayers[orderOfPlay[i]];
		notify();
		do {
			addResult = GameMap->ListOfPlayers[orderOfPlay[i]]->addTerritory(GameMap->CompleteList[ rand()% numberOfTerritories ]);
			CurrentMessage = CurrentPlayer->PlayerMessage;
			notify();
		} while (addResult != 1);
	}
}

void GameEngine::reinforcementPhase()
{
	CurrentPhase = "Reinforcement Phase";

	int currentNumArmy=0;
	//Player* currentPlayer = NULL;
	for (int i = 0; i < NumberOfPlayers; i++)
	{
		CurrentPlayer = GameMap->ListOfPlayers[orderOfPlay[i]];

		currentNumArmy = CurrentPlayer->getNumberOfArmies();
		currentNumArmy += CurrentPlayer->getNumberOfTerritories()/3;
		int size = (int)GameMap->ListOfContinents.size();

		for (int i = 0; i < size; i++)
		{
			if (CurrentPlayer == GameMap->ListOfContinents[i]->ControlledByPlayer)
			{
				printf("%d Bonus for controlling %s\n", GameMap->ListOfContinents[i]->bonus,
					GameMap->ListOfContinents[i]->Name.c_str());
				currentNumArmy += GameMap->ListOfContinents[i]->bonus;
			}
		}

		CurrentPlayer->setNumberOfArmies(0);
		if (currentNumArmy < 3)
			currentNumArmy = 3;
		CurrentPlayer->setNumberToDeploy(currentNumArmy);

		CurrentPlayer->stream.clear();
		CurrentPlayer->stream.str("");
		CurrentPlayer->stream<<"Player "<< CurrentPlayer->getID() << " received "<< currentNumArmy << " unit(s).";
		CurrentMessage = CurrentPlayer->stream.str();
		notify();


	}
}

void GameEngine::issueOrdersPhase()
{
	CurrentPhase = "Issue Orders Phase";

	bool boolPlayCard = true;
	bool boolIssueCommand = true;
	std::vector<bool> boolPlayerDone;
	int numberOfDonePlayers =0;
	for (int i = 0; i < NumberOfPlayers; i++)
	{
		boolPlayerDone.push_back(false);
	}

	int i = 0;
	while(numberOfDonePlayers < NumberOfPlayers)
	{
		//keep cycling through players until number of done players == total num of players
		if (i == NumberOfPlayers)
			i = 0;

		if (!boolPlayerDone[i])
		{
			CurrentPlayer = GameMap->ListOfPlayers[orderOfPlay[i]];
			notify();

			boolIssueCommand = CurrentPlayer->queryIssueAction();


			if (boolIssueCommand)
			{
				CurrentPlayer->issueOrder();
				CurrentMessage = CurrentPlayer->PlayerMessage;
				notify();

			}

			boolPlayerDone[i] = true;
			numberOfDonePlayers++;
			


		}
		i++;


	}

}

void GameEngine::executeOrdersPhase()
{
	CurrentPhase = "Execute Orders Phase";

	std::vector<bool> boolPlayerDone;
	for (int i = 0; i < NumberOfPlayers; i++)
	{
		boolPlayerDone.push_back(false);
	}

	int i = 0, numberOfDonePlayers = 0;
	bool orderExecuted = false; 
	while (numberOfDonePlayers < NumberOfPlayers)
	{
		if (i == NumberOfPlayers)
			i = 0;
		if (!boolPlayerDone[i])
		{
			CurrentPlayer = GameMap->ListOfPlayers[orderOfPlay[i]];

			orderExecuted = CurrentPlayer->executeNextOrder();

			if (!orderExecuted)
			{
				boolPlayerDone.push_back(true);
				numberOfDonePlayers++;
			}
			else
			{
				CurrentMessage = CurrentPlayer->PlayerMessage;
				notify();
			}

		}
		i++;
	}

	for (int i = 0; i < NumberOfPlayers; i++)
	{
		CurrentPlayer = GameMap->ListOfPlayers[orderOfPlay[i]];

		if (CurrentPlayer->getConquerBool())
		{
			//printf("Player [%d] conquered a territory this turn. Draw a card.\n",
			//	CurrentPlayer->getID());
			CurrentPlayer->drawCard(*GameDeck);

			CurrentPlayer->stream.clear();
			CurrentPlayer->stream.str("");
			CurrentPlayer->stream << "Player " << CurrentPlayer->getID() << "conquered a territory this turn. Draw a card.";
			CurrentMessage = CurrentPlayer->stream.str();
			notify();

		}
		CurrentPlayer->resetConquerBool();
		CurrentPlayer->clearAlliances();
	}

}


void GameEngine::mainGameLoop()
{

	bool isGameFinished = false;

	while (!isGameFinished)
	{
		checkIfPlayerEliminated();
		if (!checkIfPlayerWon())
		{
			reinforcementPhase();
			issueOrdersPhase();
			executeOrdersPhase();
		}
		else
		{
			Player* winner = GameMap->ListOfPlayers[*orderOfPlay.begin()];

	/*		CurrentMessage = "Player " + winner->getID() + " won!";
			notify();*/
			printf("Player [%d] won!\n", winner->getID());
		}

	}
}

void GameEngine::checkIfPlayerEliminated()
{
	for (int i = 0; i < orderOfPlay.size(); i++)
	{
		if (GameMap->ListOfPlayers[i]->getNumberOfTerritories() == 0)
		{
			orderOfPlay.erase(orderOfPlay.begin() + i);
			printf("[%d] player was eliminated.\n", GameMap->ListOfPlayers[i]->getID());
		}
	}
}

bool GameEngine::checkIfPlayerWon()
{
	if (orderOfPlay.size() == 1)
	{
		return true;
	}
	else
	{
		return false;
	}


}

void GameEngine::initObservers()
{
	PhaseObserver* phaseObs = new PhaseObserver(this);

}

void GameEngine::notify()
{
	for (int i = 0; i < views.size(); i++)
	{
		views[i]->update();
	}
}
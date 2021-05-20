#include "Player.h"

/* Player class */

Player::Player()
{
	playerID = 0;
	numberOfArmies = 0;
	numberToDeploy = 0;
	playerHand = new Hand();
	gameMap = nullptr;
	CommandList = new OrderList();
	TerritoryConquiredThisTurn = false;
	PlayerMessage = "";
}

Player::Player(int _numberOfArmies)
{
	playerID = 0;
	numberOfArmies = _numberOfArmies;
	numberToDeploy = 0;
	playerHand = new Hand();
	gameMap = nullptr;
	CommandList = new OrderList();
	TerritoryConquiredThisTurn = false;
	PlayerMessage = "";

}

Player::~Player() 
{
	delete playerHand;
	delete CommandList;
}

// For negotiatie card/command
int Player::addAlliance(Player* p)
{
	listOfAllies.push_back(p);

	return 0;
}

int Player::clearAlliances()
{
	listOfAllies.clear();
	return 0;
}

bool Player::checkAlliance(Player* p)
{
	for (int i = 0; i < listOfAllies.size(); i++)
	{
		if (listOfAllies[i] == p)
		{
			return true;
		}
	}
	return false;
}

int Player::addTerritory(Territory* t)
{
	if (checkTerritoryAvailable(t->getID()))
	{

		territoriesOwned.push_back(t);
		t->setPlayerOwner(this);

		stream.clear();
		stream.str("");
		stream << "Territory ["<< t->getID() << "] is now owned by player ["<<t->getPlayerOwner()->getID()<<"]";
		PlayerMessage = stream.str();
		
		t->getContinent()->CheckIfAllContinentControl(this);
		return 1;
	}
	else
	{
		stream.clear();
		stream.str("");
		stream << "Territory [" << t->getID() << "] is already owned by player [" << t->getPlayerOwner()->getID() << "]";
		PlayerMessage = stream.str();

		return 0;

	}
}

int Player::removeTerritory(int ID)
{
	int index = checkTerritoryOwnedByCurrentPlayer(ID);
	if (index > -1)
	{
		//printf("Territory [%d] is no longer owned by player [%d]\n", ID, getID());
		if (territoriesOwned[index]->getContinent()->ControlledByPlayer == this)
		{
			territoriesOwned[index]->getContinent()->ControlledByPlayer = NULL;
		}
		territoriesOwned[index]->setPlayerOwner(nullptr);
		territoriesOwned.erase(territoriesOwned.begin() + index);


		return 1;
	}
	else
	{
		return 0;
	}



}

//check if the territory belongs to the player. returns a negative number if false
int Player::checkTerritoryOwnedByCurrentPlayer(int ID)
{
	for (int i = 0; i < territoriesOwned.size(); i++)
	{
		if (territoriesOwned[i]->getID() == ID)
		{
			return i;
		}
	}
	return -1;
}

bool Player::checkTerritoryAvailable(int ID)
{
	if (gameMap->CompleteList[ID]->getPlayerOwner() != nullptr)
		return false;
	return true;
}


bool findElement(std::vector<int> vec, int target)
{
	if (vec.size() <= 0)
	{
		return false;
	}
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == target)
		{

			return true;
		}
	}
	return false;
}


Pair& Player::movementDecision( std::vector<Pair> eligiblePairs, Pair& pair)
{
	bool correct = false;
	int playerChoice = -99;
	do
	{
		printf("List of eligible targets: \n");
		for (int i = 0; i < eligiblePairs.size(); i++)
		{
			printf("(%d) [%d] %s -> [%d] %s\n",i, eligiblePairs[i].Source->getID(),
				gameMap->CompleteList[eligiblePairs[i].Source->getID()]->getName().c_str(),
				eligiblePairs[i].Target->getID(),
				gameMap->CompleteList[eligiblePairs[i].Target->getID()]->getName().c_str());
		}
		printf("\n");
		printf("Choose an option (integer):\n");
		std::cin >> playerChoice;

		if (playerChoice >= 0 && playerChoice < eligiblePairs.size())
		{
					pair.Source = eligiblePairs[playerChoice].Source;
					pair.Target = eligiblePairs[playerChoice].Target;
					correct = true;
		}
	} while (!correct);
	return pair;
}

Pair& Player::movementDecision(std::vector<Territory*> eligiblePairs, Pair& pair) //helper function to handle player input
{
	bool correct = false;
	int playerChoice = -99;
	do
	{
		printf("List of eligible targets: \n");
		for (int i = 0; i < eligiblePairs.size(); i++)
		{
			printf("(%d) [%d] %s\n", i, eligiblePairs[i]->getID(),
				gameMap->CompleteList[eligiblePairs[i]->getID()]->getName().c_str());
		}
		printf("\n");
		printf("Choose an option (integer):\n");
		std::cin >> playerChoice;

		if (playerChoice >= 0 && playerChoice < eligiblePairs.size())
		{
			pair.Source = NULL;
			pair.Target = eligiblePairs[playerChoice];
			correct = true;
		}
	} while (!correct);
	return pair;
}

Player* Player::movementDecision(std::vector<int> eligibleIDs) //helper function to handle player input
{
	bool correct = false;
	int playerChoice = -99;
	Player* temp = NULL;
	do
	{
		printf("List of eligible targets: \n");
		for (int i = 0; i < eligibleIDs.size(); i++)
		{
			printf("(%d) Player [%d]\n", i, gameMap->ListOfPlayers[eligibleIDs[i]]->getID());
		}
		printf("\n");
		printf("Choose an option (integer):\n");
		std::cin >> playerChoice;

		if (playerChoice >= 0 && playerChoice < eligibleIDs.size())
		{
			temp = gameMap->ListOfPlayers[eligibleIDs[playerChoice]];
			correct = true;
		}
	} while (!correct);
	return temp;
}

int Player::queryNumberOfUnitsToMove(Territory* sourceTerritory)
{
	bool correct = false;
	int playerChoice = -99;
	int numberOfUnits = 0;
	if (sourceTerritory)
		numberOfUnits = sourceTerritory->getNumberOfArmies();
	else
		numberOfUnits = numberToDeploy;
	do
	{
		printf("You can deploy [1 - %d] units:\n", numberOfUnits);
		std::cin >> playerChoice;

		if (playerChoice > 0 && playerChoice <= numberOfUnits)
		{
			correct = true;
		}
	} while (!correct);
	return playerChoice;
}

//List all territories owned and returns the ID of the territory to atk
int Player::toAttack()
{
	printf("To Attack: \n");
	int ID = 0;
	std::vector<int> eligibleIDs;
	for (int i = 0; i < territoriesOwned.size(); i++)
	{
		for (int j = 0; j < territoriesOwned[i]->getNeighborVector().size(); j++)
		{
			Territory* target = territoriesOwned[i]->getNeighborVector()[j];
			ID = target->getID();
			if (!findElement(eligibleIDs, ID) && target->getPlayerOwner() != this)
			{
				eligibleIDs.push_back(ID);
			}
		}
	}
	printf("\n");
	if (eligibleIDs.size() <= 0)
	{
		printf("No available targets!\n");
		return -99;
	}
	return 1;
}

Pair& Player::toAttack(Pair& pair)
{
	std::vector<int> eligibleIDs;
	std::vector<Pair> eligiblePairs;
	
	printf("To Attack: \n");
	int ID = 0;
	for (int i = 0; i < territoriesOwned.size(); i++)
	{
		for (int j = 0; j < territoriesOwned[i]->getNeighborVector().size(); j++)
		{
			Territory* target = territoriesOwned[i]->getNeighborVector()[j];
			ID = target->getID();
			if (!findElement(eligibleIDs, ID) && target->getPlayerOwner() != this)
			{
				eligibleIDs.push_back(ID);
				Pair temp = Pair();
				temp.Source = territoriesOwned[i];
				temp.Target = target;
				eligiblePairs.push_back(temp);
			}
		}
	}
	printf("\n");
	if (eligibleIDs.size() <= 0)
	{
		printf("No available targets!\n");
		return pair;
	}
	return movementDecision(eligiblePairs, pair);
}



int Player::toDefend()
{
	std::vector<int> eligibleIDs;
	printf("To defend:\t");
	for (int i = 0; i < territoriesOwned.size(); i++)
	{
		int ID = territoriesOwned[i]->getID();
		if (!findElement(eligibleIDs, ID))
		{
			eligibleIDs.push_back(ID);
		}
	}
	printf("\n");

	if (eligibleIDs.size() <= 0)
	{
		return -99;
	}

	bool correct = false;
	int playerChoice = -99;
	do
	{
		printf("List of eligible targets: \n");
		for (int i = 0; i < eligibleIDs.size(); i++)
		{
			printf("%d \t", eligibleIDs[i]);
		}
		printf("\n");
		printf("Choose a territory to defend (integer):\n");
		std::cin >> playerChoice;

		for (int i = 0; i < eligibleIDs.size(); i++)
		{
			if (playerChoice == eligibleIDs[i])
			{
				correct = true;
				break;
			}
		}
	} while (!correct);

	return playerChoice;
}


Pair& Player::toDefend(Pair& pair)
{
	std::vector<int> eligibleIDs;
	std::vector<Pair> eligiblePairs;


	printf("To Defend: \n");
	int ID = 0;
	for (int i = 0; i < territoriesOwned.size(); i++)
	{
		if (territoriesOwned[i]->getNumberOfArmies() > 0)
		{
			for (int j = 0; j < territoriesOwned[i]->getNeighborVector().size(); j++)
			{
				Territory* target = territoriesOwned[i]->getNeighborVector()[j];
				ID = target->getID();
				if (!findElement(eligibleIDs, ID) && target->getPlayerOwner() == this)
				{
					eligibleIDs.push_back(ID);
					Pair temp = Pair();
					temp.Source = territoriesOwned[i];
					temp.Target = target;
					eligiblePairs.push_back(temp);
				}
			}
		}
	}
	printf("\n");
	if (eligiblePairs.size() <= 0)
	{
		return pair;
	}
	return movementDecision(eligiblePairs, pair);
}


Pair& Player::toAirlift(Pair& pair)
{
	std::vector<int> eligibleIDs;
	std::vector<Pair> eligiblePairs;


	printf("To Airlift: \n");
	int ID = 0;
	for (int i = 0; i < territoriesOwned.size(); i++)
	{
		if (territoriesOwned[i]->getNumberOfArmies() > 0)
		{
			for (int j = 0; j < territoriesOwned.size(); j++)
			{
				Territory* target = territoriesOwned[j];
				ID = target->getID();
				if (!findElement(eligibleIDs, ID) && target != territoriesOwned[i])
				{
					eligibleIDs.push_back(ID);
					Pair temp = Pair();
					temp.Source = territoriesOwned[i];
					temp.Target = target;
					eligiblePairs.push_back(temp);
				}
			}
		}

	}

	printf("\n");
	if (eligiblePairs.size() <= 0)
	{
		return pair;
	}

	return movementDecision(eligiblePairs, pair);
}


Pair& Player::toBomb(Pair& pair)
{
	std::vector<int> eligibleIDs;
	std::vector<Territory*> eligiblePairs;

	Player* targetPlayer = NULL;
	Territory* targetTerritory = NULL;
	printf("To Bomb: \n");
	int ID = 0;

	for (int i = 0; i < gameMap->ListOfPlayers.size(); i++)
	{
		 targetPlayer = gameMap->ListOfPlayers[i];
		if (targetPlayer != this)
		{
			auto playerTerritories = targetPlayer->getTerritoriesOwned();
			for (int j = 0; j < playerTerritories.size(); j++)
			{
				targetTerritory = playerTerritories[j];
				ID = targetTerritory->getID();
				if (!findElement(eligibleIDs, ID))
				{
					eligibleIDs.push_back(ID);
					eligiblePairs.push_back(targetTerritory);
				}
				
				targetTerritory = NULL;
			}

		}
		targetPlayer = NULL;
	}

	printf("\n");

	if (eligiblePairs.size() <= 0)
	{
		return pair;
	}

	return movementDecision(eligiblePairs, pair);
}

Pair& Player::toBlockade(Pair& pair)
{
	std::vector<int> eligibleIDs;
	std::vector<Territory*> eligiblePairs;

	Player* targetPlayer = NULL;
	Territory* targetTerritory = NULL;
	printf("To Blockade: \n");
	int ID = 0;

	for (int j = 0; j < territoriesOwned.size(); j++)
	{
		targetTerritory = territoriesOwned[j];
		ID = targetTerritory->getID();
		if (!findElement(eligibleIDs, ID))
		{
			eligibleIDs.push_back(ID);
			eligiblePairs.push_back(targetTerritory);
		}
	}

	printf("\n");

	if (eligiblePairs.size() <= 0)
	{
		return pair;
	}

	return movementDecision(eligiblePairs, pair);
}

Player* Player::toNegotiate()
{
	Player* targetPlayer = NULL;
	printf("To Negotiate: \n");
	int ID = 0;
	std::vector<int> eligibleIDs;

	for (int j = 0; j < gameMap->ListOfPlayers.size(); j++)
	{
		targetPlayer = gameMap->ListOfPlayers[j];
		ID = targetPlayer->getID();
		if (!findElement(eligibleIDs, ID) && this != targetPlayer && !this->checkAlliance(targetPlayer))
		{
			eligibleIDs.push_back(ID);
		}
	}

	printf("\n");

	if (eligibleIDs.size() <= 0)
	{
		return NULL;
	}

	return movementDecision(eligibleIDs);
}




int Player::getAdvanceArmyUnits(Territory* sourceTerritory)
{

	int territoryMAX = sourceTerritory->getNumberOfArmies();
	if (territoryMAX <= 0)
	{
		return 0;
	}
	bool correct = false;
	int playerChoice = -99;
	do
	{
		printf("Enter the number of units to advance [1 - %d]:\n", territoryMAX);
		std::cin >> playerChoice;

		if (playerChoice < territoryMAX && playerChoice > 0)
		{
			correct = true;
		}
	} while (!correct);

	return playerChoice;

}

void Player::setConquerBool() 
{
	if (!TerritoryConquiredThisTurn) 
		TerritoryConquiredThisTurn = true;
}
void Player::resetConquerBool() 
{
		TerritoryConquiredThisTurn = false;
}

Order* Player::createCommandFromCard(Cards* card)
{
	int armyUnits = 0;
	Pair pairtemp;
	Order* temp = NULL;
	Player* playertemp;
	switch (card->getType())
	{
	case CARD_TYPES::AIRLIFT:
		pairtemp = toAirlift(pairtemp);

		armyUnits = queryNumberOfUnitsToMove(pairtemp.Source);

		temp = new Airlift(this, armyUnits,pairtemp.Source, pairtemp.Target);
		break;
	case CARD_TYPES::BLOCKADE:
		pairtemp = toBlockade(pairtemp);

		temp = new Blockade(this, pairtemp.Target);
		break;
	case CARD_TYPES::BOMB:
		pairtemp = toBomb(pairtemp);

		temp = new Bomb(this, pairtemp.Target);
		break;
	case CARD_TYPES::NEGOTIATE:
		playertemp = toNegotiate();

		temp = new Negotiate(this, playertemp);
		break;
	case CARD_TYPES::REINFORCEMENT:
		temp = new Order();
		break;
	default:
		temp = new Order();
		break;
	}
	return temp;
	

}

void Player::issueOrder()
{
	int playerChoice = 0;
	bool invalid = false;

	while (!invalid)
	{
		if (numberToDeploy > 0)
		{
			printf("You still have %d unit(s) to deploy.\n", numberToDeploy);
			playerChoice = 9;
		}
		else
		{
			printf("Would you like to attack, defend, play a card or nothing? \n");
			printf("[0]Attack\n");
			printf("[1]Defend\n");
			printf("[2]Play a card\n");
			printf("[3]Nothing\n");
			std::cin >> playerChoice;
		}

		if (playerChoice == 9 || playerChoice >= 0 && playerChoice <= 3)
		{
			invalid = true;
		}
	}
	int target_ID = 0, armyUnits = 0;
	std::vector<int> eligibleIDs;
	Hand* currentHand = NULL;
	Cards* currentCard = NULL;
	Order* temp;
	Pair pairtemp;

	switch (playerChoice)
	{
	case 0:
		pairtemp = toAttack(pairtemp);
		armyUnits = queryNumberOfUnitsToMove(pairtemp.Source);

		temp = new Advance(this,armyUnits, pairtemp.Source, pairtemp.Target); //TODO: change to advance order
		break;
	case 1:
		pairtemp = toDefend(pairtemp);
		armyUnits = queryNumberOfUnitsToMove(pairtemp.Source);

		temp = new Advance(this, armyUnits, pairtemp.Source, pairtemp.Target); //TODO: change to advance order to move armies
		break;
	case 2:
		currentHand = getPlayerHand();

		if (currentHand->getSize() > 0)
		{
			currentCard = currentHand->playCard();
			temp = createCommandFromCard(currentCard);
			gameMap->getGameDeck()->sendToGraveyard(currentCard);
		}
		else 
			temp = NULL;
		break;
	case 3:
		temp = NULL;
		break;

	case 9:
		target_ID = toDefend(); 
		armyUnits = queryNumberOfUnitsToMove(NULL);

		temp = new Deploy(this, armyUnits, gameMap->CompleteList[target_ID]);//TODO: change to deploy order
		setNumberToDeploy(numberToDeploy - armyUnits);
		

		stream.clear();
		stream.str("");
		stream << "Player " << getID() << " created a deploy command.";
		PlayerMessage = stream.str();

		break;
	default:
		temp = NULL;
		break;
	}
	if(temp)
		CommandList->add(temp);
}

int Player::drawCard(Deck& d)
{
	playerHand->placeCardInHand(d.draw());
	return 0;
}

bool Player::queryHandAction()
{
	int playerChoice = 0;
	bool done = false;

	while (!done)
	{
		printf("Would you like to play a card from your hand?\n");
		printf("[0] No\n");
		printf("[1] Yes\n");
		printf("[2] View Hand.\n");
		std::cin >> playerChoice;

		if (playerChoice == 0 || playerChoice == 1)
		{
			done = true;
		}
		else if (playerChoice == 2)
		{
			playerHand->printHand();
		}
	}
	return playerChoice;
}

bool Player::queryIssueAction()
{
	int playerChoice = 0;
	bool done = false;

	while (!done)
	{
		printf("Would you like to issue a command?\n");
		printf("[0] No\n");
		printf("[1] Yes\n");
		std::cin >> playerChoice;

		if (playerChoice == 0 || playerChoice == 1)
		{
			done = true;
		}
	}
	return playerChoice;
}

bool Player::executeNextOrder()
{
	return CommandList->playNextOrder();
}

#include "Orders.h"


Order::Order()
{
	name = "Order";
	description = "Default order.\n";
	Value = 0;
}

Order::~Order() {}
int Order::execute()
{
	return 0;
}

bool Order::validate()
{
	return false;
}


std::ostream& operator << (std::ostream& out, const Order& o)
{
	out << o.name << std::endl;
	out << o.description << std::endl;
	return out;
}

std::istream& operator >> (std::istream& in, Order& o)
{
	std::cout << "Enter a description:\n";
	in >> o.description;

	std::cout << o.description << std::endl;

	return in;
}

bool operator > (Order& first, Order& second)
{
	return (first.getValue() > second.getValue());
}

bool operator < (Order& first, Order& second)
{
	return (first.getValue() < second.getValue());
}

OrderList::OrderList()
{
	map = NULL;
}

int OrderList::add(Order* o)
{
	pending.push_back(o);
	return 0;
}
int OrderList::remove(int index)
{
	Order* temp = pending.at(index);
	pending.erase(pending.begin() + index);
	history.push_back(temp);
	if (history.size() > 100)
	{
		printf("Warning: Order history is very long.\n");
	}
	return 0;

}
int OrderList::move(int index1, int index2)
{
	std::swap(pending[index1], pending[index2]);
	return 0;

}

int OrderList::playWholeList()
{
	while (!pending.empty())
	{
		pending[0]->execute();
		remove(0);
	}
	return 0;
}

bool OrderList::playNextOrder()
{
	if (!pending.empty())
	{
		sort();
		pending[0]->execute();
		remove(0);
		return true;
	}
	else
	{
		printf("Command List is empty.\n");
		return false;
	}
}

bool descendingOrder(Order* i, Order* j)
{
	return i->getValue() > j->getValue();
}

void OrderList::sort()
{
	std::sort(pending.begin(), pending.end(), descendingOrder);
}

Deploy::Deploy(Player* _sourcePlayer, int _Army, Territory* _targetTerritory)
{
	name = "Deploy";
	description = "Deploy order:\n";
	description += "Place some armies on one of the current player’s territories.\n";
	army = _Army;
	sourcePlayer = _sourcePlayer;
	targetTerritory = _targetTerritory;
	targetPlayer = nullptr;
	sourceTerritory = nullptr;
	gameMap = nullptr;
	Value = 5;
}

int Deploy::execute()
{
	if (validate())
	{
		int currentArmyTotal = targetTerritory->getNumberOfArmies()+army;
		int temp = targetTerritory->setNumberOfArmies(currentArmyTotal);

		sourcePlayer->stream.clear();
		sourcePlayer->stream.str("");
		sourcePlayer->stream << "Player " << sourcePlayer->getID() 
			<< " deployed " << army << " to territory[" 
			<< targetTerritory->getID() << "] ("<< currentArmyTotal <<")";
		sourcePlayer->PlayerMessage = sourcePlayer->stream.str();

	}
	return 0;

}

bool Deploy::validate()
{
	if (army <= 0)
	{
		return false;
	}
	if (targetTerritory == nullptr)
	{
		return false;
	}
	if (sourcePlayer == nullptr)
	{
		return false;
	}
	else
	{
		//if the territory doesn't belong to the player, don't deploy
		if (sourcePlayer != targetTerritory->getPlayerOwner())
		{
			return false;
		}
	}


	return true;
}


Advance::Advance(Player* _sourcePlayer, int _army,
	Territory* _sourceTerritory,
	Territory* _targetTerritory)
{

	name = "Advance";
	description = "Advance order:\n";
	description += "Move some armies from one of the current player’s territories (source)\n";
	description += "to an adjacent territory(target).If the target territory belongs to the\n";
	description += "current player, the armies are moved to the target territory.If the target\n";
	description += "territory belongs to another player, an attack happens between the two territories.\n";

	sourcePlayer = _sourcePlayer;
	targetPlayer = nullptr;
	army = _army;
	sourceTerritory = _sourceTerritory;
	targetTerritory = _targetTerritory;
	gameMap = nullptr;
	Value = 1;
}


int Advance::execute()
{
	if (validate())
	{

		if (targetTerritory->getPlayerOwner() == sourcePlayer)
		{
			/*printf("Player %d advanced %d units from territory[%d] to territory[%d]\n",
				sourcePlayer->getID(), army, sourceTerritory->getID(), targetTerritory->getID());*/

			sourcePlayer->stream.clear();
			sourcePlayer->stream.str("");
			sourcePlayer->stream << "Player "<<sourcePlayer->getID()<< " advanced "
				<< army <<" units from territory["<< sourceTerritory->getID()
				<<"] to territory["<< targetTerritory->getID()<<"]";
			sourcePlayer->PlayerMessage = sourcePlayer->stream.str();

			targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() + army);
			sourceTerritory->setNumberOfArmies(sourceTerritory->getNumberOfArmies() - army);

		}
		else
		{

			int numberOfDefenders = targetTerritory->getNumberOfArmies();
			int numberOfAttackers = army;
			battle(numberOfDefenders, numberOfAttackers);
		}




		return 0;

	}
	return -1;
}

bool Advance::validate()
{
	if (sourceTerritory->getPlayerOwner() != sourcePlayer)
		return false;

	if (army <= 0)
	{
		printf("Advance command failed. No army left.\n");
		return false;
	}

	if (army > sourceTerritory->getNumberOfArmies())
	{
		army = sourceTerritory->getNumberOfArmies();
	}

	if (sourcePlayer && targetPlayer)
	{
		if (sourcePlayer->checkAlliance(targetPlayer) == 1)
		{
			//they're allies
			return false;
		}
	}

	//check adjacency
	auto temp = sourceTerritory->getNeighborVector();
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i]->getID() == targetTerritory->getID())
		{
			return true;
		}
	}

	return false;
}

void Advance::battle(int defencePower, int attackPower)
{
	printf("Battle started at [%d]: %d attacks %d\n",
		targetTerritory->getID(), attackPower, defencePower);
	int attackersKilled = 0, defendersKilled = 0;
	for (int d = 0; d < defencePower; d++)
	{
		float chance = (float)rand() / RAND_MAX;
		if (chance > (1.0 - DEFENDER_CHANCE))
		{
			attackersKilled++;
		}
	}
	for (int a = 0; a < attackPower; a++)
	{
		float chance = (float)rand() / RAND_MAX;

		if (chance > (1.0 - ATTACKER_CHANCE))
		{
			defendersKilled++;
		}
	}

	int attackerStrength = attackPower - attackersKilled;
	int defenderStrength = defencePower - defendersKilled;

	printf("%d defending units killed.\n", 
		defenderStrength >= 0 ? defendersKilled : defencePower);
	printf("%d attacking units killed.\n",
		attackerStrength >= 0 ? attackersKilled : attackPower);

	if (defenderStrength <= 0)
	{
		printf("[%d] conquered. %d now occupy the territory.\n",
			targetTerritory->getID(), attackerStrength);

		targetTerritory->getPlayerOwner()->removeTerritory(targetTerritory->getID());
		sourcePlayer->addTerritory(targetTerritory);
		targetTerritory->setNumberOfArmies(attackerStrength);
		int sourceDifference = sourceTerritory->getNumberOfArmies() - attackPower;
		sourceTerritory->setNumberOfArmies(sourceDifference);
		sourcePlayer->setConquerBool();
	}
	else
	{
		printf("[%d] prevailed. %d remain in the territory.\n",
			targetTerritory->getID(), defenderStrength);
		targetTerritory->setNumberOfArmies(defenderStrength);
		int attackerRemainingUnits = attackerStrength > 0 ? attackerStrength : 0;
		sourceTerritory->setNumberOfArmies(attackerRemainingUnits);
	}

}


Airlift::Airlift(Player* _sourcePlayer, int _army, Territory* _sourceTerritory,
	Territory* _targetTerritory)
{

	name = "Airlift";
	description = "Airlift order:\n";
	description += "advance some armies from one of the current player’s territories \n";
	description += "to any another territory.\n";

	sourcePlayer = _sourcePlayer;
	targetPlayer = _targetTerritory->getPlayerOwner();
	army = _army;
	sourceTerritory = _sourceTerritory;
	targetTerritory = _targetTerritory;
	gameMap = nullptr;
	Value = 4;
}

bool Airlift::validate()
{
	if (sourceTerritory->getPlayerOwner() != sourcePlayer || 
		targetTerritory->getPlayerOwner() != sourcePlayer)
		return false;

	if (army > sourceTerritory->getNumberOfArmies())
	{
		army = sourceTerritory->getNumberOfArmies();
	}

	if (army <= 0)
	{
		printf("Airlift command failed. No army left.\n");
		return false;
	}


	if (sourcePlayer && targetPlayer)
	{
		if (sourcePlayer->checkAlliance(targetPlayer) == 1)
		{
			//they're allies
			return false;
		}
	}
	return true;
}

int Airlift::execute()
{
	if (validate())
	{
		if (targetTerritory->getPlayerOwner() == sourcePlayer)
		{
			//printf("Player %d airlifted %d units from territory[%d] to territory[%d]\n",
			//	sourcePlayer->getID(), army, sourceTerritory->getID(), targetTerritory->getID());

			sourcePlayer->stream.clear();
			sourcePlayer->stream.str("");
			sourcePlayer->stream << "Player " << sourcePlayer->getID() << " airlifted "
				<< army << " units from territory[" << sourceTerritory->getID()
				<< "] to territory[" << targetTerritory->getID() << "]";
			sourcePlayer->PlayerMessage = sourcePlayer->stream.str();


			targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() + army);
			sourceTerritory->setNumberOfArmies(sourceTerritory->getNumberOfArmies() - army);

		}
		else
		{

			int numberOfDefenders = targetTerritory->getNumberOfArmies();
			int numberOfAttackers = army;
			battle(numberOfDefenders, numberOfAttackers);
		}
		return 0;

	}
	return -1;

}


Bomb::Bomb(Player* _sourcePlayer, Territory* _targetTerritory)
{
	name = "Bomb";
	description = "Bomb order:\n";
	description += "Destroy half of the armies located on an opponent’s territory\n";
	description += "that is adjacent to one of the current player’s territories.\n";


	army = 0;
	sourcePlayer = _sourcePlayer;
	sourceTerritory = nullptr;

	targetTerritory = _targetTerritory;
	targetPlayer = nullptr;
	gameMap = nullptr;
}

int Bomb::execute()
{

	if (validate())
	{
		int bombedUnits = targetTerritory->getNumberOfArmies() / 2;
		int remaining = targetTerritory->getNumberOfArmies() - bombedUnits;
		targetTerritory->setNumberOfArmies(remaining);


		//printf("Player %d bombed territory[%d] and removed %d units!\n",
		//	sourcePlayer->getID(), targetTerritory->getID(),
		//	bombedUnits);

		sourcePlayer->stream.clear();
		sourcePlayer->stream.str("");
		sourcePlayer->stream << "Player " << sourcePlayer->getID() << " bombed territory[" << targetTerritory->getID()
			<< "] and removed "<< bombedUnits <<" units!";

		return 0;
	}
	return -1;
}

bool Bomb::validate()
{
	if (targetTerritory->getPlayerOwner() == sourcePlayer)
		return false;

	return true;
}


Blockade::Blockade(Player* _sourcePlayer, Territory* _targetTerritory)
{
	name = "Blockade";
	description = "Blockade order:\n";
	description += "triple the number of armies on one of the current player’s \n";
	description += "territories and make it a neutral territory.\n";


	army = 0;
	sourcePlayer = _sourcePlayer;
	sourceTerritory = nullptr;

	targetTerritory = _targetTerritory;
	targetPlayer = nullptr;
	gameMap = nullptr;
}

bool Blockade::validate()
{
	if (targetTerritory->getPlayerOwner() != sourcePlayer)
		return false;


	return true;
}

int Blockade::execute()
{
	if (validate())
	{

		targetTerritory->setNumberOfArmies(targetTerritory->getNumberOfArmies() * 2);
		sourcePlayer->removeTerritory(targetTerritory->getID());

		sourcePlayer->stream.clear();
		sourcePlayer->stream.str("");
		sourcePlayer->stream << "Player " << sourcePlayer->getID() << " blockaded territory[" << targetTerritory->getID()
			<< "] and there's now " << targetTerritory->getNumberOfArmies() << " units!";
		sourcePlayer->PlayerMessage = sourcePlayer->stream.str();


		//printf("Player %d blockaded territory[%d] and there's now %d units!\n",
		//	sourcePlayer->getID(), targetTerritory->getID(),
		//	targetTerritory->getNumberOfArmies());
	}
	return 0;
}



Negotiate::Negotiate(Player* _sourcePlayer, Player* _targetPlayer)
{
	name = "Negotiate";
	description = "Negotiate order:\n";
	description += "prevent attacks between the current player and another player \n";
	description += "until the end of the turn.\n";

	sourcePlayer = _sourcePlayer;
	targetPlayer = _targetPlayer;
	army = 0;
	sourceTerritory = nullptr;
	targetTerritory = nullptr;
	gameMap = nullptr;
}

bool Negotiate::validate()
{
	if (sourcePlayer == targetPlayer)
	{
		printf("Player[%d] can't target themself\n", sourcePlayer->getID());
		return false;
	}

	if (sourcePlayer->checkAlliance(targetPlayer))
	{
		//check if 1 == true
		printf("Player[%d] is already allied with Player[%d]\n",
			sourcePlayer->getID(), targetPlayer->getID());

		return false;
	}

	return true;
}

int Negotiate::execute()
{
	if (validate())
	{
		sourcePlayer->addAlliance(targetPlayer);
		targetPlayer->addAlliance(sourcePlayer);

		sourcePlayer->stream.clear();
		sourcePlayer->stream.str("");
		sourcePlayer->stream << "Player " << sourcePlayer->getID() << " is allied with Player["<< targetPlayer->getID() <<"]";
		sourcePlayer->PlayerMessage = sourcePlayer->stream.str();


		//printf("Player[%d] is allied with Player[%d]\n", sourcePlayer->getID(),
		//	targetPlayer->getID());
	}

	return 0;
}

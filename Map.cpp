#include "Map.h"
/* Territory class */
Territory::Territory()
{
	ID = 0;
	numberOfArmies = 0;
	previewedNumberOfArmies = 0;
	playerOwner = nullptr;
	X = 0;
	Y = 0;
	Name = "";
}

Territory::Territory(int _ID, std::string _Name)
{
	ID = _ID;
	numberOfArmies = 0;
	previewedNumberOfArmies = 0;
	playerOwner = nullptr;
	X = 0;
	Y = 0;
	Name = _Name;
}

Territory::~Territory() {}

int Territory::setPlayerOwner(Player* p)
{
	playerOwner = p;
	return 0;
}

int Territory::setNumberOfArmies(int num)
{
	if (num < 0)
	{
		return -1;
	}
	numberOfArmies = num;
	return 0;
}

bool Territory::checkIfNeighbor(Territory* targetTerritory)
{
	for (int i = 0; i < Neighbors.size(); i++)
	{
		if (Neighbors[i]->getID() == targetTerritory->getID())
		{
			return true;
		}
	}
	return false;
}

void Territory::addNeighbor(Territory* targetTerritory)
{
	this->Neighbors.push_back(targetTerritory);
	targetTerritory->Neighbors.push_back(this);
}


void Territory::setPreviewedArmies(int deployed)
{
	if (deployed >= 0)
	{
		previewedNumberOfArmies = deployed;
	}
	else
	{
		previewedNumberOfArmies = 0;
	}
}

bool Continent::CheckIfAllContinentControl( Player *p)
{

	int size = (int)Territories.size();
	bool IsControlledByThisPlayer = true;
	for (int i = 0; i < size; i++)
	{
		if (Territories[i]->getPlayerOwner() != p)
		{
			IsControlledByThisPlayer = false;
		}
	}
	if (IsControlledByThisPlayer)
	{
		ControlledByPlayer = p;
		return true;

	}
	return false;

}


/* Map class */
Map::Map()
{
	//srand((unsigned int)time(NULL));
	MapCounter = 0;
	numberOfPlayers = 0;
	//View = nullptr;


	//Loader = new MapLoader();
	//ListOfContinents.reserve(50);

	gameDeck = nullptr;


	//receiver = new OrderList();
	//receiver->setMap(this);
}
Map::~Map() 
{
	for (int i = 0; i < CompleteList.size(); i++)
	{
		delete CompleteList[i];
	}
}

Territory* Map::createNode(int ID, std::string name)
{
	Territory* temp = new Territory(ID, name);
	CompleteList.push_back(temp);
	ListOfNeighbors[ID].push_back(CompleteList.back());

	MapCounter++;
	return temp;
}

int Map::addEdge(Territory* u, Territory* v)
{
	ListOfNeighbors[u->getID()].push_back(v);
	u->getNeighborVector().push_back(v);


	//ListOfNeighbors[v->getID()].push_back(u);
	//v->getNeighborVector().push_back(u);


	return 0;
}

int Map::createContinent(std::string _Name, int _Bonus)
{
	Continent* temp = new Continent();
	temp->Name = _Name;
	temp->bonus = _Bonus;
	ListOfContinents.push_back(temp);

	return 0;
}

int Map::addToContinent(int index, Territory* u)
{
	Continent* temp = ListOfContinents.at(index);
	temp->Territories.push_back(u);
	temp->numberOfTerritories++;
	u->setContinent(temp);

	return 0;
}


int Map::printBoard()
{
	for (int x = 0; x < MapCounter; x++)
	{
		printf("[%d]%s: ", ListOfNeighbors[x][0]->getID()+1, ListOfNeighbors[x][0]->getName().c_str());

		for (int y = 1; y < ListOfNeighbors[x].size(); y++)
		{
			printf("-> %d ", ListOfNeighbors[x][y]->getID()+1);
		}

		printf("\n");

	}

	printf("Continents\n");

	for (int y = 0; y < ListOfContinents.size(); y++)
	{
		printf("[%d]%s\t", y+1, ListOfContinents[y]->Name.c_str());

		int z = 0;
		for (z; z < ListOfContinents[y]->Territories.size(); z++)
		{
			printf("-> %d ", ListOfContinents[y]->Territories[z]->getID()+1);
		}

		printf("\n");
	}
	return 0;
}

int Map::checkConnectedGraph(int index, std::vector<Territory*> vec)
{
	std::vector<bool> visited;
	for (int i = 0; i <CompleteList.size(); i++)
	{
		visited.push_back(false);
	}
	BFS(index, visited);

	if (vec.size() == CompleteList.size())
	{
		for (int i = 0; i < vec.size(); i++)
		{
			if (!visited[i])
			{
				return 0; //false
			}
		}
	}
	else
	{
		for (int i = 0; i < vec.size(); i++)
		{
			int target = vec[i]->getID();
			bool found = false;
			if (!visited[target])
			{
				return 0; //false
			}
		}
	}
	return 1; //true
}

int Map::checkDuplicateCountries()
{
	std::vector<int> v1(CompleteList.size());
	std::vector<std::set<int>> collection;
	for (int i = 0; i < v1.size(); i++)
	{
		v1[i] = -99;
	}

	for (int i = 0; i < ListOfContinents.size(); i++)
	{
		collection.push_back(TransferSet(ListOfContinents[i]->Territories));
	}

	for (int i = 1; i < ListOfContinents.size(); i++)
	{
		std::set_intersection(collection[0].begin(), collection[0].end(), collection[i].begin(),
			collection[i].end(), v1.begin());
	}

	if (*v1.begin() != -99)
	{
		return 0;
	}


	return 1;
}


//convert vector to set
std::set<int> Map::TransferSet(std::vector<Territory*> vec)
{
	std::set<int> set;
	for (int j = 0; j < vec.size(); j++)
	{
		set.insert(vec[j]->getID());
	}
	return set;
}

int Map::printNeighbors(Territory* t)
{
	for (int i = 1; i < ListOfNeighbors[t->getID()].size(); i++)
	{
		printf("%d ", ListOfNeighbors[t->getID()][i]->getID());
	}
	printf("\n");
	return 0;
}


int Map::BFS(int index, std::vector<bool>& visited)
{
	std::vector<int> q;

	visited[index] = true;


	q.push_back(index);

	while (!q.empty())
	{
		index = q.front();
		q.erase(q.begin());

		size_t SIZE = ListOfNeighbors[index].size();
		for (int i = 1; i < SIZE; i++)
		{
			int targetIndex = ListOfNeighbors[index][i]->getID();
			if (!visited[targetIndex ])
			{
				visited[targetIndex] = true;
				q.push_back(targetIndex);
			}
		}
	}


	return 0;
}

bool Map::validate()
{
	//Check whole graph is connected
	if (!checkConnectedGraph(1, CompleteList))
	{
		return false;
	}
	//check all subgraphs are connected
	for (int c = 0; c < ListOfContinents.size(); c++)
	{
		if (!checkConnectedGraph(1, ListOfContinents[0]->Territories))
		{
			return false;
		}
	}
	//Check if any countries are part of another continent
	if (!checkDuplicateCountries())
	{
		return false;
	}

	return true;
}

void Map::addPlayer(Player* p)
{
	ListOfPlayers.push_back(p);
	p->setMap(this);
	p->setID(numberOfPlayers++);
	
}
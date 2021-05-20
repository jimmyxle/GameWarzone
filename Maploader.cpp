#pragma once
#include "Maploader.h"



MapLoader::MapLoader()
{
	GameMap = new Map();
}

int MapLoader::readFile(std::string file)
{
	std::ifstream myFile(file);
	std::string text;

	if (myFile.fail())
	{
		printf("Failed to open game map file[%s].\n", file.c_str());
		return 0;
	}

	while (std::getline(myFile, text))
	{

		if (!text.empty())
		{
			if (text == "[files]")
			{
				while (std::getline(myFile, text))
				{
					if (!text.empty())
					{
						files.push_back(text.c_str());
						//printf("%s\n", text.c_str());
					}
					else
					{
						break;
					}
				}
				std::getline(myFile, text);
			}

			if (text == "[continents]")
			{
				while (std::getline(myFile, text))
				{
					if (!text.empty())
					{
						continents.push_back(text.c_str());
						//printf("%s\n", text.c_str());
					}
					else
					{
						break;
					}
				}
				std::getline(myFile, text);
			}

			if (text == "[countries]")
			{
				while (std::getline(myFile, text))
				{
					if (!text.empty())
					{
						countries.push_back(text.c_str());
						//printf("%s\n", text.c_str());
					}
					else
					{
						break;
					}
				}
				std::getline(myFile, text);
			}

			if (text == "[borders]")
			{
				while (std::getline(myFile, text))
				{
					if (!text.empty())
					{
						borders.push_back(text.c_str());
						//printf("%s\n", text.c_str());
					}
					else
					{
						break;
					}
				}
				std::getline(myFile, text);
			}


		}

	}

	myFile.close();
	return 0;
}

int MapLoader::readMapData(std::string str)
{
	readFile(str);
	createContinentsFromMapData();
	createCountriesFromMapData();
	createBordersFromMapData();

	return 0;
}

int MapLoader::createContinentsFromMapData()
{
	auto temp = getContinents();
	char* context = NULL;
	char* name = NULL;
	char* bonus = NULL;
	char* color = NULL;

	char delim[] = " ";

	for (int i = 0; i < temp.size(); i++)
	{
		name = strtok_s((char*)temp[i].c_str(), delim, &context);
		bonus = strtok_s(NULL, delim, &context);
		color = strtok_s(NULL, delim, &context);

		GameMap->createContinent(name, atoi(bonus));

		if ((std::string)color == "white")
		{
			GameMap->ListOfContinents.back()->color = WHITE;
		}
		else if ((std::string)color == "blue")
		{
			GameMap->ListOfContinents.back()->color = BLUE;
		}
		else if ((std::string)color == "cyan")
		{
			GameMap->ListOfContinents.back()->color = CYAN;
		}
		else if ((std::string)color == "green")
		{
			GameMap->ListOfContinents.back()->color = GREEN;
		}
		else if ((std::string)color == "orange")
		{
			GameMap->ListOfContinents.back()->color = ORANGE;
		}
		else if ((std::string)color == "yellow")
		{
			GameMap->ListOfContinents.back()->color = YELLOW;
		}
		else if ((std::string)color == "red")
		{
			GameMap->ListOfContinents.back()->color = RED;
		}
		else if ((std::string)color == "grey")
		{
			GameMap->ListOfContinents.back()->color = GREY;
		}
		else
		{
			GameMap->ListOfContinents.back()->color = WHITE;
			printf("Error. Unexpected color. Default to white.\n");
			return -1;
		}
	}


	return 0;
}


int MapLoader::createCountriesFromMapData()
{
	auto temp = getCountries();
	char* context = NULL;
	char* ID = NULL;
	char* name = NULL;
	char* continent = NULL;
	char* X = NULL;
	char* Y = NULL;

	char delim[] = " ";

	for (int i = 0; i < temp.size(); i++)
	{
		ID = strtok_s((char*)temp[i].c_str(), delim, &context);
		name = strtok_s(NULL, delim, &context);
		continent = strtok_s(NULL, delim, &context);
		X = strtok_s(NULL, delim, &context);
		Y = strtok_s(NULL, delim, &context);

		GameMap->createNode(atoi(ID)-1, name);
		GameMap->addToContinent(atoi(continent)-1, GameMap->CompleteList.back());

		GameMap->CompleteList.back()->setXY(atoi(X), atoi(Y));
	}

	return 0;
}

int MapLoader::createBordersFromMapData()
{
	auto temp = getBorders();
	char* index = NULL;
	char* neighbor = NULL;
	char* context = NULL;
	char delim[] = " ";

	for (int i = 0; i < temp.size(); i++)
	{
		index = strtok_s((char*)temp[i].c_str(), delim, &context);
		neighbor = strtok_s(NULL, delim, &context);

		if (neighbor != NULL)
		{
			do
			{
				GameMap->addEdge(GameMap->CompleteList[atoi(index) - 1], GameMap->CompleteList[atoi(neighbor) - 1]);
				neighbor = strtok_s(NULL, delim, &context);

			} while (neighbor);
		}
	}

	return 0;
}
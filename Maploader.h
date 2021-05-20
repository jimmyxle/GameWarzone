#pragma once
#include "Essentials.h"

#define WHITE 0
#define BLUE 1
#define CYAN 2
#define GREEN 3
#define ORANGE 4
#define YELLOW 5
#define RED 6
#define GREY 7

class MapLoader
{

private:
	std::vector<std::string> files;
	std::vector<std::string> continents;
	std::vector<std::string> countries;
	std::vector<std::string> borders;
	Map* GameMap;
public:
	MapLoader();
	~MapLoader() = default;
	int readFile(std::string file);
	int readMapData(std::string str);
	std::vector<std::string> getFiles() { return files; }
	std::vector<std::string> getContinents() { return continents; }
	std::vector<std::string> getCountries() { return countries; }
	std::vector<std::string> getBorders() { return borders; }
	int createContinentsFromMapData();
	int createCountriesFromMapData();
	int createBordersFromMapData();
	Map* getMap() { return GameMap; };

};

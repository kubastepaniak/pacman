#include "map.h"
#include <fstream>

Map::Map(int type) {
    std::ifstream database;

	if(type == MapType::logic) {
		database.open("maps/mapData.txt");
	} else if (type == MapType::collectable) {
		database.open("maps/collectableMapData.txt");
	}

	database >> width;
	database >> height;
    
    this->map = new int*[height]();
	for (int y = 0; y < height; y++)
	{
        this->map[y] = new int[width]();
		for (int x = 0; x < width; x++)
		{
			database >> map[y][x];
		}
	}
}

int& Map::operator()(int x, int y) { return map[y][x]; }

int Map::getWidth() const { return width; }

int Map::getHeight() const { return height; }

void Map::operator=(const Map& otherMap) { this->map = otherMap.map; }

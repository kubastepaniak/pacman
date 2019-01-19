#pragma once

enum MapType : int { logic, collectable };
enum MapTag : int { space, wall, gate, teleport };
enum CollTag : int { point = 6, candy = 8 };

struct Map {
    int **map;
    int width; int height;
    
    Map(int type = MapType::logic);
    int getWidth() const;
    int getHeight() const;
    int& operator()(int x, int y);
    void operator=(const Map& otherMap);
};
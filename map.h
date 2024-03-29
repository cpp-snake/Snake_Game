#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "ncurses.h"

#define MAPSIZE 25

class Map
{
    int map_stat[MAPSIZE][MAPSIZE];

public:
    Map(std::string file_name);
    void test();
    void init();
    int get_stat_value(int row, int col);
    void set_stat_value(int row, int col, int value);
};

#endif
#include <iostream>
#include "ncurses.h"

#define N 25

class Map
{
    int map_stat[N][N];

public:
    Map(std::string file_name);
    void test();
    WINDOW *init();
};

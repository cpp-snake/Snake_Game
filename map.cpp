#include <iostream>
#include <fstream>
#include "ncurses.h"
#include "map.h"
using namespace std;

Map::Map(string file_name)
{
    ifstream file(file_name);
    int number;

    for (int i = 0; i < MAPSIZE; i++)
    {
        for (int j = 0; j < MAPSIZE; j++)
        {
            file >> number;
            map_stat[i][j] = number;
        }
    }
    file.close();
}

void Map::test()
{
    for (int i = 0; i < MAPSIZE; i++)
    {
        for (int j = 0; j < MAPSIZE; j++)
        {
            cout << map_stat[i][j] << " ";
        }
        cout << endl;
    }
}

void Map::init()
{
    start_color();
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(1, COLOR_BLACK, COLOR_BLACK);

    for (int row = 0; row < MAPSIZE; row++)
    {
        for (int col = 0; col < MAPSIZE; col++)
        {
            attron(COLOR_PAIR(map_stat[row][col] + 1));
            printw("   ");
            attroff(COLOR_PAIR(map_stat[row][col] + 1));
        }
        printw("\n");
    }

    refresh();
}

int Map::get_stat_value(int row, int col){
    return map_stat[row][col];
}

void Map::set_stat_value(int row, int col, int value){
    map_stat[row][col] = value;
}
#ifndef ITEM_H
#define ITEM_H

#include "map.h"

#include <vector>

using namespace std;

#define item_Appeard_Time 5
#define POISON 5
#define GROWTH 6

class Item
{
    int item_x, item_y; // 아이템 좌표

public:
    Item generate_growth_item(Map &map);   // snake의 길이를 늘리는 아이템
    Item generate_poison_item(Map &map);   // Snake의 길이를 줄이는 아이템
    void delete_item(Map &map, Item item); // 맵에서 아이템 삭제
    int get_item_x();
    int get_item_y();
};

#endif
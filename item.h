#ifndef ITEM_H
#define ITEM_H

#include "map.h"

#include <vector>

using namespace std;

#define item_Appeard_Time 5

class Item{
    int item_x, item_y; // 아이템 좌표
    
public:
    void generate_Item(); // 아이템 좌표 정하기
    void Growth_Item(Map *map); // Snake의 길이를 늘리는 아이템
    void Poison_Item(Map *map); // Snake의 길이를 줄이는 아이템
    void Choice_item(Map *map); // 아이템 선택
    void delete_item(Map *map); // 맵에서 아이템 삭제
};


#endif
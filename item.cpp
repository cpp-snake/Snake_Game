#include "ncurses.h"
#include "map.h"
#include "settings.h"
#include <vector>
#include <thread> // 동시에 작동하도록 하는 것
#include "item.h"
#include <fstream> //랜덤 시드 설정
#include <random> //랜덤 시드 설정
#include <unistd.h> // 랜덤 시드 설정

using namespace std;

void Item::generate_Item()
{

    // 랜덤 시드를 설정하는 부분
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100000);

    // 난수 생성 및 좌표 설정
    int rand_x = dist(gen)%(MAPSIZE-2);
    int rand_y = dist(gen)%(MAPSIZE-2);
    item_x = 1+(rand_x);
    item_y = 1+(rand_y);

}

// map_stat 배열을 posion_item 고유 번호 5로 변경
void Item::Growth_Item(Map *map)
{
    map->set_item_map(item_x, item_y, 5);  
    
    attron(COLOR_PAIR(5));
    mvprintw(item_y, 3*item_x, "   ");
    attroff(COLOR_PAIR(5));
}

// map_stat 배열을 posion_item 고유 번호 6으로 변경
void Item::Poison_Item(Map *map)
{
    map->set_item_map(item_x, item_y, 6);

    attron(COLOR_PAIR(6));
    mvprintw(item_y, 3*item_x, "   ");
    attroff(COLOR_PAIR(6));
}

void Item::Choice_item(Map *map)
{
    // 랜덤으로 성장 또는 독 아이템 출력
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100000);

    if(dist(gen)%2==1)
        Growth_Item(map);
    else
        Poison_Item(map);
}

void Item::delete_item(Map *map)
{
    map->delete_item_map(item_x, item_y);
}
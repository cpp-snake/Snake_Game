#include "ncurses.h"
#include "map.h"
#include <vector>
#include <thread> // 동시에 작동하도록 하는 것
#include "item.h"
#include <fstream>  //랜덤 시드 설정
#include <random>   //랜덤 시드 설정
#include <unistd.h> // 랜덤 시드 설정

using namespace std;

Item Item::generate_growth_item(Map &map)
{
    // 랜덤 시드를 설정하는 부분
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100000);

    Item growth;

    while (true)
    {
        // 난수 생성 및 좌표 설정
        int rand_x = dist(gen) % (MAPSIZE - 2);
        int rand_y = dist(gen) % (MAPSIZE - 2);

        growth.item_x = rand_x;
        growth.item_y = rand_y;

        if (map.get_stat_value(growth.item_y, growth.item_x) == 0)
        {
            break;
        }
    }

    // 아이템 출력
    map.set_stat_value(growth.item_y, growth.item_x, GROWTH);

    attron(COLOR_PAIR(GROWTH));
    mvprintw(growth.item_y, 3 * growth.item_x, "   ");
    attroff(COLOR_PAIR(GROWTH));

    refresh();

    return growth;
}

Item Item::generate_poison_item(Map &map)
{
    // 랜덤 시드를 설정하는 부분
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100000);

    // 난수 생성 및 좌표 설정
    int rand_x = dist(gen) % (MAPSIZE - 2);
    int rand_y = dist(gen) % (MAPSIZE - 2);

    Item poison;
    poison.item_x = 1 + (rand_x);
    poison.item_y = 1 + (rand_y);

    // 아이템 출력
    map.set_stat_value(poison.item_y, poison.item_x, POISON);

    attron(COLOR_PAIR(POISON));
    mvprintw(poison.item_y, 3 * poison.item_x, "   ");
    attroff(COLOR_PAIR(POISON));

    refresh();

    return poison;
}

void Item::delete_item(Map &map, Item item)
{
    map.set_stat_value(item.item_y, item.item_x, 0);

    attron(COLOR_PAIR(1));
    mvprintw(item.item_y, 3 * item.item_x, "   ");
    attroff(COLOR_PAIR(1));

    refresh();
}

int Item::get_item_x()
{
    return item_x;
}

int Item::get_item_y()
{
    return item_y;
}
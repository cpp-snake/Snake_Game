#include "ncurses.h"
#include "map.h"
#include "settings.h"
#include "item.h"
#include <chrono>
#include <thread>

#define POISON_ITEM_TICK1 1
#define POISON_ITEM_TICK2 3
#define POISON_ITEM_TICK3 4
#define GROWTH_ITEM_TICK 6

// 좌표 값 출력 디버깅용
void printMap(Map& map){ 
    int i = 12, j = 110;
    move(i++, j);
    for (int row = 0; row < MAPSIZE; row++)
    {
        for (int col = 0; col < MAPSIZE; col++)
            printw(" %d ", map.get_stat_value(row, col));
        move(i++, j);
    }
}

int main()
{
    screen_setup();
    Map map("map_design.txt");
    map.init();

    init_pair_colors();

    Item item;

    std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초 동안 아무 것도 안 함
    Item poison_item1 = item.generate_poison_item(map);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    Item poison_item2 = item.generate_poison_item(map);

    std::this_thread::sleep_for(std::chrono::seconds(0));
    Item poison_item3 = item.generate_poison_item(map);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    Item growth_item = item.generate_growth_item(map);

    auto next_poison_time1 = std::chrono::system_clock::now() + std::chrono::seconds(POISON_ITEM_TICK1);
    auto next_poison_time2 = std::chrono::system_clock::now() + std::chrono::seconds(POISON_ITEM_TICK2);
    auto next_poison_time3 = std::chrono::system_clock::now() + std::chrono::seconds(POISON_ITEM_TICK3);
    auto next_growth_time = std::chrono::system_clock::now() + std::chrono::seconds(GROWTH_ITEM_TICK);

    int ch;
    while (true) {
        ch = getch();
        if (ch == KEY_UP) break; // 윗 방향키 누르면 종료

        auto now = std::chrono::system_clock::now();

        if (now >= next_poison_time1) {
            poison_item1.delete_item(map, poison_item1);
            poison_item1 = item.generate_poison_item(map);
            printMap(map);
            next_poison_time1 = now + std::chrono::seconds(POISON_ITEM_TICK1);
        }

        if (now >= next_poison_time2) {
            poison_item2.delete_item(map, poison_item2);
            poison_item2 = item.generate_poison_item(map);
            printMap(map);
            next_poison_time2 = now + std::chrono::seconds(POISON_ITEM_TICK2);
        }

        if (now >= next_poison_time3) {
            poison_item3.delete_item(map, poison_item3);
            poison_item3 = item.generate_poison_item(map);
            printMap(map);
            next_poison_time3 = now + std::chrono::seconds(POISON_ITEM_TICK3);
        }

        if (now >= next_growth_time) {
            growth_item.delete_item(map, growth_item);
            growth_item = item.generate_growth_item(map);
            printMap(map);
            next_growth_time = now + std::chrono::seconds(GROWTH_ITEM_TICK);
        }
    }
    
    screen_teardown();

    return 0;
}
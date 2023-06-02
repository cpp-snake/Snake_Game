#include "ncurses.h"
#include "map.h"
#include "settings.h"
#include "item.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream> //랜덤 시드 설정
#include <random> //랜덤 시드 설정
#include <unistd.h> // 랜덤 시드 설정
#define item_TICK 5

void G_Item(Map *map){
    Item item_g;
    item_g.generate_Item();
    item_g.Choice_item(map);
//    item_g.delete_item(map); << 삭제함수임 갱신할 때마다 삭제하도록 해야하는데 갱신을 못하겠어요..
}

int main()
{
    Map map("map_design.txt");
    initscr();
    map.init();

    init_pair_colors();
    
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, 1000);

        // 아이템을 1~3개 랜덤 출력
        int random = 1+dist(gen)%3; // dist(gen)%n : 1~n개 만큼의 아이템을 출력하도록 하는 수
        std::vector<std::thread> itemThreads(random);
        for(int i = 0; i < random; i++)
            itemThreads[i] = std::thread(G_Item, &map);

        for(int i = 0; i < random; i++)
            itemThreads[i].join();
    
    getch();
    endwin();
    return 0;
}
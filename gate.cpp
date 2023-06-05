#include "ncurses.h"
#include "map.h"
#include <vector>
#include <thread> // 동시에 작동하도록 하는 것
#include "gate.h"
#include <fstream>  //랜덤 시드 설정
#include <random>   //랜덤 시드 설정
#include <unistd.h> // 랜덤 시드 설정

using namespace std;

Gate Gate::generate_gate(Map &map)
{
    // 랜덤 시드를 설정하는 부분
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100000);

    Gate gate;

    while (true)
    {
        // 난수 생성 및 좌표 설정
        int rand_x = dist(gen) % MAPSIZE;
        int rand_y = dist(gen) % MAPSIZE;

        gate.gate_x = rand_x;
        gate.gate_y = rand_y;

        if (map.get_stat_value(gate.gate_y, gate.gate_x) == 1)
        {
            break;
        }
    }

    // 아이템 출력
    map.set_stat_value(gate.gate_y, gate.gate_x, GATE);

    attron(COLOR_PAIR(GATE));
    mvprintw(gate.gate_y, 3 * gate.gate_x, "   ");
    attroff(COLOR_PAIR(GATE));

    refresh();

    return gate;
}

void Gate::delete_gate(Map &map)
{
    map.set_stat_value(gate_y, gate_x, 1);

    attron(COLOR_PAIR(2));
    mvprintw(gate_y, 3 * gate_x, "   ");
    attroff(COLOR_PAIR(2));

    refresh();
}

int Gate::get_gate_x()
{
    return gate_x;
}

int Gate::get_gate_y()
{
    return gate_y;
}
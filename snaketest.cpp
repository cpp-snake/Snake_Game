#include "ncurses.h"
#include "map.h"
#include "snake.h"
#include "settings.h"
#include "item.h"
#include "gate.h"
#include "board.h"
#include <vector>
#include <chrono> // TICK에 맞춰 한 번 씩 이동
#include <thread>
#include <stdlib.h>
using namespace std;

#define POISON_ITEM_TICK1 15
#define POISON_ITEM_TICK2 8
#define GROWTH_ITEM_TICK 12

bool isRudder(int ch)
{
    return ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_DOWN || ch == KEY_UP;
}

// 좌표 값 출력 디버깅용
void printMap(Map &map)
{
    int i = 12, j = 110;
    move(i++, j);
    for (int row = 0; row < MAPSIZE; row++)
    {
        for (int col = 0; col < MAPSIZE; col++)
            printw(" %d ", map.get_stat_value(row, col));
        move(i++, j);
    }
}

bool meet_item(Item item, Snake snake)
{
    return (item.get_item_x() == snake.get_head_x() && item.get_item_y() == snake.get_head_y());
}

bool meet_gate(Gate gate, Snake snake)
{
    return (gate.get_gate_x() == snake.get_head_x() && gate.get_gate_y() == snake.get_head_y());
}

int main()
{
    screen_setup();
    Map map("./map/map_design4.txt");
    map.init();

    init_pair_colors();

    Snake snake(3);
    snake.draw();

    Item item;
    Item poison_item1 = item.generate_poison_item(map);
    Item poison_item2 = item.generate_poison_item(map);
    Item growth_item = item.generate_growth_item(map);

    Board board;
    board.count_init(snake);

    board.makeMissionBoard();
    board.makeScoreBoard();

    Gate gate;
    Gate gatePair1 = gate.generate_gate(map);
    Gate gatePair2 = gate.generate_gate(map);

    auto next_poison_time1 = chrono::system_clock::now() + chrono::seconds(POISON_ITEM_TICK1);
    auto next_poison_time2 = chrono::system_clock::now() + chrono::seconds(POISON_ITEM_TICK2);
    auto next_growth_time = chrono::system_clock::now() + chrono::seconds(GROWTH_ITEM_TICK);
    // 게임 실행
    int ch;
    bool is_direction_changed = TRUE;
    auto lastUpdateTime = chrono::system_clock::now(); // 마지막 업데이트 시간 초기화
    chrono::duration<double> elapsedSeconds;

    bool gate_flag = true; // 게이트를 통과 하기 전에 true, 통과하는 동안, 통과 한 후 false
    int input_x, input_y;  // 게이트를 통과하기전 xy좌표

    while (true)
    {
        auto now = chrono::system_clock::now();
        if (meet_item(poison_item1, snake))
        {
            snake.decrease_length(map);
            printMap(map);
            board.countMinus(); // 뱀의 길이가 줄어들고 보드판을 건들여야 적용됨
            board.update_score(snake);
            poison_item1 = item.generate_poison_item(map);
            next_poison_time1 = now + chrono::seconds(POISON_ITEM_TICK1);
        }
        if (meet_item(poison_item2, snake))
        {
            snake.decrease_length(map);
            printMap(map);
            board.countMinus(); // 뱀의 길이가 줄어들고 보드판을 건들여야 적용됨
            board.update_score(snake);
            poison_item2 = item.generate_poison_item(map);
            next_poison_time2 = now + chrono::seconds(POISON_ITEM_TICK2);
        }
        if (meet_item(growth_item, snake))
        {
            snake.increase_length(map);
            printMap(map);
            board.countPlus(); // 뱀의 길이가 줄어들고 보드판을 건들여야 적용됨
            board.update_score(snake);
            growth_item = item.generate_growth_item(map);
            next_growth_time = now + chrono::seconds(GROWTH_ITEM_TICK);
        }

        if (meet_gate(gatePair1, snake) && gate_flag)
        {
            input_x = snake.get_tail_x(0);
            input_y = snake.get_tail_y(0);
            snake.move_gate(map, gatePair1, gatePair2);
            printMap(map);
            gate_flag = false;
        }

        else if (meet_gate(gatePair2, snake) && gate_flag)
        {
            input_x = snake.get_tail_x(0);
            input_y = snake.get_tail_y(0);
            snake.move_gate(map, gatePair2, gatePair1);
            printMap(map);
            gate_flag = false;
        }

        if (!gate_flag) // 통과 중
        {
            if (map.get_stat_value(input_y, input_x) != TAIL) // 통과완료
            {
                gatePair1.delete_gate(map);
                gatePair2.delete_gate(map);
                gatePair1 = gate.generate_gate(map);
                gatePair2 = gate.generate_gate(map);
                gate_flag = true;
                board.countUsedGate();
                board.update_score(snake);
            }
        }

        if (now >= next_poison_time1)
        {
            poison_item1.delete_item(map, poison_item1);
            poison_item1 = item.generate_poison_item(map);
            next_poison_time1 = now + chrono::seconds(POISON_ITEM_TICK1);
        }

        if (now >= next_poison_time2)
        {
            poison_item2.delete_item(map, poison_item2);
            poison_item2 = item.generate_poison_item(map);
            next_poison_time2 = now + chrono::seconds(POISON_ITEM_TICK2);
        }

        if (now >= next_growth_time)
        {
            growth_item.delete_item(map, growth_item);
            growth_item = item.generate_growth_item(map);
            next_growth_time = now + chrono::seconds(GROWTH_ITEM_TICK);
        }
        ch = getch();
        if (isRudder(ch) && ch)
        {
            switch (ch)
            {
            case KEY_LEFT:
                if (snake.get_dir() == RIGHT)
                {
                    screen_teardown();
                    exit(0);
                };
                if (snake.get_dir() == LEFT)
                    is_direction_changed = FALSE;
                else
                {
                    snake.set_dir(LEFT);
                    is_direction_changed = TRUE;
                }
                break;
            case KEY_RIGHT:
                if (snake.get_dir() == LEFT)
                {
                    screen_teardown();
                    exit(0);
                }

                if (snake.get_dir() == RIGHT)
                    is_direction_changed = FALSE;
                else
                {
                    snake.set_dir(RIGHT);
                    is_direction_changed = TRUE;
                }
                break;
            case KEY_UP:
                if (snake.get_dir() == DOWN)
                {
                    screen_teardown();
                    exit(0);
                }

                if (snake.get_dir() == UP)
                    is_direction_changed = FALSE;
                else
                {
                    snake.set_dir(UP);
                    is_direction_changed = TRUE;
                }
                break;
            case KEY_DOWN:
                if (snake.get_dir() == UP)
                {
                    screen_teardown();
                    exit(0);
                }

                if (snake.get_dir() == DOWN)
                    is_direction_changed = FALSE;
                else
                {
                    snake.set_dir(DOWN);
                    is_direction_changed = TRUE;
                }
                break;
            }

            // 올바른 방향키가 들어오면 스네이크 이동
            if (is_direction_changed)
            {
                snake.move(map);
                snake.draw();
                printMap(map);
                lastUpdateTime = std::chrono::system_clock::now(); // 업데이트 시간 갱신
            }
        }

        // 입력이 없으면 1초마다 진행방향으로 이동
        else
        {
            auto currentTime = std::chrono::system_clock::now();
            elapsedSeconds = currentTime - lastUpdateTime;

            if (elapsedSeconds.count() >= TICK)
            { // 1초 이상 경과한 경우
                snake.move(map);
                snake.draw();
                printMap(map);
                lastUpdateTime = currentTime; // 업데이트 시간 갱신
            }
        }
    }

    screen_teardown();

    return 0;
}
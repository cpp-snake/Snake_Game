#include "ncurses.h"
#include "map.h"
#include "snake.h"
#include "settings.h"
#include "item.h"
#include "board.h"
#include <vector>
#include <chrono> // TICK에 맞춰 한 번 씩 이동
#include <thread>
#include <stdlib.h>

using namespace std;

#define POISON_ITEM_TICK1 10
#define POISON_ITEM_TICK2 10
#define GROWTH_ITEM_TICK 10

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

int main()
{
    screen_setup();
    Map map("map_design.txt");
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

    auto next_poison_time1 = chrono::system_clock::now() + chrono::seconds(POISON_ITEM_TICK1);
    auto next_poison_time2 = chrono::system_clock::now() + chrono::seconds(POISON_ITEM_TICK2);
    auto next_growth_time = chrono::system_clock::now() + chrono::seconds(GROWTH_ITEM_TICK);
    // 게임 실행
    int ch;
    bool is_direction_changed = TRUE;
    auto lastUpdateTime = chrono::system_clock::now(); // 마지막 업데이트 시간 초기화
    chrono::duration<double> elapsedSeconds;
    while (true)
    {    
        auto now = chrono::system_clock::now();
        if (meet_item(poison_item1, snake))
        {
            snake.decrease_length(map);
            board.countMinus(); // 뱀의 길이가 줄어들고 보드판을 건들여야 적용됨
            board.update_score(snake);
            poison_item1 = item.generate_poison_item(map);
            next_poison_time1 = now + chrono::seconds(POISON_ITEM_TICK1);
        }
        if (meet_item(poison_item2, snake))
        {
            snake.decrease_length(map);
            board.countMinus(); // 뱀의 길이가 줄어들고 보드판을 건들여야 적용됨
            board.update_score(snake);
            poison_item2 = item.generate_poison_item(map);
            next_poison_time2 = now + chrono::seconds(POISON_ITEM_TICK2);
        }
        if (meet_item(growth_item, snake))
        {
            snake.increase_length();
            board.countPlus(); // 뱀의 길이가 줄어들고 보드판을 건들여야 적용됨
            board.update_score(snake);
            growth_item = item.generate_growth_item(map);
            next_growth_time = now + chrono::seconds(GROWTH_ITEM_TICK);
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
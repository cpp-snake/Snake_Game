#include "ncurses.h"
#include "snake.h"
#include "map.h"
#include "settings.h"
#include <vector>
#include <chrono> // TICK에 맞춰 한 번 씩 이동
#include <thread>
#include <stdlib.h> // exit(0);
using namespace std;

Snake::Snake(int length) : tailLength(length), dir(RIGHT) // 길이를 인자로 받아 뱀 생성
{
    head_x = head_y = MAPSIZE / 2;

    for (int i = 1; i <= length; i++)
    {
        tail_x.push_back(head_x - i);
        tail_y.push_back(head_y);
    }

    tail_x.push_back(tail_x[length - 1]);
    tail_y.push_back(head_y);
    /*마지막 두 줄 설명:
    draw()함수에서 뱀을 뱀의 각 좌표에 따라 출력할 때
    새로 출력 하기 전, 출력 돼 있던 뱀의 마지막 꼬리가 있던 부분은 지우고 출력 해야 함.
    이를 저장하기 위해 뱀의 마지막 꼬리 좌표를 백업하는 값으로 사용
    따라서 tailLength는 tail_x.size() - 1이고,
    꼬리를 늘리거나 줄일 때는 insert,erase(tail_x.end() - 2, i)로 추가하고
    tail_x[length] = i로 백업해놔야함.(length + 1번째 값은 length번째 인덱스 값)
    */
}

void Snake::increase_length()
{
    tailLength++;
}

void Snake::decrease_length(Map &map)
{
    tailLength--;
    attron(COLOR_PAIR(1));
    mvprintw(tail_y[tailLength], 3 * tail_x[tailLength], "   ");
    attroff(COLOR_PAIR(1));
    map.set_stat_value(tail_y[tailLength], tail_x[tailLength], 0);
}

void Snake::move(Map &map)
{ // 키 입력에 따라서 snake 좌표 이동
    // 꼬리 이동
    for (int i = tailLength; i > 0; i--)
    {
        tail_x[i] = tail_x[i - 1];
        tail_y[i] = tail_y[i - 1];
    }
    if (tailLength > 0)
        tail_x[0] = head_x, tail_y[0] = head_y;

    // 머리 이동
    switch (dir)
    {
    case LEFT:
        head_x--;
        break;
    case RIGHT:
        head_x++;
        break;
    case UP:
        head_y--;
        break;
    case DOWN:
        head_y++;
        break;
    }
    // 일단 게임종료를 exit로 구현
    // WALL에 부딪히면 종료
    if (map.get_stat_value(head_y, head_x) == 1)
    {
        screen_teardown();
        exit(0);
    }
    // 몸에 부딪히면 종료
    if (tailLength > 3)
        for (int i = 3; i < tailLength; i++)
        {
            if (head_x == tail_x[i] && head_y == tail_y[i])
            {
                screen_teardown();
                exit(0);
            }
        }
    if (tailLength < 2)
    {
        screen_teardown();
        exit(0);
    }
    // 맵 좌표 수정 뱀 머리:3 꼬리:4

    // 이전 꼬리 부분 좌표 제거(안지우면 그대로 두고 감)
    map.set_stat_value(tail_y[tailLength], tail_x[tailLength], 0);

    //  맵 좌표 수정
    map.set_stat_value(head_y, head_x, HEAD);
    for (int i = 0; i < tailLength; i++)
        map.set_stat_value(tail_y[i], tail_x[i], TAIL);
}

void Snake::draw()
{ // 뱀의 현재 위치에 따라 출력
    attron(COLOR_PAIR(1));
    mvprintw(tail_y[tailLength], 3 * tail_x[tailLength], "   ");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(12));              // 머리출력
    mvprintw(head_y, 3 * head_x, "   "); // 출력시 정사각형을 맞춰주기 위해 x좌표에 항상 3을 곱해야함.
    attroff(COLOR_PAIR(12));

    attron(COLOR_PAIR(11)); // 꼬리출력

    for (int i = 0; i < tailLength; i++)
        mvprintw(tail_y[i], 3 * tail_x[i], "   ");

    attroff(COLOR_PAIR(12));
}

void Snake::set_dir(Direction d)
{
    dir = d;
}

Direction Snake::get_dir()
{
    return dir;
}

int Snake::get_head_x()
{
    return head_x;
}

int Snake::get_head_y()
{
    return head_y;
<<<<<<< HEAD
}

int Snake::get_snake_length()
{
    return 1+tailLength;
}
=======
}
>>>>>>> 75aeba196b41ade45a54afeded65ee494425e03f

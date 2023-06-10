#ifndef BOARD_H
#define BOARD_H

#include "map.h"
#include "snake.h"

using namespace std;

#define BOARDSIZE 12

class Board
{
    int curB;        // Current Length
    int maxB;        // Max Length
    int countPoison; // 독 아이템 먹은 횟수
    int countGrowth; // 성장 아이템 먹은 횟수
    int countGate;   // 게이트 이용한 횟수

public:
    void init();
    WINDOW *makeMissionBoard();
    WINDOW *makeScoreBoard();
    void countPlus();                // 성장 아이템을 성장 아이템 먹은 횟수가 늘어남
    void countMinus();               // 독 아이템을 먹으면 독 아이템 먹은 횟수가 늘어남
    void countUsedGate();            // 게이트를 사용하면 게이트 이용한 횟수가 늘어남
    void count_init(Snake &snake);   // 상태 초기화
    void update_score(Snake &snake); // 아이템을 먹으면 갱신
};

#endif
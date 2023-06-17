#include <iostream>
#include <fstream>
#include "ncurses.h"
#include "map.h"
#include "board.h"
#include "item.h"
#include "snake.h"
#include "game.h"

using namespace std;

extern int count;

// 상태 초기화
void Board::init()
{
    WINDOW *scoreBoard = makeScoreBoard();
    WINDOW *missionBoard = makeMissionBoard();
}

// ScoreBoard 생성
WINDOW *Board::makeScoreBoard()
{
    WINDOW *wScoreBoard = subwin(stdscr, BOARDSIZE - 1 + 2, BOARDSIZE * 2, 0, 3 * MAPSIZE + 10);
    box(wScoreBoard, 0, 0);

    wattron(wScoreBoard, A_BOLD);
    mvwprintw(wScoreBoard, 1, 1, "Score Board");
    mvwprintw(wScoreBoard, 3, 1, "B: %d / %d", curB, maxB);
    mvwprintw(wScoreBoard, 5, 1, "+: %d", countGrowth);
    mvwprintw(wScoreBoard, 7, 1, "-: %d", countPoison);
    mvwprintw(wScoreBoard, 9, 1, "G: %d", countGate);
    mvwprintw(wScoreBoard, 11, 1, "S: %d", countSec);
    wrefresh(wScoreBoard);
    wattroff(wScoreBoard, A_BOLD);

    return wScoreBoard;
}

// MissionBoard 생성
WINDOW *Board::makeMissionBoard()
{
    WINDOW *wMissionBoard = subwin(stdscr, BOARDSIZE - 1, BOARDSIZE * 2, 15, 3 * MAPSIZE + 10);
    box(wMissionBoard, 0, 0);

    wattron(wMissionBoard, A_BOLD);
    mvwprintw(wMissionBoard, 1, 1, "Mission ");
    if (maxB >= count+4)
        mvwprintw(wMissionBoard, 3, 1, "B: %d (v)", count+4);
    else
        mvwprintw(wMissionBoard, 3, 1, "B: %d ( )", count+4);

    if (countGrowth >= count*2)
        mvwprintw(wMissionBoard, 5, 1, "+: %d (v)", count*2);
    else
        mvwprintw(wMissionBoard, 5, 1, "+: %d ( )", count*2);

    if (countPoison >= count)
        mvwprintw(wMissionBoard, 7, 1, "-: %d (v)", count);
    else
        mvwprintw(wMissionBoard, 7, 1, "-: %d ( )", count);

    if (countGate >= count)
        mvwprintw(wMissionBoard, 9, 1, "G: %d (v)", count);
    else
        mvwprintw(wMissionBoard, 9, 1, "G: %d ( )", count);
    wrefresh(wMissionBoard);
    wattroff(wMissionBoard, A_BOLD);

    return wMissionBoard;
}

// 성장 아이템을 성장 아이템 먹은 횟수가 늘어남
void Board::countPlus()
{
    countGrowth++;
}

// 독 아이템을 먹으면 독 아이템 먹은 횟수가 늘어남
void Board::countMinus()
{
    countPoison++;
}

// 게이트를 사용하면 게이트 이용한 횟수가 늘어남
void Board::countUsedGate()
{
    countGate++;
}

void Board::countSecPlus()
{
    countSec++;
}

// 상태 초기화
void Board::count_init(Snake &snake)
{
    curB = snake.get_snake_length();
    maxB = snake.get_snake_length();
    countGrowth = 0;
    countPoison = 0;
    countGate = 0;
    countSec = 0;
}

// 아이템을 먹으면 갱신
void Board::update_score(Snake &snake)
{
    // 뱀의 길이를 가져옴
    curB = snake.get_snake_length();
    if (curB > maxB)
        maxB = curB;
    makeMissionBoard();
    makeScoreBoard();
    nextStage();
}

void Board::nextStage()
{
    if (maxB >= count+4 && countGrowth >= count*2 && countPoison >= count && countGate >= count)
        gameClear();
}
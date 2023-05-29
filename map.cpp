#include <ncurses.h>

#define map_height 25
#define map_width 50

#define score_board_height 10
#define score_board_width 20

#define mission_board_height 10
#define mission_board_width 20

char map[25][50] = {
    {"2111111111111111111111111111111111111111111111112"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000034400000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"1000000000000000000000000000000000000000000000001"},
    {"2111111111111111111111111111111111111111111111112"},
};

WINDOW* makeScoreBoard()
{
    WINDOW *wScoreBoard = subwin(stdscr,score_board_height, score_board_width, 0, map_width + 10);
    box(wScoreBoard, 0, 0);
    wrefresh(wScoreBoard);
    return wScoreBoard;
}

WINDOW* makeMissionBoard()
{
    WINDOW *wMissionBoard = subwin(stdscr, mission_board_height, mission_board_width, 15, map_width + 10);
    box(wMissionBoard, 0, 0);
    wrefresh(wMissionBoard);
    return wMissionBoard;
}

WINDOW* makeMap()
{
    WINDOW *wMap = subwin(stdscr, map_height, map_width, 0, 0);

    for (int row = 0; row < map_height; row++)
    {
        for (int col = 0; col < map_width; col++)
        {
            switch (map[row][col])
            {
            case '0':
                mvwprintw(wMap, row, col, " ");
                break;
            case '1':
                mvwprintw(wMap, row, col, "+");
                break;
            case '2':
                mvwprintw(wMap, row, col, "*");
                break;
            }
        }
    }

    wrefresh(wMap);
    return wMap;
}

int main()
{
    initscr();
    start_color();

    WINDOW *wMap = makeMap();
    WINDOW *wScoreBoard = makeScoreBoard();
    WINDOW *wMissionBoard = makeMissionBoard();

    getch();
    endwin();

    return 0;
}

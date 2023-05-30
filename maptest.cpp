#include <ncurses.h>

#define map_height 25
#define map_width 25

#define score_board_height 10
#define score_board_width 20

#define mission_board_height 10
#define mission_board_width 20

int map[map_height][map_width];

void map_init(int map[][map_width])
{
    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            if (i == 0 || i == map_height - 1 || j == 0 || j == map_width - 1)
            {
                map[i][j] = 1;
            }
        }
    }
    map[0][0] = 2;
    map[0][map_width - 1] = 2;
    map[map_height - 1][0] = 2;
    map[map_height - 1][map_width - 1] = 2;
}

WINDOW *makeScoreBoard()
{
    WINDOW *wScoreBoard = subwin(stdscr, score_board_height, score_board_width, 0, map_width + 10);
    box(wScoreBoard, 0, 0);
    wrefresh(wScoreBoard);
    return wScoreBoard;
}

WINDOW *makeMissionBoard()
{
    WINDOW *wMissionBoard = subwin(stdscr, mission_board_height, mission_board_width, 15, map_width + 10);
    box(wMissionBoard, 0, 0);
    wrefresh(wMissionBoard);
    return wMissionBoard;
}

WINDOW *makeMap()
{
    WINDOW *wMap = subwin(stdscr, map_height, map_width, 0, 0);

    for (int row = 0; row < map_height; row++)
    {
        for (int col = 0; col < map_width; col++)
        {
            attron(COLOR_PAIR(map[row][col] + 1));
            printw("  ");
        }
        printw("\n");
    }

    wrefresh(wMap);
    return wMap;
}

int main()
{
    initscr();
    start_color();
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    map_init(map);

    WINDOW *wMap = makeMap();
    // WINDOW *wScoreBoard = makeScoreBoard();
    // WINDOW *wMissionBoard = makeMissionBoard();

    getch();
    endwin();

    return 0;
}
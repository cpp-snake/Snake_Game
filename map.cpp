#include <ncurses.h>
#include <locale.h>

#define MAP_HEIGHT 30
#define MAP_WIDTH 90

#define GAMESTATUS_HEIGHT 30
#define GAMESTATUS_WIDTH 50

#define IMWALL 0
#define WALL 1
#define FIELD 2

const char map[MAP_HEIGHT][(MAP_WIDTH/3) + 1] = {
    "011111111111111111111111111110",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "122222222222222222222222222221",
    "011111111111111111111111111110"
};

WINDOW* makeGameStatus(){
    WINDOW *wGameStatus = subwin(stdscr, GAMESTATUS_HEIGHT, GAMESTATUS_WIDTH, 0, MAP_WIDTH);
    box(wGameStatus, 0, 0);
    wrefresh(wGameStatus);
    return wGameStatus;
}

WINDOW* makeMap(){
    const wchar_t wall = L'\U0001F7E6';
    WINDOW *wMap = subwin(stdscr, MAP_HEIGHT, MAP_WIDTH, 0, 0);

    for(int row = 0; row < MAP_HEIGHT; row++)
        for(int column = 0; column < MAP_WIDTH; column++){
            switch(map[row][column]){
                case '0':
                case '1':
                    mvwprintw(wMap, row, column * 3, "%lc",  wall);
                    break;
                case '2':
                    break;
            }
        }
    wrefresh(wMap);
    return wMap;
}

int main() {
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    
    WINDOW* wMap = makeMap();
    WINDOW* wGameStatus = makeGameStatus();

    getch();
    // ncurses 종료
    endwin();

    return 0;
}

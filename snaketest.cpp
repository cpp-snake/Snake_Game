#include "ncurses.h"
#include "map.h"
#include "snake.h"
#include "settings.h"
#include <vector>
#include <chrono> // TICK에 맞춰 한 번 씩 이동
#include <thread>
#include <stdlib.h>
using namespace std;

bool isRudder(int ch){
    return ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_DOWN || ch == KEY_UP;
}

int main(){
    screen_setup();
    Map map("map_design.txt");
    map.init();

    init_pair_colors();

    Snake snake(8);
    snake.draw();

    // 게임 실행
    int ch;
    bool is_direction_changed = TRUE;
    auto lastUpdateTime = std::chrono::system_clock::now();  // 마지막 업데이트 시간 초기화
    std::chrono::duration<double> elapsedSeconds;
    while(true){
        ch = getch();
        if (isRudder(ch) && ch ){
            switch(ch){
                case KEY_LEFT:
                    if(snake.get_dir() == RIGHT) { screen_teardown(); exit(0); };
                    if(snake.get_dir() == LEFT)
                        is_direction_changed = FALSE;
                    else{
                        snake.set_dir(LEFT);
                        is_direction_changed = TRUE;
                    }
                    break;
                case KEY_RIGHT:
                    if(snake.get_dir() == LEFT) { screen_teardown(); exit(0); } 

                    if(snake.get_dir() == RIGHT)
                        is_direction_changed = FALSE;
                    else{
                        snake.set_dir(RIGHT);
                        is_direction_changed = TRUE;
                    }
                    break;
                case KEY_UP:
                    if(snake.get_dir() == DOWN) { screen_teardown(); exit(0); } 

                    if(snake.get_dir() == UP)
                        is_direction_changed = FALSE;
                    else{
                        snake.set_dir(UP);
                        is_direction_changed = TRUE;
                    }
                    break;
                case KEY_DOWN:
                    if(snake.get_dir() == UP) { screen_teardown(); exit(0); } 

                    if(snake.get_dir() == DOWN)
                        is_direction_changed = FALSE;
                    else{
                        snake.set_dir(DOWN);
                        is_direction_changed = TRUE;
                    }
                    break;
            }

            if(is_direction_changed){
                snake.move(map);
                snake.draw();
                lastUpdateTime = std::chrono::system_clock::now();  // 업데이트 시간 갱신
            }
        }

        // 입력이 없으면 1초마다 진행방향으로 이동
        else{
            auto currentTime = std::chrono::system_clock::now();
            elapsedSeconds = currentTime - lastUpdateTime;

            if (elapsedSeconds.count() >= TICK) {  // 1초 이상 경과한 경우
                snake.move(map);
                snake.draw();
                lastUpdateTime = currentTime;  // 업데이트 시간 갱신
            }
        }
    }

    screen_teardown();

    return 0;
}
#ifndef SNAKE_H
#define SNAKE_H

#include "map.h"
#include <vector>
using namespace std;

#define TICK 0.5

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class Snake{
    int head_x, head_y; // 뱀 머리 좌표
    vector<int> tail_x; // 뱀 꼬리 좌표 x
    vector<int> tail_y; // 뱀 꼬리 좌표 y
    int tailLength; // 뱀의 꼬리 길이
    Direction dir; // 뱀 머리 방향

public:
    Snake(int length = 2); // 길이를 인자로 받아 뱀을 생성하는 생성자
    void move(Map& map); // 키 입력에 따라서 snake 좌표 이동
    void draw(); // 뱀의 현재 위치에 따라 출력
    void set_dir(Direction d); // 방향 설정
    Direction get_dir();

    void increase_length();
    void derease_length();
};

#endif
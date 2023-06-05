#ifndef GATE_H
#define GATE_H

#include "map.h"

#define GATE 7

class Gate
{
    int gate_x, gate_y; // 게이트 좌표

public:
    Gate generate_gate(Map &map);
    void delete_gate(Map &map);
    int get_gate_x();
    int get_gate_y();
    
};

#endif
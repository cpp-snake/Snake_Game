#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "item.h"
#include "gate.h"

#define POISON_ITEM_TICK1 15
#define POISON_ITEM_TICK2 8
#define GROWTH_ITEM_TICK 12

bool isRudder(int ch);
bool meet_item(Item item, Snake snake);
bool meet_gate(Gate gate, Snake snake);
void gameFail();
void gameStart(const std::string& map_design_path);
void gameClear();

#endif
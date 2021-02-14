#ifndef TETRIS_BLOCK
#define TETRIS_BLOCK

#include "struct.h"

void new_Block(tetris* t);

void rotate_Block(tetris* t);

int move_block(tetris* t, int direction);

void debug_new_Block(tetris* t);

#endif
#ifndef TETRIS_BLOCK
#define TETRIS_BLOCK

#include "struct.h"

/* 완성 */
void new_Block(tetris* t);

void rotate_Block(tetris* t);

/* 완성 */
int move_block(tetris* t);

/* 완성 */
void fall_block(tetris* t);

#endif
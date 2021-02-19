#ifndef TETRIS_BLOCK
#define TETRIS_BLOCK

#include "struct.h"

/* 완성 */
void first_new_Block(tetris* t);    // 첫 블럭 생성 & 다음 블럭 생성

/* 완성 */
void new_Block(tetris* t);          // 다음 블럭을 현재 블럭으로 가져오기 & 다음 블럭 생성

/* 완성 */
void rotate_Block(tetris* t);       // 블럭 회전

/* 완성 */
int move_block(tetris* t);          // 블럭 충돌 계산

/* 완성 */
void fall_block(tetris* t);         // 즉시 낙하

#endif
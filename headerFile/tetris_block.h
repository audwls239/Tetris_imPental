#ifndef TETRIS_BLOCK
#define TETRIS_BLOCK

#include "struct.h"

/* 완성 */
void first_new_Block(tetris* t);    // 처음에 사용할 블럭과 다음 블럭 생성

/* 완성 */
void new_Block(tetris* t);  // 다음 블럭을 현재 블럭으로 가져오고 그 다음 블럭 생성

/* 완성 */
void rotate_Block(tetris* t);   // 블럭 회전

/* 완성 */
int move_block(tetris* t);  // 블럭 좌우 아래 충돌 판정

/* 완성 */
void fall_block(tetris* t); // 즉시 낙하

#endif
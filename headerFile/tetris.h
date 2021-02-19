#ifndef TETRIS_H
#define TETRIS_H

#include "struct.h"

#define W 119
#define SPACE 32
#define UP 65
#define DOWN 66
#define LEFT 67
#define RIGHT 68

/* 완성 */
void create_Board(tetris* t);   // 넓이*높이 게임판 생성

/* 완성 */
void tetris_Print(tetris* t);   // 화면 출력

/* 완성 */
void setting_Tetris(tetris* t, int width, int height);  // 게임셋팅 리셋

int hittest_block(tetris* t);   // 아래가 바닥이거나 블럭일때 블럭 박제 및 새 블럭 생성

void carveblock(tetris* t); // 블럭 박제

void check_line(tetris* t); // 완성된 라인 체크

void remove_line(tetris* t, int line);  // 해당 라인 삭제 후 위 라인 블럭 아래로 내리기

#endif
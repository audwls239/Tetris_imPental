#ifndef TETRIS_H
#define TETRIS_H

#include "struct.h"

#define SPACE 32
#define UP 65
#define DOWN 66
#define LEFT 67
#define RIGHT 68

/* 완성 */
void create_Board(tetris* t);   // 게임판 생성 & 초기화

/* 완성 */
void tetris_Print(tetris* t);   // 화면 출력

/* 완성 */
void setting_Tetris(tetris* t, int width, int height);  // 게임 셋팅 초기화

int hittest_block(tetris* t);   // 블럭 하단 충돌 계산

void carveblock(tetris* t);     // 하단 충돌시 블럭 박제

void check_line(tetris* t);     // 완성된 라인 확인

void remove_line(tetris* t, int line);  // 완성된 라인 삭제 & 위 라인 아래로 당기기

#endif
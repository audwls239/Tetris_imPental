#ifndef STRUCT_H
#define STRUCT_H

/* 블럭 정보 */
struct tetris_block{
    int shape[4][4];    // 블럭 모양
    int width;          // 블럭 넓이
    int height;         // 블럭 높이
};

typedef struct tetris{
    int** board;    // 게임판
    int width;      // 게임판 넓이
    int height;     // 게임판 높이
    struct tetris_block current;    // 현재 블럭
    struct tetris_block next;       // 다음 블럭
    int posX;       // 블럭 X좌표
    int posY;       // 블럭 Y좌표
    int gameover;   // 게임오버 여부(1 = 게임오버)
    int score;      // 점수
} tetris;

#endif
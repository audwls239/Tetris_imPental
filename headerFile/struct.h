#ifndef STRUCT_H
#define STRUCT_H

struct tetris_block{
    int shape[4][4];
    int width;
    int height;
};

typedef struct tetris{
    int** board;
    int width;
    int height;
    struct tetris_block current;
    int posX;
    int posY;
} tetris;

#endif
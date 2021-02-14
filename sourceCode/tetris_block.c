#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headerFile/main.h"
#include "../headerFile/struct.h"
#include "../headerFile/tetris.h"
#include "../headerFile/systemFunc.h"
#include "../headerFile/tetris_block.h"

struct tetris_block block_Shape[] = {
    {{1, 1, 1, 1}, 4, 1},

    {{  {1, 1},
        {1, 1}}, 2, 2},

    {{  {1, 1, 0},
        {0, 1, 1}}, 3, 2},

    {{  {0, 1, 1},
        {1, 1, 0}}, 3, 2},

    {{  {0, 1},
        {0, 1},
        {1, 1}}, 2, 3},

    {{  {1, 0},
        {1, 0},
        {1, 1}}, 2, 3},

    {{  {1, 1, 1},
        {0, 1, 0}}, 3, 2}
};

/* 새 블럭 생성 */
void new_Block(tetris* t){
    srand(time(NULL));

    t -> current = block_Shape[rand() % 7];
    
    t -> posX = (t -> width / 2) - (t -> current.width / 2);
    t -> posY = 0;

    if(hittest_block(t) == 1){
        tetris_Print(t);
        t -> gameover = 1;
    }
}

/* 블럭 90도 회전 */
void rotate_Block(tetris* t){
    struct tetris_block temp = {};
    int i, j;

    temp.height = t -> current.width;
    temp.width = t -> current.height;

    // temp에 90도 회전한 블럭 저장
    for(i = 0; i < t -> current.height; i++){
        for(j = 0; j < t -> current.width; j++){
            if(t -> current.shape[i][j] == 1)
                temp.shape[j][(t -> current.height - 1) - i] = 1;
        }
    }

    // 회전할 위치에 블럭이 있을시 회전 무효
    for(i = 0; i < temp.height; i++){
        for(j = 0; j < temp.width; j++){
            if(temp.shape[i][j] == 1 && t -> board[t -> posY + i][t -> posY + j] == 1)
                return;
        }
    }

    t -> current = temp;
    // 회전후 블럭이 화면 밖으로 나가는걸 방지
    if(t -> posX > t -> width - t -> current.width)
        t -> posX--;
}

/* 블럭의 게임판 충돌 판정(0 = 왼쪽으로, 1 = 오른쪽으로, 2 = 아래로) */
int move_block(tetris* t, int direction){
    int i, j;

    switch(direction){
        case 0:
            // 왼쪽에 벽이 있을 경우 이동 불가능
            if(t -> posX < 0)
                return 1;

            // 왼쪽에 블럭이 있을 경우 이동 불가능
            for(i = 0; i < t -> current.width; i++){
                for(j = 0; j < t -> current.height; j++){
                    if(t -> current.shape[j][i] == 1 && t -> board[t -> posY + j][t -> posX + i] == 1)
                        return 1;
                }
            }
            break;
        case 1:
            // 오른쪽에 벽이 있을 경우 이동 불가능
            if(t -> posX > t -> width - t -> current.width)
                    return 1;

            // 오른쪽에 블럭이 있을 경우 이동 불가능
            for(i = t -> current.width - 1; i > -1; i--){
                for(j = 0; j < t -> current.height; j++){
                    if(t -> current.shape[j][i] == 1 && t -> board[t -> posY + j][t -> posX + i] == 1)
                        return 1;
                }
            }
            break;
        case 2:
            // 아래에 바닥이 있을 경우 이동 불가능
            if(t -> posY > t -> height - t -> current.height)
                return 1;

            // 아래에 블럭이 있을 경우 이동 불가능
            for(i = t -> current.height - 1; i > -1; i--){
                for(j = 0; j < t -> current.width; j++){
                    if(t -> current.shape[i][j] == 1 && t -> board[t -> posY + i][t -> posX + j] == 1)
                        return 1;
                }
            }
    }

    return 0;
}

/* 오빠 테스트용 블럭 뽑았다 */
void debug_new_Block(tetris* t){
    static int i = 0;

    t -> current = block_Shape[i++ % 7];
    
    t -> posX = (t -> width / 2) - (t -> current.width / 2);
    t -> posY = 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headerFile/struct.h"
#include "../headerFile/tetris.h"

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

/* 판 깔아봐라 */
void setting_Tetris(tetris* t, int width, int height){
    int i, j;

    t -> width = width;
    t -> height = height;
    t -> gameover = 0;
    t -> score = 0;

    t -> board = (int**) malloc(sizeof(int*) * t -> height);

    for(i = 0; i < t -> height; i++){
        t -> board[i] = (int*) malloc(sizeof(int) * t -> width);

        for(j = 0; j < t -> width; j++)
                t -> board[i][j] = 0;
    }
}

/* 오빠 새 블럭 뽑았다 */
void new_Block(tetris* t){
    srand(time(NULL));

    t -> current = block_Shape[rand() % 7];
    
    t -> posX = (t -> width / 2) - (t -> current.width / 2);
    t -> posY = 0;

    if(hittest_block(t) == 1){
        t -> gameover = 1;
    }
}

/* 화면 출력 */
void tetris_Print(tetris* t){
    int i, j;

    system("clear");

    for(i = 0; i < t -> width + 2; i++)
        printf("0");
    printf("\n");

    for(i = 0; i < t -> height; i++){
        printf("0");
        for(j = 0; j < t -> width; j++){
            if(j >= t -> posX
            && j < t -> posX + t -> current.width
            && i >= t -> posY
            && i < t -> posY + t -> current.height
            && t -> current.shape[i - t -> posY][j - t -> posX] == 1)
                printf("#");
            else if(t -> board[i][j] == 1)
                printf("#");
            else
                printf(" ");
        }
        printf("0\n");
    }

    for(i = 0; i < t -> width + 2; i++)
        printf("0");
    printf("\n");
}

/* 90도 회전 하겠습니다(미완성) */
void rotate_Block(tetris* t){
    struct tetris_block temp = {};
    int i, j;

    temp.height = t -> current.width;
    temp.width = t -> current.height;

    for(i = 0; i < t -> current.height; i++){
        for(j = 0; j < t -> current.width; j++){
            if(t -> current.shape[i][j] == 1)
                temp.shape[j][(t -> current.height - 1) - i] = 1;
        }
    }

    t -> current = temp;
}

/* 떨어지는 블럭 아래에 블럭 있을시 게임판에 새기고 새로 생성 */
int hittest_block(tetris* t){
    int i, j;
    // 바닥에 닿았을 때
    if(t -> posY == t -> height - t -> current.height){
        carveblock(t);
        return 1;
    }

    // 아래에 블록 있을때
    for(i = t -> current.height - 1; i > -1; i--){
        for(j = 0; j < t -> current.width; j++){
            if(t -> current.shape[i][j] == 1 && t -> board[t -> posY + 1 + i][t -> posX + j] == 1){
                carveblock(t);
                return 1;
            }
        }
    }
}

/* 게임판에 블럭 새기기 */
void carveblock(tetris* t){
    int i, j;

    for(i = 0; i < t -> current.height; i++){
        for(j = 0; j < t -> current.width; j++){
            if(t -> current.shape[i][j] == 1)
                t -> board[t -> posY + i][t -> posX + j] = 1;
        }
    }

    check_line(t);
}

/* 블럭 내려 온다 블럭 내려온다~ */
void block_Gravity(tetris* t){
    t -> posY++;
    if(move_block(t, 2))
        t -> posY--;
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

/* 짬통 다 찼나? */
void check_line(tetris* t){
    int i, j;
    int line;
    int state;
    
    for(i = t -> height - 1; i > 0; i--){
        for(j = 0; j < t -> width; j++){
            if(t -> board[i][j] == 1){
                state = 1;
                continue;
            }
            // 현재 줄 체크중 중간에 빈 블럭 있을 경우 다음줄 체크
            else{
                state = 0;
                break;
            }
        }

        // 한 줄 완성시 삭제
        if(state){
            t -> score += 100;
            remove_line(t, i);
        }
    }
}

/* 야야 짬통 찼다 비워라 */
void remove_line(tetris* t, int line){
    int i;

    for(i = line; i > 0; i--){
        t -> board[i] = t -> board[i - 1];
    }
    for(i = 0; i < t -> width; i++)
        t -> board[0][i] = 0;
}

/* 오빠 테스트용 블럭 뽑았다 */
void debug_new_Block(tetris* t){
    static int i = 0;

    t -> current = block_Shape[i++ % 7];
    
    t -> posX = (t -> width / 2) - (t -> current.width / 2);
    t -> posY = 0;
}
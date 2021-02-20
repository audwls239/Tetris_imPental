#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headerFile/struct.h"
#include "../headerFile/tetris.h"
#include "../headerFile/systemFunc.h"
#include "../headerFile/tetris_block.h"


/* 게임 설정 초기화 */
void setting_Tetris(tetris* t, int width, int height){
    int i, j;

    t -> width = width;
    t -> height = height;
    t -> gameover = 0;
    t -> score = 0;
    t -> posX = 0;
    t -> posY = 0;

    t -> board = (int**) malloc(sizeof(int*) * t -> height);

    for(i = 0; i < t -> height; i++){
        t -> board[i] = (int*) malloc(sizeof(int) * t -> width);

        for(j = 0; j < t -> width; j++)
            t -> board[i][j] = 0;
    }
}

/* 화면 출력 */
void tetris_Print(tetris* t){
    int i, j;

    system("clear");

    for(i = 0; i < t -> width + 7; i++)
        printf("▧ ");
    printf("\n");

    for(i = 0; i < t -> height; i++){
        printf("▧ ");
        for(j = 0; j < t -> width; j++){
            if(j >= t -> posX
            && j < t -> posX + t -> current.width
            && i >= t -> posY
            && i < t -> posY + t -> current.height
            && t -> current.shape[i - t -> posY][j - t -> posX])
                printf("■ ");
            else if(t -> board[i][j] == 1)
                printf("■ ");
            else
                printf("  ");

        }
        printf("▧ ");

        // 다음 블럭 표시
        if(i < 4){
            for(j = 0; j < 4; j++){
                if(t -> next.shape[i][j])
                    printf("■ ");
                else
                    printf("  ");
            }
            printf("▧ ");
        }
        if(i == 4){
            for(j = 0; j < 5; j++)
                printf("▧ ");
        }
        printf("\n");
    }

    for(i = 0; i < t -> width + 2; i++)
        printf("▧ ");
    printf("\n");
}

/* 하단 충돌 판정 & 충돌 판정시 블럭 박제 */
int hittest_block(tetris* t){
    int i, j;
    int count = 0;

    // 바닥에 닿았을때
    if(t -> posY == t -> height - t -> current.height){
        carveblock(t);
        return 1;
    }

    // 아래에 블록 있을때
    for(i = t -> current.height - 1; i > -1; i--){
        for(j = 0; j < t -> current.width; j++){
            if(t -> current.shape[i][j] && t -> board[t -> posY + 1 + i][t -> posX + j]){
                carveblock(t);
                return 1;
            }
        }
    }

    return 0;
}

/* 게임판에 블럭 박제하기 */
void carveblock(tetris* t){
    int i, j;

    for(i = 0; i < t -> current.height; i++){
        for(j = 0; j < t -> current.width; j++){
            if(t -> current.shape[i][j])
                t -> board[t -> posY + i][t -> posX + j] = 1;
        }
    }

    check_line(t);
}

/* 완성된 라인 체크 */
void check_line(tetris* t){
    int i, j;
    int state;
    
    for(i = 0; i < t -> height; i++){
        for(j = 0; j < t -> width; j++){
            // 현재 줄 체크중 중간에 빈 블럭 있을 경우 다음줄 체크
            if(t -> board[i][j])
                state = 1;
            else{
                state = 0;
                break;
            }
        }

        // 한 줄 완성시 삭제 + 점수 상승
        if(state){
            t -> score += 100;
            remove_line(t, i);
        }
    }
}

/* 해당 라인 삭제 */
void remove_line(tetris* t, int line){
    int i, j;
    int* temp;

    // 위에 줄 한칸 아래로 내리기
    temp = t -> board[line];

    for(i = 0; i < line; i++)
        t -> board[line - i] = t -> board[line - 1 -i];
    t -> board[0] = temp;

    // 맨 윗줄 0으로 초기화
    for(i = 0; i < t -> width; i++)
        t -> board[0][i] = 0;
}
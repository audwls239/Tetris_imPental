#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

/* 첫 블럭 생성 & 다음 블럭 생성 */
void first_new_Block(tetris* t){
    srand(time(NULL));

    t -> current = block_Shape[rand() % 7];

    t -> posX = (t -> width / 2) - (t -> current.width / 2);
    t -> posY = 0;

    t -> next = block_Shape[(rand() + 1) % 7];
}

/* 현재 블럭에 다음 블럭 가져오기 & 다음 블럭 생성 */
void new_Block(tetris* t){
    srand(time(NULL));

    t -> current = t -> next;

    t -> next = block_Shape[rand() % 7];
    
    // 블럭 중앙 배치
    t -> posX = (t -> width / 2) - (t -> current.width / 2);
    t -> posY = 0;

    // 블럭 생성 후 충돌 판정시 게임오버
    if(hittest_block(t)){
        tetris_Print(t);
        t -> gameover = 1;
    }

}

/* 블럭 시계방향 90도 회전 */
void rotate_Block(tetris* t){
    struct tetris_block temp = {};
    int i, j;

    temp.height = t -> current.width;
    temp.width = t -> current.height;

    // temp에 90도 회전한 블럭 저장
    for(i = 0; i < t -> current.height; i++){
        for(j = 0; j < t -> current.width; j++){
            if(t -> current.shape[i][j])
                temp.shape[j][(t -> current.height - 1) - i] = 1;
        }
    }

    // 자연스러운 회전을 위한 좌표 변경
    t -> posX -= (temp.width - t -> current.width) / 2;
    t -> posY -= (temp.height - t -> current.height) / 2;

    // 바닥에서 회전시 좌표 조정
    if(t -> posY + temp.height > t -> height){
        t -> posY = t -> height - temp.height;
    }

    // 회전 후 블럭이 바닥에 묻힐때 좌표조정
    if(t -> posY < 0)
        t -> posY++;
    
    // 회전할 위치에 블럭이 있을시 회전 무효
    for(i = 0; i < temp.height; i++){
        for(j = 0; j < temp.width; j++){
            if(temp.shape[i][j] && t -> board[t -> posY + i][t -> posX + j])
                return;
        }
    }

    t -> current = temp;

    // 우측벽에서 회전후 블럭이 화면 밖으로 나가는걸 방지
    if(t -> posX > t -> width - t -> current.width)
        t -> posX = t -> width - t -> current.width;
}

/* 블럭의 게임판 충돌 판정 */
int move_block(tetris* t){
    int i, j;

    // 왼쪽에 벽이 있을 경우 이동 불가능
    if(t -> posX < 0)
        return 1;

    // 오른쪽에 벽이 있을 경우 이동 불가능
    if(t -> posX > t -> width - t -> current.width)
        return 1;

    // 아래에 바닥이 있을 경우 이동 불가능
    if(t -> posY > t -> height - t -> current.height)
        return 1;

    // 왼쪽에 블럭이 있을 경우 이동 불가능
    for(i = 0; i < t -> current.width; i++){
        for(j = 0; j < t -> current.height; j++){
            if(t -> current.shape[j][i] && t -> board[t -> posY + j][t -> posX + i])
                return 1;
        }
    }

    // 오른쪽에 블럭이 있을 경우 이동 불가능
    for(i = t -> current.width - 1; i > -1; i--){
        for(j = 0; j < t -> current.height; j++){
            if(t -> current.shape[j][i] && t -> board[t -> posY + j][t -> posX + i])
                return 1;
        }
    }

    // 아래에 블럭이 있을 경우 이동 불가능
    for(i = t -> current.height - 1; i > -1; i--){
        for(j = 0; j < t -> current.width; j++){
            if(t -> current.shape[i][j] && t -> board[t -> posY + i][t -> posX + j])
                return 1;
        }
    }

    return 0;
}

/* 즉시 낙하 */
void fall_block(tetris* t){
    while(1){
        // 내리기 반복
        t -> posY++;
        if(move_block(t))
            t -> posY--;

        // 하단 충돌시 종료
        if(hittest_block(t)){
            new_Block(t);
            break;
        }
    }
}
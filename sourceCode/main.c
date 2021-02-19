#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headerFile/struct.h"
#include "../headerFile/tetris.h"
#include "../headerFile/systemFunc.h"
#include "../headerFile/tetris_block.h"

int main(void){
    int cmd;
    int width = 12;
    int height = 18;
    struct tetris t;
    struct timespec tm;

    // 키 입력을 받기 위한 터미널 셋팅
    set_ioconfig();

    // 블럭 낙하 시간 조절
    tm.tv_sec = 0;
    tm.tv_nsec = 1000000;

    // 게임판 생성 & 블럭 생성
    setting_Tetris(&t, width, height);
    first_new_Block(&t);

    system("clear");
    puts("■ ■ ■ ■ ■ ■");
    puts("■  Tetris ■ ");
    puts("■ ■ ■ ■ ■ ■");
    puts("DOWN   = ↓");
    puts("RIGHT  = ←");
    puts("LEFT   = →");
    puts("Rotate = SPACE");
    puts("Drop   = W");
    puts("");
    puts("Press ENTER Key for start!!");
    while(10 != getchar());

    int i = 0;
    int timer = 0;
    int count = 0;

    while(t.gameover == 0){
        nanosleep(&tm, NULL);
        timer++;
        count++;

        // 키 입력 받는 구간
        while((cmd = getchar()) > 0){
            if(cmd == 27){
                if(getchar() == 91){
                    cmd = getchar();
                    switch(cmd){
                        // 하단 이동
                        case DOWN:
                            t.posY++;
                            if(move_block(&t))
                                t.posY--;
                            break;
                        // 좌측 이동
                        case LEFT:
                            t.posX++;
                            if(move_block(&t))
                                t.posX--;
                            count = 1;
                            break;
                        // 우측 이동
                        case RIGHT:
                            t.posX--;
                            if(move_block(&t))
                                t.posX++;
                            count = 1;
                            break;
                    }
                }
            }
            // 블럭 회전
            else if(cmd == 32){
                rotate_Block(&t);
                count = 1;
            }
            // 즉시 낙하
            else if(cmd == 119)
                fall_block(&t);
        }

        // timer가 350이 되면 블럭이 한칸 내려감
        if(timer % 350 == 0){
            t.posY++;
            if(move_block(&t))
                t.posY--;
        }

        // count가 350이 되면 하단 충돌 판정 계산
        if(count % 350 == 0){
            if(hittest_block(&t) == 1){
                new_Block(&t);
                count = 1;
            }
        }

        // timer가 100이 되면 화면 출력
        if(timer % 100 == 0){
            tetris_Print(&t);
            printf("[SCORE: %d] \n", t.score);
        }

        // 버그 찾기용
        for(i = 0; i < 4; i++){
            t.board[17][i] = 1;
            t.board[17][8 + i] = 1;
        }
    }

    free(t.board);
    tetris_cleanup_io();
    puts("GAME OVER!!");
    return 0;
}
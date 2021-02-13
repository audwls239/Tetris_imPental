#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headerFile/main.h"
#include "../headerFile/struct.h"
#include "../headerFile/tetris.h"
#include "../headerFile/systemFunc.h"

int main(void){
    int cmd;
    int width = 12;
    int height = 15;
    struct tetris t;
    struct timespec tm;

    // 키 입력을 받기 위한 터미널 셋팅
    set_ioconfig();

    // 블럭 낙하 시간 조절
    tm.tv_sec = 0;
    tm.tv_nsec = 1000000;

    // 게임판 생성 & 블럭 생성
    setting_Tetris(&t, width, height);
    new_Block(&t);

    system("clear");
    puts("##########");
    puts("# Tetris #");
    puts("##########");
    puts("↓  = DOWN");
    puts("←  = RIGHT");
    puts("→  = LEFT");
    puts("Rotate = Space");
    puts("");
    puts("Press to Enter to start!!");
    while(1){    
        if(getchar() == 10) break;
    }

    int i = 0;
    int timer = 0;
    int count = 0;

    while(t.gameover == 0){
        nanosleep(&tm, NULL);
        timer++;
        count++;

        while((cmd = getchar()) > 0){
            if(cmd == 27){
                if(getchar() == 91){
                    cmd = getchar();
                    switch(cmd){
                        case DOWN:
                            block_Gravity(&t);
                            break;
                        case LEFT:
                            t.posX++;
                            if(move_block(&t, 1))
                                t.posX--;
                            count = 1;
                            break;
                        case RIGHT:
                            t.posX--;
                            if(move_block(&t, 0))
                                t.posX++;
                            count = 1;
                            break;
                    }
                }
            }
            else if(cmd == 32)
                rotate_Block(&t);
            // else if(cmd == 119)
            //     hittest_block(&t);
            // else if(cmd == 101)
            //     debug_new_Block(&t);
        }

        if(timer % 350 == 0)
            block_Gravity(&t);

        if(count % 350 == 0){
            if(hittest_block(&t) == 1)
                new_Block(&t);
        }

        if(timer % 50 == 0){
            tetris_Print(&t);
            printf("[SCORE: %d] \n", t.score);
        }
    }

    free(t.board);
    tetris_cleanup_io();
    puts("GAME OVER!!");
    return 0;
}
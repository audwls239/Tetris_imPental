#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headerFile/struct.h"
#include "../headerFile/tetris.h"
#include "../headerFile/systemFunc.h"
#include "../headerFile/tetris_block.h"

void logOut(tetris* t, Log* log){
    int i, j;
        
    fprintf(log -> ch1, "%4d년, ", log -> now -> tm_year);
    fprintf(log -> ch1, "%2d월, ", log -> now -> tm_mon);
    fprintf(log -> ch1, "%2d일, ", log -> now -> tm_mday);
    fprintf(log -> ch1, "%2d시, ", log -> now -> tm_hour);
    fprintf(log -> ch1, "%2d분, ", log -> now -> tm_min);
    fprintf(log -> ch1, "%2d초\n", log -> now -> tm_sec);

    for(i = 0; i < t -> width + 7; i++)
        fprintf(log -> ch1, "▧");
    fprintf(log -> ch1, "\n");

    for(i = 0; i < t -> height; i++){
        fprintf(log -> ch1, "▧");
        for(j = 0; j < t -> width; j++){
            if(j >= t -> posX
            && j < t -> posX + t -> current.width
            && i >= t -> posY
            && i < t -> posY + t -> current.height
            && t -> current.shape[i - t -> posY][j - t -> posX])
                fprintf(log -> ch1, "■");
            else if(t -> board[i][j])
                fprintf(log -> ch1, "■");
            else
                fprintf(log -> ch1, "  ");

        }
        fprintf(log -> ch1, "▧");

        // 다음 블럭 표시
        if(i < 4){
            for(j = 0; j < 4; j++){
                if(t -> next.shape[i][j] == 1){
                    fprintf(log -> ch1, "■");
                }
                else
                    fprintf(log -> ch1, "  ");
            }
            fprintf(log -> ch1, "▧");
        }
        if(i == 4){
            for(j = 0; j < 5; j++)
                fprintf(log -> ch1, "▧");
        }
        fprintf(log -> ch1, "\n");
    }

    for(i = 0; i < t -> width + 2; i++)
        fprintf(log -> ch1, "▧");
    fprintf(log -> ch1, "\n");
    fprintf(log -> ch1, "[SCORE: %d] \n", t -> score);
    
    return;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ROW 15
#define COL 20
#define KEYROW 5
#define KEYCOL 5


/*print2D fucntion is for printing 2 dimentional arrays*/
void print2D(int ** KEYMAP,int keyrow, int keycol){
    for(size_t i2 = 0; i2 < keyrow; i2++){
       for(size_t i3 = 0; i3 < keycol; i3++)
               printf("%d ",KEYMAP[i2][i3]);
       printf("\n");
    }
}
/*
inputs:
    int ** KEY     : KEY matrix;
    int ** MAP     : MAP matrix;
    int keyColSize : column size of the KEY matrix;
    int keyRowSize : row size of the KEY matrix;
    int mapColSize : column size of the MAP matrix;
    int mapRowSize : row size of the MAP matrix;
    int col        : current position of tthe col cursor;
    int row        : current position of the row cursor;
Goal: 
    Goal of that function is to find treasure while moving around a MAP matrix at the directions 
    which can be finded as dot producting the KEY matrix and the sub matrix of MAP matrix.if the
    result is equal to zero it will return 1 and finish to execute it 
Returns:
    1 if it founded the location of the treasure
*/
int findtreasure(int ** KEY, int ** MAP,int keyColSize,int keyRowSize,int mapColSize,int mapRowSize, int col, int row){
    
    int result = 0; /*result = unmoded dot product*/
    int temprow = row; /*temprow is for moving at submatrix*/
    int kcol;
    int krow;
    for(kcol = 0; kcol <keyColSize; col++,kcol++){  
        temprow = row;
        for(krow = 0; krow < keyRowSize; temprow++,krow++)
            result += KEY[kcol][krow] * MAP[col][temprow]; 
    }
    row = temprow;
    int curcolpos = (col+col-keyColSize)/2;
    int currowpos = (row+row-keyRowSize)/2;
    int resultmod = result % 5;

    if(resultmod == 0){
        printf("%d,%d;%d\n",curcolpos,currowpos,result);
        return 1;
    }
    if(resultmod == 1){
        printf("%d,%d;%d\n",curcolpos,currowpos,result);
        if((col-2*keyColSize) >= 0)
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col-2*keyColSize,row-keyRowSize);
        else
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col,row-keyRowSize);
    }
    if(resultmod == 2){
        printf("%d,%d;%d\n",curcolpos,currowpos,result);
        if((col) <= mapColSize-keyColSize)
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col,row-keyRowSize);
        else
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col-2*keyColSize,row-keyRowSize);
    }
    if(resultmod == 3){
        printf("%d,%d;%d\n",curcolpos,currowpos,result);
        if((row) <= mapRowSize-keyRowSize)
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col-keyColSize,row);
        else
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col-mapColSize,row-2*mapRowSize);
    }
    if(resultmod == 4){
        printf("%d,%d;%d\n",curcolpos,currowpos,result);
        if((row - 2 * keyRowSize) >= 0)
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col-mapColSize,row-2*mapRowSize);
        else
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col-keyColSize,row);
    }
    return 0;
}
  
    



int main(int argc, char const *argv[])
{
   
    /** --------------------------------------------
     * KEYMAP 2d KEYMAP
     * fopentdeki filename i degistir
     * 
     */
    int ** KEYMAP = malloc(sizeof(int *) * ROW);
    int i1;
    for (i1 = 0; i1 < COL; ++i1) 
        KEYMAP[i1] = malloc(sizeof(int) * COL);
    /*DECLARATIONS*/
    char *char_readline = NULL; 
    char  char_readline_split[KEYCOL*2][KEYROW*2]; 
    size_t chars_len = 0;
    size_t char_readline_length;
    FILE *fptr;
    /*DECLARATIONS*/
    if ((fptr = fopen("keymatrix1.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    int keycol = 0;
    int keyrow = 0;
    while ((char_readline_length = getline(&char_readline, &chars_len, fptr)) != -1) { /*That reads line by line from chars file and stops when it has reached end of file*/
        char *token = NULL;
        int n_tokens = 0;
        keycol = 0;
        token = strtok(char_readline, " ");
        while (token != NULL) { 
            strcpy(char_readline_split[keycol], token);
            KEYMAP[keyrow][keycol] = atoi(char_readline_split[keycol]);
            token = strtok(NULL, " ");
            n_tokens++;
            keycol++;
        }
        keyrow++;
    }
    fclose(fptr);
    /* fileread -------------------------------------------------------*/
    /** --------------------------------------------
     * KEYMAP 2d KEYMAP
     * fopentdeki filename i degistir
     * 
     */
    
    int ** MAP = malloc(sizeof(int *) * ROW);
    int i2;
    for (i2 = 0; i2 < COL; ++i2) 
        MAP[i2] = malloc(sizeof(int) * COL);
    /*DECLARATIONS*/
    char *char_readline1 = NULL; 
    char  char_readline_split1[COL*2][ROW*2]; 
    size_t chars_len1 = 0;
    size_t char_readline_length1;
    FILE *fptr1;
    /*DECLARATIONS*/
    if ((fptr1 = fopen("mapmatrix1.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    int mapcol = 0;
    int maprow = 0;
    while ((char_readline_length1 = getline(&char_readline1, &chars_len1, fptr1)) != -1) { /*That reads line by line from chars file and stops when it has reached end of file*/
        char *token1 = NULL;
        int n_tokens1 = 0;
        mapcol = 0;
        token1 = strtok(char_readline1, " ");
        while (token1 != NULL) { 
            strcpy(char_readline_split1[mapcol], token1);
            MAP[maprow][mapcol] = atoi(char_readline_split1[mapcol]);
            token1 = strtok(NULL, " ");
            n_tokens1++;
            mapcol++;
        }
        maprow++;
    }
    fclose(fptr1);
    /* fileread -------------------------------------------------------*/

    // print2D(KEYMAP,keyrow,keycol);
    // printf("\n\n\n");
    // print2D(MAP,maprow,mapcol);   
    findtreasure(KEYMAP,MAP,KEYCOL,KEYROW,ROW,COL,0,0);
    return 0;
}
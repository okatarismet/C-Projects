
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*print2D fucntion is for printing 2 dimentional arrays*/
void print2D(int ** KEYMAP,int keyrow, int keycol){
    for(size_t i2 = 0; i2 < keyrow; i2++){
       for(size_t i3 = 0; i3 < keycol; i3++)
               printf("%d ",KEYMAP[i2][i3]);
       printf("\n");
    }
}
/*
Inputs:
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
int findtreasure(int ** KEY, int ** MAP,int keyColSize,int keyRowSize,int mapColSize,int mapRowSize, int col, int row,char * argv[]){
    
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
    int curcolpos = (col+col-keyColSize)/2; /* Calculate current col position */
    int currowpos = (row+row-keyRowSize)/2; /* Calculate current row position */
    int resultmod = result % 5;             /* Calculate the mod to 5 */

    FILE *optr = fopen(argv[5],"a");

    if(resultmod == 0){/*Treasure found*/
        fprintf(optr,"%d,%d;%d\n",curcolpos,currowpos,result); /* Print the data*/
        fclose(optr);
        return 1;                                        /* return 1 and terminate the function*/
    }
    if(resultmod == 1){ /*Go Up*/
        fprintf(optr,"%d,%d;%d\n",curcolpos,currowpos,result); /* Print the data*/
        fclose(optr);
        if((col-2*keyColSize) >= 0)
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col-2*keyColSize,row-keyRowSize,argv);
        else
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col,row-keyRowSize,argv);
    }
    if(resultmod == 2){ /*Go Down*/
        fprintf(optr,"%d,%d;%d\n",curcolpos,currowpos,result); /* Print the data*/
        fclose(optr);
        if((col) <= mapColSize-keyColSize)
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col,row-keyRowSize,argv);
        else
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col-2*keyColSize,row-keyRowSize,argv);
    }
    if(resultmod == 3){ /*Go Right*/
        fprintf(optr,"%d,%d;%d\n",curcolpos,currowpos,result); /* Print the data*/
        fclose(optr);
        if((row) <= mapRowSize-keyRowSize)
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col-keyColSize,row,argv);
        else
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col-mapColSize,row-2*mapRowSize,argv);
    }
    if(resultmod == 4){ /*Go Left*/
        fprintf(optr,"%d,%d;%d\n",curcolpos,currowpos,result); /* Print the data*/
        fclose(optr);
        if((row - 2 * keyRowSize) >= 0)
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col-mapColSize,row-2*mapRowSize,argv);
        else
            return findtreasure(KEY,MAP,keyColSize,keyRowSize,mapColSize,mapRowSize,col-keyColSize,row,argv);
    }
    return 0;
}
  
/*
Inputs:
    int ** MAP     : MAP matrix that will be loaden form  text file;
    char * filename: name of the text file
Goal: 
    Goal of that function is to read a text and convert it to 2D Array
Returns:
    void
*/
void readfile2Darr(int ** MAP,char * filename,int col,int row){

    char *char_readline = NULL; 
    char  char_readline_split[col*2][row*2]; 
    size_t chars_len = 0;
    size_t char_readline_length;
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL) {
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
            strcpy(char_readline_split[keycol], token);              /* Copy the token to our array*/
            MAP[keyrow][keycol] = atoi(char_readline_split[keycol]); /* Change to integer and assign the value*/
            token = strtok(NULL, " ");
            n_tokens++;
            keycol++;
        }
        keyrow++;
    }
    fclose(fptr);
}
int main(int argc, char *argv[])
{
    /*Allocating memory <--*/
    char *token1 = strtok(argv[1],"x");
	int ROW = atoi(token1);
	token1 = strtok(NULL,"x");
	int COL = atoi(token1);
    int KEYCOL = atoi(argv[2]);
    int KEYROW = atoi(argv[2]);


    int ** KEYMAP = malloc(sizeof(int *) * KEYROW);
    int i1;
    for (i1 = 0; i1 < COL; ++i1) 
        KEYMAP[i1] = malloc(sizeof(int) * KEYCOL);
    /*-->*/
    /*read file to allocated memory*/
    
    readfile2Darr(KEYMAP,argv[4],ROW,COL);
    /*Allocating memory <--*/
    int ** MAP = malloc(sizeof(int *) * ROW);
    int i2;
    for (i2 = 0; i2 < COL; ++i2) 
        MAP[i2] = malloc(sizeof(int) * COL);
    /*-->*/
     /*read file to allocated memory*/
    readfile2Darr(MAP,argv[3],ROW,COL);
    /* send data to findtreasure function and start the recursive part*/
    FILE *outputfile = fopen(argv[5],"w+");
	fclose(outputfile);
    findtreasure(KEYMAP,MAP,KEYCOL,KEYROW,ROW,COL,0,0,argv);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 24 ekim carsamba
 * dynamic memory allocate edildi.
 * file dan map okundu
 * Map[][] E yazildi
 * fakat return edince mainin icinde 46 46 gozukuyor


*/
 int** ayran(int row_size,int col_size){
    int** MAP = malloc(sizeof(int *) * row_size);
    int i1;
    for (i1 = 0; i1 < row_size; ++i1) {
        MAP[i1] = malloc(sizeof(int) * col_size);
    }
    int l;
    int i;
    for (l = 0; l < row_size; ++l) { /*set map to "."*/
        for (i = 0; i < col_size; ++i) {
            MAP[l][i] = '.';
        }
    }


    FILE *aptr; /*chars file pointer*/
    size_t char_readline_length;
    char *command_readline = NULL; /*that includes a line of the commands file like "lOADMAP 5 5"*/
    size_t command_len = 0;

    if((aptr = fopen("mapmatrix1.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
       while ((char_readline_length = getline(&command_readline, &command_len, aptr)) != -1) { /*that reads line by line from commands file and stop when EOF*/

        /* */
        /* Parse into char_readline_split */
        char command_readline_split[25][25] = {0}; /*that includes command_readlines splitted version like {"LOADMAP","5","5"}*/
        char *token = NULL;
        int n_tokens = 0, i = 0,j = 0;
        token = strtok(command_readline, " ");
        while (token != NULL) {
            strcpy(command_readline_split[i], token);
            MAP[j][i] = atoi(command_readline_split[i]);
            printf("%d ",MAP[j][i]);
            token = strtok(NULL, " ");
            n_tokens++;
            i++;
        }
        printf("%s ","\n"); 
        j++;

    }
 return MAP;
 }

int main(int argc, char const *argv[])
{
   int **MAP;
   
   MAP = ayran(30,30);
   printf("\n--> %p \n",MAP);

for(int i = 0; i < 900; i++)
{
    int a = **(MAP + sizeof(int));
    printf("%d",a);
}


    return 0;
}
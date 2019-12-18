#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LLENGTH 100
#define RLENGTH 100

char * rdline(char filename[50], FILE* fh);
int * trim(char * line, int * newline);
/**
 * 28 kasim 23:11
 *  eksileri unutmusum ona bakiyordum
 *  cogu sey tamam map ler yuklendi fakat dynamiclik den bahsedemeyiz.
 *  
 * =======================
 * trim
 * INPUTS: (untrimed string, trimed string)
 * 
 * =======================
 * rdline
 * INPUTS: ("map.txt",fh) (char filename[50], FILE * fh)
 * RETURN: a line
 * if it reachs EOF it returns "EOF"
 */
int getlinel(char * line){
    int length = 0;
    while(line[length] != '\0')
        length++;
    return length; 
}



char * rdline(char filename[50], FILE* fh){ 
    //read line by line
    char* line = malloc(LLENGTH);
    if (fgets(line, LLENGTH, fh) != NULL)  {
        return line;
    }
    else return "EOF";
    free(line);    // dont forget to free heap memory
}


int * trim(char *line, int * newline){
    int linecounter = 0;
    int newlinecounter = 0;
    char ch = '0';
    while(line[linecounter] != '\0'){
        
        printf("\n------ Current line element %d. %c -----\n",linecounter,line[linecounter]);
        if(line[linecounter] !=  ' ' && line[linecounter] != '\t'){
            if (line[linecounter] == '-'){
                char str[2];
                str[0] = line[linecounter];
                linecounter++;
                str[1] = line[linecounter];
                str[2] = '\0'; 
                newline[newlinecounter] = atoi(str);
                printf("\nnewline %d str %s\n",newline[newlinecounter],str);
            }
            else {
                 newline[newlinecounter] = line[linecounter];
            }
            newlinecounter++;
        }
        linecounter++;
        if(line[linecounter] == 'E'){
            printf("cikti");
            return newline;
        }
    }
    return newline;
}


int readfileto2D(char filename[50],int MAP[RLENGTH][LLENGTH]){
    FILE* fh = fopen(filename, "r");
    if (fh == NULL){
        printf("file does not exists %s", filename);
        return 0;
    }
    int newline[LLENGTH];
    int k = 0;
    do{
        trim(rdline(filename,fh),newline);
        if (newline[0] == 'E'){
            break;
        }
        int i = 0;
        while( newline[i] != '\0' && newline[i] != ' '){
            MAP[k][i] = newline[i];
            i++;
        }
        //  printf("%ls",MAP[k]);
        k++;
    }while(1);
    return 0 ;  
}


int main(int argc, char const *argv[]){
    int MAP[RLENGTH][LLENGTH];
    // readfileto2D("mapmatrix1.txt",MAP);
    
    // for(size_t i = 0; i < RLENGTH; i++)
    // {
        
    //     for(size_t k = 0; k < 18; k++)
    //     {
    //         printf("%c",MAP[i][k]);
    //     }
    //     printf("%s","\n");
        
    // }
    
    int KEY[RLENGTH][LLENGTH];
    readfileto2D("keymatrix1.txt",KEY);
    for(size_t i = 0; i < 6; i++)
    {
        
        for(size_t k = 0; k < 6; k++)
        {
            printf("%d ",KEY[i][k]);
        }
        printf("%s","\n");
        
    }
    

    
    
    return 0;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//17:33 okuldaki en son yapilsi
// struct yapisina da atilan caracketrlerin neden outer da basamadigimi anlamaya calisiyorum.
struct type{
    char char_name[20];
    int char_HP,char_DP,char_XP,char_location_x,char_location_y;
};
int main ()
{
    //CHAR READ PARSE LOAD
    /* DECLARATIONS */
    struct type hero[4];
    struct type monster[6];
    FILE *fptr;
    char * char_readline = NULL;
    char char_readline_parsed[4][25];
    int monster_count = 0,hero_count = 0;
    size_t len = 0;
    ssize_t char_readline_length;
    /* */
    /* FILE READ INTO CHARS_READLINE*/
    if ((fptr = fopen("chars_1.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
 for (int j1 = 0; j1 <10 ; ++j1) {
     char_readline_length = getline(&char_readline, &len, fptr);
     /* */
     /* Parse into char_readline_parsed */
     char *token = NULL;
     int n_tokens = 0, i = 0;

     token = strtok(char_readline, ",");
     while (token != NULL) {
         strcpy(char_readline_parsed[i], token);
         token = strtok(NULL, ",");
         n_tokens++;
         i++;
     }
     /* ASSIGN TO STRUCT*/
     //________________________________________

      if (strcmp(char_readline_parsed[0], "HERO") == 0) {
            strcpy(hero[hero_count].char_name, char_readline_parsed[1]);
            hero[hero_count].char_HP = atoi(char_readline_parsed[2]);
            hero[hero_count].char_DP = atoi(char_readline_parsed[3]);
          hero_count++;
        }
        if (strcmp(char_readline_parsed[0], "MONSTER") == 0) {
            strcpy(monster[monster_count].char_name, char_readline_parsed[1]);
            monster[monster_count].char_HP = atoi(char_readline_parsed[2]);
            monster[monster_count].char_DP = atoi(char_readline_parsed[3]);
            monster_count++;
        }
     /**/
 }
    //CHAR READ PARSE LOAD HAS DONE




  return 0;
}
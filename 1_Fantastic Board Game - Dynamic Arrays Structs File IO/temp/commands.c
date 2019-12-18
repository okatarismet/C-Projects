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
    char * command_readline = NULL;
    char char_readline_parsed[4][25];
    char command_readline_parsed[10][25] ={0};
    int monster_count = 0,hero_count = 0;
    size_t chars_len = 0;
    size_t command_len= 0;
    ssize_t char_readline_length;
    ssize_t command_readline_lenght;
    int load_row = 0,load_col = 0;
    /* */
    /* FILE READ INTO CHARS_READLINE*/
    if ((fptr = fopen("chars_1.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
 for (int j1 = 0; j1 <10 ; ++j1) {
     char_readline_length = getline(&char_readline, &chars_len, fptr);
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
 }    //CHAR READ PARSE LOAD HAS DONE
      //Commands CRPL
fclose(fptr);
if ((fptr = fopen("commands_1.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
 for (int j1 = 0; j1 <3 ; ++j1) {
     char_readline_length = getline(&command_readline, &command_len, fptr);
     /* */
     /* Parse into char_readline_parsed */
     char *token = NULL;
     int n_tokens = 0, i = 0;

     token = strtok(command_readline, " ");
     while (token != NULL) {
         strcpy(command_readline_parsed[i], token);
         token = strtok(NULL, " ");
         n_tokens++;
         i++;
     }
     printf("----------------------------------------------\n\t%s\n",command_readline_parsed[0]);
     /* in that scope we can use the array which includes the commadn variables
     *commands_readline_parsed[%d][%d];
      *
*    */
      if(strcmp(command_readline_parsed[0],"LOADMAP") == 0){
                            printf("GIRDU loadmap\n");

          load_row = atoi(command_readline_parsed[1]);
          load_col = atoi(command_readline_parsed[2]);
         int(*MAP)[load_col] = malloc((sizeof *MAP) * load_row);

      }
      if(strcmp(command_readline_parsed[0],"PUT") == 0){
          printf("ttt");
          int hero_put = 0,monster_put = 0,x = 0;
          if(strcmp(command_readline_parsed[1],"HERO")==0){
                                printf("GIRDU a %d",x);

              while(command_readline_parsed[2+3*hero_put] != 0){
                  printf("GIRDU; %d",x);
                  for (int i = 0; i <4 ; ++i) {
                      if(strcmp(command_readline_parsed[2+3*x],hero[i].char_name) == 0){
                          hero[i].char_location_x = atoi(command_readline_parsed[3+3*x]);
                          hero[i].char_location_y = atoi(command_readline_parsed[4+3*x]);
                      }
                  }
                  x++;
              }
          }
          if(strcmp(command_readline_parsed[1],"MONSTER")==0){
              while(command_readline_parsed[2+3*monster_put] != 0){
                  for (int i = 0; i <4 ; ++i) {
                      if(strcmp(command_readline_parsed[2+3*x],monster[i].char_name) == 0){
                          monster[i].char_location_x = atoi(command_readline_parsed[3+3*x]);
                          monster[i].char_location_y = atoi(command_readline_parsed[4+3*x]);
                      }
                  }
                  x++;
              }
          }
      }
      if(strcmp(command_readline_parsed[0],"SHOW") == 0){
           if(strcmp(command_readline_parsed[1],"MAP") == 0){}
           if(strcmp(command_readline_parsed[1],"HERO") == 0){}
           if(strcmp(command_readline_parsed[0],"MONSTER") == 0){}
      }
      if(strcmp(command_readline_parsed[0],"ATTACK") == 0){}






 }    //CHAR READ PARSE LOAD HAS DONE






  return 0;
}
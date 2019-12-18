#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define hero_size 4
#define monster_size 6
//17:33 okuldaki en son yapilsi
// struct yapisina da atilan caracketrlerin neden outer da basamadigimi anlamaya calisiyorum.


// en son map e realloclayip adamlarin konumunu atmaya caisiyordum.
// 124 line number
struct type{
    char char_name[20];
    int char_HP,char_DP,char_XP,char_location_x,char_location_y,char_life;
};
int main () {
    //CHAR READ PARSE LOAD
    /* DECLARATIONS */
    struct type hero[hero_size];
    for (int m1 = 0; m1 < hero_size; ++m1) {
        hero[m1].char_XP = 0;
        hero[m1].char_DP = 0;
        hero[m1].char_HP = 0;
        hero[m1].char_life = 1;
        hero[m1].char_location_x = 0;
        hero[m1].char_location_y = 0;
    }
    struct type monster[monster_size];
    for (int m = 0; m < monster_size; ++m) {
        monster[m].char_XP = 0;
        monster[m].char_DP = 0;
        monster[m].char_HP = 0;
        monster[m].char_life = 1;
        monster[m].char_location_x = 0;
        monster[m].char_location_y = 0;
    }
    FILE *fptr;
    char *char_readline = NULL;
    char *command_readline = NULL;
    char char_readline_parsed[4][25];
    char command_readline_parsed[25][25] = {0};
    int monster_count = 0, hero_count = 0;
    size_t chars_len = 0;
    size_t command_len = 0;
    ssize_t char_readline_length;
    ssize_t command_readline_lenght;
    int load_row = 0, load_col = 0;
 int **MAP = malloc(load_row * sizeof(int *));
    for (int i = 0; i < load_row; i++)
        MAP[i] = malloc(load_col * sizeof(int));
    /* FILE READ INTO CHARS_READLINE*/
    if ((fptr = fopen("chars_1.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    while ((char_readline_length = getline(&char_readline, &chars_len, fptr)) != -1) {
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
    if ((fptr = fopen("commands_1.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
while((char_readline_length = getline(&command_readline, &command_len, fptr)) != -1) {
            printf(" -->>\t%s\n",command_readline);

    printf("\n");
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
        /* in that scope we can use the array which includes the commadn variables
        *commands_readline_parsed[%d][%d];
         *
   *    */
        if (strcmp(command_readline_parsed[0], "LOADMAP") == 0) {

            load_row = atoi(command_readline_parsed[1]);
            load_col = atoi(command_readline_parsed[2]);
            MAP = realloc(MAP, 12 * sizeof(int *));
            for (int j = 0; j < rows; j++)
                MAP[j] = realloc(MAP[j], 32 * sizeof(int));
            for (int l = 0; l < 5; ++l) {
                for (int i = 0; i < 5; ++i) {
                    MAP[l][i] = '.';
                }

            }


        }
        // BASLANGIC OF PUT
        if (strcmp(command_readline_parsed[0], "PUT") == 0) {
            int hero_put = 0, monster_put = 0, x = 0;
            if (strcmp(command_readline_parsed[1], "HERO") == 0) {
                x = 0;
                while (x < 4) {
                    for (int i = 0; i < hero_size; ++i) {
                        if (command_readline_parsed[2 + 3 * x] != 0) {
                            int a = 2 + 3 * x;
                            if (strcmp(command_readline_parsed[a], hero[i].char_name) == 0) {
                                hero[i].char_location_x = atoi(command_readline_parsed[a + 1]);
                                hero[i].char_location_y = atoi(command_readline_parsed[a + 2]);
                                MAP[atoi(command_readline_parsed[a + 1])][atoi(
                                        command_readline_parsed[a + 2])] = hero[i].char_name[0];
                            }
                        }
                    }
                    x++;
                    i = 0;
                }
            }
            if (strcmp(command_readline_parsed[1], "MONSTER") == 0) {
                x = 0;
                while (x < 6) {
                    for (int i = 0; i < monster_size; ++i) {
                        int a = 2 + 3 * x;
                        if (strcmp(command_readline_parsed[a], monster[i].char_name) == 0) {
                            monster[i].char_location_x = atoi(command_readline_parsed[a + 1]);
                            monster[i].char_location_y = atoi(command_readline_parsed[a + 2]);
                            MAP[atoi(command_readline_parsed[a + 1])][atoi(
                                    command_readline_parsed[a + 2])] = monster[i].char_name[0];
                        }
                    }
                    x++;
                    i = 0;
                }
            }
        } // END OF PUT
        if (strcmp(command_readline_parsed[0], "SHOW") == 0) {
            if (strcmp(command_readline_parsed[1], "MAP\n") == 0) {
                printf("MAP STATUS\n");
                for (int j = 0; j < load_row; ++j) {
                    for (int k = 0; k < load_col; ++k) {
                        printf("%c ", MAP[j][k]);
                    }
                    printf("\n");
                }
            }
            if (strcmp(command_readline_parsed[1], "HERO\n") == 0) {
                printf("HERO STATUS\n");
                for (int j = 0; j < hero_size; ++j) {
                    printf("%s HP:%d XP: %d\n", hero[j].char_name, hero[j].char_HP, hero[j].char_XP);
                }
            }
            if (strcmp(command_readline_parsed[1], "MONSTER\n") == 0) {
                printf("MONSTER STATUS\n");
                for (int j = 0; j < monster_size; ++j) {
                    printf("%s HP:%d\n", monster[j].char_name, monster[j].char_HP);
                }
            }
        }


        if (strcmp(command_readline_parsed[0], "ATTACK") == 0) {

            if (strcmp(command_readline_parsed[1], "HERO\n") == 0) {
                printf("HERO S ATTACKED\n");
                for (int j = 0; j < hero_size; ++j) {
                    if (hero[j].char_life == 1) {
                        for (int k = 0; k < monster_size; ++k) {
                            if (monster[k].char_location_x == hero[j].char_location_x - 1 &&
                                monster[k].char_location_y == hero[j].char_location_y) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                    hero[j].char_XP++;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x - 1 &&
                                monster[k].char_location_y == hero[j].char_location_y + 1) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                    hero[j].char_XP++;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x &&
                                monster[k].char_location_y == hero[j].char_location_y + 1) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                    hero[j].char_XP++;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x + 1 &&
                                monster[k].char_location_y == hero[j].char_location_y + 1) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                    hero[j].char_XP++;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x + 1 &&
                                monster[k].char_location_y == hero[j].char_location_y) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                    hero[j].char_XP++;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x + 1 &&
                                monster[k].char_location_y == hero[j].char_location_y - 1) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                    hero[j].char_XP++;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x &&
                                monster[k].char_location_y == hero[j].char_location_y - 1) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                    hero[j].char_XP++;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x - 1 &&
                                monster[k].char_location_y == hero[j].char_location_y - 1) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                    hero[j].char_XP++;
                                }
                            }
                        }
                    }
                }
            }
            if (strcmp(command_readline_parsed[1], "MONSTER\n") == 0) {
                printf("MONSTER S ATTACKED\n");

                for (int j = 0; j < monster_size; ++j) {
                    if (monster[j].char_life == 1) {
                        for (int k = 0; k < hero_size; ++k) {
                            if (hero[k].char_location_x == monster[j].char_location_x - 1 &&
                                hero[k].char_location_y == monster[j].char_location_y) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x - 1 &&
                                hero[k].char_location_y == monster[j].char_location_y + 1) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x &&
                                hero[k].char_location_y == monster[j].char_location_y + 1) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x + 1 &&
                                hero[k].char_location_y == monster[j].char_location_y + 1) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x + 1 &&
                                hero[k].char_location_y == monster[j].char_location_y) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x + 1 &&
                                hero[k].char_location_y == monster[j].char_location_y - 1) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x &&
                                hero[k].char_location_y == monster[j].char_location_y - 1) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x - 1 &&
                                hero[k].char_location_y == monster[j].char_location_y - 1) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                        }
                    }
                }
            } // if attack is monsters
            for (int l = 0; l < hero_size; ++l) {
                if (hero[l].char_life == 0) {
                    MAP[hero[l].char_location_x][hero[l].char_location_y] = '.';
                }
            }
            for (int l = 0; l < monster_size; ++l) {
                if (monster[l].char_life == 0) {
                    MAP[monster[l].char_location_x][monster[l].char_location_y] = '.';
                }
            }
        } // attack block


        // BASLANGIC OF MOVE
        if (strcmp(command_readline_parsed[0], "MOVE") == 0) {
            int hero_put = 0, monster_put = 0, x = 0;
            if (strcmp(command_readline_parsed[1], "HERO") == 0) {
                printf("HERO S MOVED\n");
                x = 0;
                while (x < 4) {
                    for (int i = 0; i < hero_size; ++i) {
                        if (command_readline_parsed[2 + 3 * x] != 0) {
                            int a = 2 + 3 * x;

                            if (strcmp(command_readline_parsed[a], hero[i].char_name) == 0) {
                                if (hero[i].char_life == 0) {
                                    printf("%s can t move. Dead.\n", hero[i].char_name);
                                } else if (atoi(command_readline_parsed[a + 1]) > load_row - 1 ||
                                           atoi(command_readline_parsed[a + 1]) < 0 ||
                                           atoi(command_readline_parsed[a + 2]) > load_col - 1 ||
                                           atoi(command_readline_parsed[a + 2]) < 0) {
                                    printf("%s cant move. There is a wall.\n", hero[i].char_name);
                                } else if (MAP[atoi(command_readline_parsed[a + 1])][atoi(
                                        command_readline_parsed[a + 2])] != '.') {
                                    printf("%s can’t move. Place is occupied.\n", hero[i].char_name);
                                } else {
                                    MAP[hero[i].char_location_x][hero[i].char_location_y] = '.';
                                    hero[i].char_location_x = atoi(command_readline_parsed[a + 1]);
                                    hero[i].char_location_y = atoi(command_readline_parsed[a + 2]);
                                    MAP[atoi(command_readline_parsed[a + 1])][atoi(
                                            command_readline_parsed[a + 2])] = hero[i].char_name[0];
                                }
                            }
                        }
                    }
                    x++;
                    i = 0;
                }
            }

        }//END OF MOVE
        int result = 0;
        for (int m = 0; m < hero_size; ++m) {
            result += (hero[m].char_life == 1);
            if (result == 0) {
                printf("HEROES WON\n");
                return 0;
            }
        }
        for (int n = 0; n < monster_size; ++n) {
            result += ((hero[n].char_life == 1));
            if(result == 0) {
                printf("MONSTERS WON \n");
                return 0;
            }
        }
    } // loop of commands
}


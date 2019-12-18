
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Map uzerinde gosterim
 *22:11
 *
 *
 * */
struct type{
    char char_name[25];
    int char_HP,char_DP,char_XP,char_location_x,char_location_y,char_life;
};
int main (int argc, char **argv) {
    /*CHAR READ PARSE LOAD */
    /* DECLARATIONS */
    struct type *hero =  malloc(sizeof(struct type)*2);
    /* initialize to standard values for error-preventation */
    int m1 = 0;
    for (m1 = 0; m1 < 2; ++m1) {
        hero[m1].char_XP = 0;
        hero[m1].char_DP = 0;
        hero[m1].char_HP = 0;
        hero[m1].char_life = 1;
        hero[m1].char_location_x = 0;
        hero[m1].char_location_y = 0;
    }

    struct type *monster =  malloc(sizeof(struct type)*2);
    /* initialize to standard values for error-preventation */
    int m = 0;
    for (m = 0; m < 2; ++m) {
        monster[m].char_XP = 0;
        monster[m].char_DP = 0;
        monster[m].char_HP = 0;
        monster[m].char_life = 1;
        monster[m].char_location_x = 0;
        monster[m].char_location_y = 0;
    }

    FILE *fptr; /*chars file pointer*/
    FILE *wptr;/*output file pointer*/
    FILE *coptr;/*commands file pointer*/
    char *char_readline = NULL; /*that includes a line of the chars file like "HERO,DRIZZ,4,3"*/
    char *command_readline = NULL; /*that includes a line of the commands file like "lOADMAP 5 5"*/
    char char_readline_split[4][25]; /*that includes char_readlines splitted version like {"HERO","DRIZZ","4","4"}*/
    char command_readline_split[25][25] = {0}; /*that includes command_readlines splitted version like {"LOADMAP","5","5"}*/
    int monster_count = 0, hero_count = 0;
    size_t chars_len = 0;
    size_t command_len = 0;
    size_t char_readline_length;
    size_t command_readline_lenght;
    int load_row = 0, load_col = 0;
 char **MAP;


    /*<<---------- */

    /* FILE READ INTO CHARS_READLINE*/
    if ((wptr = fopen(argv[3], "w")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    if ((fptr = fopen(argv[1], "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    while ((char_readline_length = getline(&char_readline, &chars_len, fptr)) != -1) { /*That reads line by line from chars file and stops when it has reached end of file*/
        /* */
        /* Parse into char_readline_split */
        char *token = NULL;
        int n_tokens = 0, i = 0;

        token = strtok(char_readline, ",");
        while (token != NULL) {  /*splitting block*/
            strcpy(char_readline_split[i], token);
            token = strtok(NULL, ",");
            n_tokens++;
            i++;
        }
        /* ASSIGN TO STRUCT*/

     /* ASSIGN TO STRUCT*/

        if (strcmp(char_readline_split[0], "HERO") == 0) {

            strcpy(hero[hero_count].char_name, char_readline_split[1]);
            hero[hero_count].char_HP = atoi(char_readline_split[2]);
            hero[hero_count].char_DP = atoi(char_readline_split[3]);
            hero_count++;
            struct type *hero =  realloc(hero,sizeof(struct type)*(5+ hero_count));


        }
        if (strcmp(char_readline_split[0], "MONSTER") == 0) {
            strcpy(monster[monster_count].char_name, char_readline_split[1]);
            monster[monster_count].char_HP = atoi(char_readline_split[2]);
            monster[monster_count].char_DP = atoi(char_readline_split[3]);
            monster_count++;
            struct type *monster =  realloc(monster,sizeof(struct type)*(monster_count + 5));

        }
        /**/
    }    /*CHAR READ PARSE LOAD HAS DONE */
    /*Commands CRPL */
    fclose(fptr);
    if ((coptr = fopen(argv[2], "r")) == NULL) {
        fprintf(wptr, "%s", "Error! opening file");
        printf("Error! opening file");
        exit(1);
    }
    while ((char_readline_length = getline(&command_readline, &command_len, coptr)) != -1) { /*that reads line by line from commands file and stop when EOF*/
        fprintf(wptr, "%s", "\n");
        printf("\n");
        /* */
        /* Parse into char_readline_split */
        char *token = NULL;
        int n_tokens = 0, i = 0;
        token = strtok(command_readline, " ");
        while (token != NULL) {
            strcpy(command_readline_split[i], token);
            token = strtok(NULL, " ");
            n_tokens++;
            i++;

        }
        /* in that scope we can use the array which includes the command variables*/
        if (strcmp(command_readline_split[0], "LOADMAP") == 0) {

            load_row = atoi(command_readline_split[1]);
            load_col = atoi(command_readline_split[2]);
            MAP = malloc(sizeof(char *) * load_row);
            for (int i1 = 0; i1 < load_row; ++i1) {
                MAP[i1] = malloc(sizeof(char) * load_col);
            }
            int l;
            int i;
            for (l = 0; l < load_row; ++l) { /*set map to "."*/
                for (i = 0; i < load_col; ++i) {
                    MAP[l][i] = '.';
                }
            }
        }
        /* START OF PUT */
        if (strcmp(command_readline_split[0], "PUT") == 0) {
            int hero_put = 0, monster_put = 0, x = 0;
            if (strcmp(command_readline_split[1], "HERO") == 0) {
                x = 0;
                int i;
                while (x < hero_count) {
                    for (i = 0; i < hero_count; ++i) {
                        if (command_readline_split[2 + 3 * x] != 0) {
                            int a = 2 + 3 * x;
                            if (strcmp(command_readline_split[a], hero[i].char_name) == 0) {
                                hero[i].char_location_x = atoi(command_readline_split[a + 1]);
                                hero[i].char_location_y = atoi(command_readline_split[a + 2]);
                                MAP[atoi(command_readline_split[a + 1])][atoi(
                                        command_readline_split[a + 2])] = hero[i].char_name[0];
                            }
                        }
                    }
                    x++;
                    i = 0;
                }
            } /*if hero end bracket*/

            if (strcmp(command_readline_split[1], "MONSTER") == 0) {
                x = 0;
                while (x < monster_count) {
                    int i;
                    for (i = 0; i < monster_count; ++i) {
                        int a = 2 + 3 * x;
                        if (strcmp(command_readline_split[a], monster[i].char_name) == 0) {
                            monster[i].char_location_x = atoi(command_readline_split[a + 1]);
                            monster[i].char_location_y = atoi(command_readline_split[a + 2]);
                            MAP[atoi(command_readline_split[a + 1])][atoi(
                                    command_readline_split[a + 2])] = monster[i].char_name[0];
                        }
                    }
                    x++;
                    i = 0;
                }
            } /*if monster end bracket*/
        } /* END OF PUT */
        if (strcmp(command_readline_split[0], "SHOW") == 0) {
            if (strcmp(command_readline_split[1], "MAP\n") == 0) {
                fprintf(wptr, "%s", "MAP STATUS\n");
                printf("MAP STATUS\n");
                int j;
                int k;
                for (j = 0; j < load_row; ++j) {
                    for (k = 0; k < load_col; ++k) {
                        fprintf(wptr, "%c", MAP[j][k]); /*prints map*/
                        printf("%c ", MAP[j][k]);
                    }
                    fprintf(wptr, "%s", "\n");
                    printf("\n");
                }
            }
            if (strcmp(command_readline_split[1], "HERO\n") == 0) {
                fprintf(wptr, "%s", "HERO STATUS\n");
                printf("HERO STATUS\n");
                int j;
                for (j = 0; j < hero_count; ++j) {
                    fprintf(wptr, "%s HP:%d XP: %d\n", hero[j].char_name, hero[j].char_HP, hero[j].char_XP); /*prints status*/
                    printf("%s HP:%d XP: %d\n", hero[j].char_name, hero[j].char_HP, hero[j].char_XP);
                }
            }
            if (strcmp(command_readline_split[1], "MONSTER\n") == 0) {
                fprintf(wptr, "%s", "MONSTER STATUS\n");
                printf("MONSTER STATUS\n");
                int j;
                for (j = 0; j < monster_count; ++j) {
                    fprintf(wptr, "%s HP:%d\n", monster[j].char_name, monster[j].char_HP);
                    printf("%s HP:%d\n", monster[j].char_name, monster[j].char_HP); /*prints status*/
                }
            }
        }

        if (strcmp(command_readline_split[0], "ATTACK") == 0) {
            if (strcmp(command_readline_split[1], "HERO\n") == 0) {
                fprintf(wptr, "%s", "HERO S ATTACKED\n");
                printf("HERO S ATTACKED\n");
                int j;
                int k;
                for (j = 0; j < hero_count; ++j) { /*for each hero*/
                    if (hero[j].char_life == 1) { /*if hero is dead it cannot attack .*/
                        for (k = 0; k < monster_count; ++k) { /*to each monster*/
                            if (monster[k].char_location_x == hero[j].char_location_x - 1 &&
                                monster[k].char_location_y == hero[j].char_location_y) { /*if it is adjanet or not*/
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                     /*i added that condition for know if it cant kill  at one shot just decrease the hp*/
                                else {  /*but if it can kill it with one shot*/
                                    if (monster[k].char_HP > 0) {  /*if it hasnt killen already*/
                                        MAP[monster[k].char_location_x][monster[k].char_location_y] = '.'; /*set maps location as empty, as "."*/
                                        hero[j].char_XP++; /*and increase heroes XP*/
                                    }
                                    monster[k].char_HP = 0;  /*set its HP to 0*/
                                    monster[k].char_life = 0;/*set its life to 0(dead)*/
                                /*The remaining 7 blocks alghorithm is the same of it. At each step it check other seven direction. */
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x - 1 &&
                                monster[k].char_location_y == hero[j].char_location_y + 1) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    if (monster[k].char_HP > 0) {
                                        MAP[monster[k].char_location_x][monster[k].char_location_y] = '.';
                                        hero[j].char_XP++;
                                    }
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x &&
                                monster[k].char_location_y == hero[j].char_location_y + 1) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    if (monster[k].char_HP > 0) {
                                        MAP[monster[k].char_location_x][monster[k].char_location_y] = '.';
                                        hero[j].char_XP++;
                                    }
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x + 1 &&
                                monster[k].char_location_y == hero[j].char_location_y + 1) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    if (monster[k].char_HP > 0) {
                                        MAP[monster[k].char_location_x][monster[k].char_location_y] = '.';
                                        hero[j].char_XP++;
                                    }
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x + 1 &&
                                monster[k].char_location_y == hero[j].char_location_y) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    if (monster[k].char_HP > 0) {
                                        MAP[monster[k].char_location_x][monster[k].char_location_y] = '.';
                                        hero[j].char_XP++;
                                    }
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x + 1 &&
                                monster[k].char_location_y == hero[j].char_location_y - 1) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    if (monster[k].char_HP > 0) {
                                        MAP[monster[k].char_location_x][monster[k].char_location_y] = '.';
                                        hero[j].char_XP++;
                                    }
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x &&
                                monster[k].char_location_y == hero[j].char_location_y - 1) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    if (monster[k].char_HP > 0) {
                                        MAP[monster[k].char_location_x][monster[k].char_location_y] = '.';
                                        hero[j].char_XP++;
                                    }
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                }
                            }
                            if (monster[k].char_location_x == hero[j].char_location_x - 1 &&
                                monster[k].char_location_y == hero[j].char_location_y - 1) {
                                if (monster[k].char_HP > hero[j].char_DP) { monster[k].char_HP -= hero[j].char_DP; }
                                else {
                                    if (monster[k].char_HP > 0) {
                                        MAP[monster[k].char_location_x][monster[k].char_location_y] = '.';
                                        hero[j].char_XP++;
                                    }
                                    monster[k].char_HP = 0;
                                    monster[k].char_life = 0;
                                }
                            }
                        }/*for each monster*/
                    } /*check if it is alive*/
                } /*end of hero count*/
            } /*end of heroes attack */
            if (strcmp(command_readline_split[1], "MONSTER\n") == 0) {
                fprintf(wptr, "%s", "MONSTER S ATTACKED\n");
                printf("MONSTER S ATTACKED\n");
                int j;
                int k;
                /*IT IS COMPLETELY THE SAME OF HEROES ATTACK ALGHORITM . BUT THERE ISNT ANY XP VALUE*/
                for (j = 0; j < monster_count; ++j) {
                    if (monster[j].char_life == 1) {
                        for (k = 0; k < hero_count; ++k) {
                            if (hero[k].char_location_x == monster[j].char_location_x - 1 &&
                                hero[k].char_location_y == monster[j].char_location_y) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    if (hero[k].char_HP >
                                        0) { MAP[hero[k].char_location_x][hero[k].char_location_y] = '.'; }

                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x - 1 &&
                                hero[k].char_location_y == monster[j].char_location_y + 1) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    if (hero[k].char_HP >
                                        0) { MAP[hero[k].char_location_x][hero[k].char_location_y] = '.'; }

                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x &&
                                hero[k].char_location_y == monster[j].char_location_y + 1) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    if (hero[k].char_HP >
                                        0) { MAP[hero[k].char_location_x][hero[k].char_location_y] = '.'; }

                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x + 1 &&
                                hero[k].char_location_y == monster[j].char_location_y + 1) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    if (hero[k].char_HP >
                                        0) { MAP[hero[k].char_location_x][hero[k].char_location_y] = '.'; }

                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x + 1 &&
                                hero[k].char_location_y == monster[j].char_location_y) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    if (hero[k].char_HP >
                                        0) { MAP[hero[k].char_location_x][hero[k].char_location_y] = '.'; }

                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x + 1 &&
                                hero[k].char_location_y == monster[j].char_location_y - 1) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    if (hero[k].char_HP >
                                        0) { MAP[hero[k].char_location_x][hero[k].char_location_y] = '.'; }

                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x &&
                                hero[k].char_location_y == monster[j].char_location_y - 1) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    if (hero[k].char_HP >
                                        0) { MAP[hero[k].char_location_x][hero[k].char_location_y] = '.'; }

                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;
                                }
                            }
                            if (hero[k].char_location_x == monster[j].char_location_x - 1 &&
                                hero[k].char_location_y == monster[j].char_location_y - 1) {
                                if (hero[k].char_HP > monster[j].char_DP) { hero[k].char_HP -= monster[j].char_DP; }
                                else {
                                    if (hero[k].char_HP >
                                        0) { MAP[hero[k].char_location_x][hero[k].char_location_y] = '.'; }
                                    hero[k].char_HP = 0;
                                    hero[k].char_life = 0;

                                }
                            }
                        } /*end of heroes count*/
                    }
                } /*End of Monsters count*/
            }/*End of monsters attack block */
        } /*end of attack block*/
        /* BASLANGIC OF MOVE */
        if (strcmp(command_readline_split[0], "MOVE") == 0) {
            int hero_put = 0, monster_put = 0, x = 0;
            if (strcmp(command_readline_split[1], "HERO") == 0) {
                fprintf(wptr, "%s", "HERO S MOVED\n");
                printf("HERO S MOVED\n");
                x = 0;

                while (x < hero_count) { /*for each hero*/
                    int z;
                    for (z = 0; z < hero_count; ++z) {
                        if (command_readline_split[2 + 3 * x] != 0) {
                            int a = 2 + 3 * x;

                            if (strcmp(command_readline_split[a], hero[z].char_name) == 0) {
                                if (hero[z].char_life == 0) {
                                    fprintf(wptr, "%s can t move. Dead.\n", hero[z].char_name);
                                    printf("%s can t move. Dead.\n", hero[z].char_name);
                                } else if (atoi(command_readline_split[a + 1]) > load_row - 1 ||
                                           atoi(command_readline_split[a + 1]) < 0 ||
                                           atoi(command_readline_split[a + 2]) > load_col - 1 ||
                                           atoi(command_readline_split[a + 2]) < 0) {
                                    printf("%s cant move. There is a wall.\n", hero[z].char_name);
                                    fprintf(wptr, "%s cant move. There is a wall.\n", hero[z].char_name);
                                } else if (MAP[atoi(command_readline_split[a + 1])][atoi(
                                        command_readline_split[a + 2])] != '.') {
                                    fprintf(wptr, "%s can’t move. Place is occupied.\n", hero[z].char_name);
                                    printf("%s can’t move. Place is occupied.\n", hero[z].char_name);
                                } else {
                                    MAP[hero[z].char_location_x][hero[z].char_location_y] = '.';
                                    hero[z].char_location_x = atoi(command_readline_split[a + 1]);
                                    hero[z].char_location_y = atoi(command_readline_split[a + 2]);
                                    MAP[atoi(command_readline_split[a + 1])][atoi(
                                            command_readline_split[a + 2])] = hero[z].char_name[0];
                                }
                            }
                        }
                    }
                    x++;
                }
            }

        }/*END OF MOVE*/
        int result = 0;
        int m;
        for (m = 0; m < hero_count; ++m) { /*if one of the heroes is alive the result must be different from zero*/
            result += (hero[m].char_life == 1);
        }
        if (result == 0) {
            fprintf(wptr, "%s", "HEROES WON\n");
            printf("HEROES WON\n");
            return 0;
        }
        result = 0;
        int n;
        for (n = 0; n < monster_count; ++n) {
            result += ((hero[n].char_life == 1));
        }
        if (result == 0) {
            fprintf(wptr, "%s", "MONSTERS WON \n");
            printf("MONSTERS WON \n");
            return 0;
        }

    }
    fclose(wptr); /*close output file*/
    fclose(coptr); /*close command file*/
    /* loop of commands */
    return 0;
}

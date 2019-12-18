#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ()
{
    //CHAR READ PARSE LOAD
    /* DECLARATIONS */
    FILE *fptr;
    char * char_readline = NULL;
    char char_readline_parsed[4][25];
    size_t len = 0;
    ssize_t char_readline_length;
    /* */
    /* FILE READ INTO CHARS_READLINE*/
    if ((fptr = fopen("chars_1.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    char_readline_length = getline(&char_readline, &len, fptr);
    printf("%s",char_readline);
    /* */
    /* Parse into char_readline_parsed */
    char *token = NULL;
    int n_tokens = 0,i=0;
    printf ("Get tokens from string \"%s\"\n",char_readline);
    printf("%s\n", "*********************************************");
   token = strtok (char_readline,",");
   while (token != NULL)
   {
       strcpy(char_readline_parsed[i],token);
       token = strtok (NULL, ",");
       n_tokens++;
       i++;
   }
        /* */
    //________________________________________

    printf("%s\n",char_readline_parsed[0]);
    printf("%s\n",char_readline_parsed[1]);
    printf("%s\n",char_readline_parsed[2]);

    printf("%s\n",char_readline_parsed[3]);

  return 0;
}
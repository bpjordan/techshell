
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 256

void prompt();
char** tokenize(char *);

int main(int argc, char **argv)
{
    prompt();
    char input[MAX_INPUT];
    fgets(input, MAX_INPUT, stdin);
    char** command = tokenize(input);

#ifdef DEBUG
    printf("Attempting to run [");
    for(int i=0; command[i] != NULL; i++)
        printf("\"%s\",", command[i]);
    printf("]\n");
#endif


}

void prompt() 
{
    printf("waa>");
}

char** tokenize(char * str)
{
    //Returns a null-terminated list of strings tokenized from the input

    //Initialize the list of tokens to be empty (ending with a null)
    int currTok = 0, depth = 0;
    char** tokens = (char**) malloc(sizeof(char*) * currTok+1);
    tokens[0] = NULL;

    char* token = strtok(str, " \n");

    while(token != NULL)
    {
        //put this token into the list and add a new token
        tokens[currTok] = token;
        depth += strlen(token) + 1;

#ifdef DEBUG
        printf("tokenizer found \"%s\"\n", tokens[currTok]);
#endif
        realloc(tokens, sizeof(char*) * ++currTok + 1);
        tokens[currTok] = NULL;

        //Get the next word or complete string from input
        if(str[depth] == '"')
            token = strtok(NULL, "\"\n");
        else
            token = strtok(NULL, " \n");

    }

    free(token);

    return tokens;
}

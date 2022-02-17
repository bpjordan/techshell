
#include "tokenizer.h"

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

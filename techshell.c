#include "techshell.h"

int main(int argc, char **argv)
{
    while(1)
    {
        prompt();
        char input[MAX_INPUT];
        fgets(input, MAX_INPUT, stdin);
        char** command = tokenize(input);

#ifdef DEBUG
        printf("Tokens: [");
        for(int i=0; command[i] != NULL; i++)
            printf("\"%s\",", command[i]);
        printf("]\n");
#endif

        command = parseRedirection(command);

        if(command == NULL)
            continue;

#ifdef DEBUG
        printf("Arguments: [");
        for(int i=0; command[i] != NULL; i++)
            printf("\"%s\",", command[i]);
        printf("]\n");
#endif

    }
}

void prompt()
{
    printf("waa> ");
}


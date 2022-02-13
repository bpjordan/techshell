#include "techshell.h"

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


#include "techshell.h"

int main(int argc, char **argv)
{

    int exitstatus = 0;
    while(1)
    {
        char* pwd = getenv("PWD");
        printf("%s $ ", pwd);

/* Get user input and tokeize it */

        char input[MAX_INPUT];
        fgets(input, MAX_INPUT, stdin);
        char** command = tokenize(input);

        if(*command == NULL)
            continue;

        if(!strcmp(command[0], "exit"))
            exit(exitstatus);

/* Parse out redirection commands */

#ifdef DEBUG
        printf("Tokens: [");
        for(int i=0; command[i] != NULL; i++)
            printf("\"%s\",", command[i]);
        printf("]\n");
#endif

        int* streams = parseRedirection(command);

        if(streams == NULL)
            continue;

/* Do the thing */

#ifdef DEBUG
        printf("Arguments: [");
        for(int i=0; command[i] != NULL; i++)
            printf("\"%s\",", command[i]);
        printf("]\n");
#endif

        pid_t childpid = fork();

        if(!childpid)   //Child
        {
            for(int i = 0; i<3; i++)
            {
                if(streams[i])
                    dup2(streams[i], i);

                execvp(command[0], command);
            }
        }
        else            //Parent
        {
            int status = 0;
            waitpid(childpid, &status, NULL);

            exitstatus = WEXITSTATUS(status);
        }


    }
}

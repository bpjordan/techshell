#include "techshell.h"

int main(int argc, char **argv)
{

    int exitstatus = 0;

    char* pwd = malloc(sizeof(char*) * CWD_BUFF);
    while(1)
    {

        if(getcwd(pwd, CWD_BUFF) == NULL)
        {
            perror("FATAL: Failed to get cwd");
            exit(1);
        }

        printf("%s $ ", pwd);

/* Get user input and tokeize it */

        char input[MAX_INPUT];
        fgets(input, MAX_INPUT, stdin);
        char** command = tokenize(input);

        if(*command == NULL)
            continue;

        if(!strcmp(command[0], "exit") || feof(stdin))
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

        if(!strcmp(command[0], "cd"))
        {
            char* dir = (command[1] == NULL) ? getenv("HOME") : command[1];
#ifdef DEBUG
            printf("Chdir to %s\n", dir);
#endif
            if(chdir(dir) == -1)
                fprintf(stderr, "Couldn't chdir to %s: %s\n", dir, strerror(errno));

            continue;
        }
        else if (!strcmp(command[0], "pwd"))
        {
            printf("%s\n", pwd);
            continue;
        }

        pid_t childpid = fork();

        if(!childpid)   //Child
        {
            for(int i = 0; i<3; i++)
            {
                if(streams[i])
                    dup2(streams[i], i);
            }

            if(execvp(command[0], command) == -1)
                fprintf(stderr, "Unable to execute %s: %s\n", command[0], strerror(errno));
            exit(1);
        }
        else            //Parent
        {
            int status = 0;
            waitpid(childpid, &status, 0);

            exitstatus = WEXITSTATUS(status);

            for(int i = 0; i<3; i++)
                if(streams[i]) close(streams[i]);

            free(streams);

//            for(int i = 0; command[i] != NULL; i++)
//                free(command[i]);

            free(command);
        }


    }
}

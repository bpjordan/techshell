#include "techshell.h"

int main(int argc, char **argv)
{

    int exitstatus = 0;

    char* pwd = malloc(sizeof(char*) * CWD_BUFF);
    while(!feof(stdin))
    {

        if(getcwd(pwd, CWD_BUFF) == NULL)
        {
            perror("FATAL: Failed to get cwd");
            exit(1);
        }

        printf("%s $ ", pwd);

/* Get user input and tokeize it */

        char input[MAX_INPUT];
        errno = 0;
        if(fgets(input, MAX_INPUT, stdin) == NULL)
        {
            if(errno == 0) exit(exitstatus);
            perror("Failed to read user input");
            continue;
        }
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

#ifdef DEBUG
        printf("Arguments: [");
        for(int i=0; command[i] != NULL; i++)
            printf("\"%s\",", command[i]);
        printf("]\n");
#endif

/* Do the thing */

        pid_t childpid;

        //Before forking, check if we're running one of the builtins
        if(!strcmp(command[0], "cd"))
        {
            char* dir = (command[1] == NULL) ? getenv("HOME") : command[1];         //Default to home if no dir is given
            exitstatus = cd(dir, streams);
        }

        else if (!strcmp(command[0], "pwd"))
        {
            exitstatus = putpwd(pwd, streams);
        }

        else if(!(childpid = fork()))   //Child
        {
#ifdef DEBUG
            printf("Child process succesfully created with PID %d\n", getpid());
#endif

            //Redirect to/from any files found in redirection step
            for(int i = 0; i<3; i++)
            {
                if(streams[i])
                    dup2(streams[i], i);
            }

            if(execvp(command[0], command) == -1)
                fprintf(stderr, "Unable to execute %s: %s\n", command[0], strerror(errno));
            exit(1);
        }
        else if(childpid == -1)
            perror("Failed to create child process");
        else            //Parent
        {
            int status = 0;
            waitpid(childpid, &status, 0);

            exitstatus = WEXITSTATUS(status);

#ifdef DEBUG
            printf("Child process exited with status %d\n", exitstatus);
#endif

        }

        cleanupRedirection(streams);

        free(command);
    }
}

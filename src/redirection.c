#include "redirection.h"

//Private functions which are
//internal to parseRedirection
int redirectIn(char *, int *);
int redirectOut(char *, int *);
int redirectErr(char *, int *);

int *parseRedirection(char ** command)
{
/* Detects and handles redirection and then passes back list of arguments with
 * redirection commands removed. Returns NULL if redirection was attempted and failed.
 */

    int *fds = calloc(3,sizeof(int));

    int curr = 0, status = 0;

    for(char **p = command; *p != NULL; p++)
    {
        if(strcmp(*p, ">") == 0)
            status = redirectOut(*(++p), fds);
        else if (strcmp(*p, "<") == 0)
            status = redirectIn(*(++p), fds);
        else if(strcmp(*p, "2>") == 0)
            status = redirectErr(*(++p), fds);
        else
        {
            command[curr++] = *p;
            continue;
        }

        if(status != 0)
        {
            fprintf(stderr, "Couldn't redirect to/from %s: %s\n", *p, strerror(status));
            return NULL;
        }
    }

    command[curr] = NULL;

    return fds;

}

int redirectIn(char *filename, int *fdlist)
{
    FILE * redirectFile = fopen(filename, "r");

    if(redirectFile == NULL)
        return errno;

#ifdef DEBUG
    printf("redirecting stdin to %s\n", filename);
#endif
    fdlist[0] = fileno(redirectFile);

    return 0;
}

int redirectOut(char *filename, int *fdlist)
{
    FILE * redirectFile = fopen(filename, "w");

    if(redirectFile == NULL)
        return errno;

#ifdef DEBUG
    printf("redirecting stdout to %s\n", filename);
#endif
    fdlist[1] = fileno(redirectFile);

    return 0;
}

int redirectErr(char *filename, int *fdlist)
{
    FILE * redirectFile = fopen(filename, "w");

    if(redirectFile == NULL)
        return errno;

#ifdef DEBUG
    printf("redirecting stderr to %s\n", filename);
#endif
    fdlist[2] = fileno(redirectFile);

    return 0;
}

void cleanupRedirection(int* filenos)
{
    for(int i = 0; i<3; i++)
        if(filenos[i]) close(filenos[i]);

    free(filenos);
}

#include "redirection.h"

//Private functions which are
//internal to parseRedirection
int redirectIn(char *);
int redirectOut(char *);
int redirectErr(char *);

char **parseRedirection(char ** command)
{
/* Detects and handles redirection and then passes back list of arguments with
 * redirection commands removed. Returns NULL if redirection was attempted and failed.
 */

    int curr = 0, status = 0;
    char ** notRedirects = malloc(sizeof(char **) * curr + 1);

    for(char **p = command; *p != NULL; p++)
    {
        if(strcmp(*p, ">") == 0)
            status = redirectOut(*(++p));
        else if (strcmp(*p, "<") == 0)
            status = redirectIn(*(++p));
        else if(strcmp(*p, "2>") == 0)
            status = redirectErr(*(++p));
        else
        {
            notRedirects[curr++] = *p;
            realloc(notRedirects, sizeof(char **) * curr + 1);
            continue;
        }

        if(status != 0)
        {
            fprintf(stderr, "Couldn't redirect to/from %s: %s\n", *p, strerror(status));
            return NULL;
        }
    }

    notRedirects[curr] = NULL;

    return notRedirects;

}

int redirectIn(char *filename)
{
    FILE * redirectFile = fopen(filename, "r");

    if(redirectFile == NULL)
        return errno;

#ifdef DEBUG
    printf("redirecting stdin to %s\n", filename);
#else
    dup2(fileno(redirectFile), 0);
#endif

    return 0;
}

int redirectOut(char *filename)
{
    FILE * redirectFile = fopen(filename, "w");

    if(redirectFile == NULL)
        return errno;

#ifdef DEBUG
    printf("redirecting stdout to %s\n", filename);
#else
    dup2(fileno(redirectFile), 1);
#endif

    return 0;
}

int redirectErr(char *filename)
{
    FILE * redirectFile = fopen(filename, "w");

    if(redirectFile == NULL)
        return errno;

#ifdef DEBUG
    printf("redirecting stderr to %s\n", filename);
#else
    dup2(fileno(redirectFile), 2);
#endif

    return 0;
}

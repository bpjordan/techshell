#include "builtins.h"

int cd(char * dir, int * iostreams)
{
#ifdef DEBUG
    printf("Attempting chdir to %s\n", dir);
#endif

    if(chdir(dir) == -1)
    {
        dprintf(iostreams[2] == 0 ? fileno(stderr) : iostreams[2],
                "Couldn't chdir to %s: %s\n", dir, strerror(errno));
        return 1;
    }
    else
        return 0;
}

int putpwd(char *pwd, int * iostreams)
{
    dprintf(iostreams[1] == 0 ? fileno(stdout) : iostreams[1], "%s\n", pwd);
    return 0;
}

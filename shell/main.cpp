#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int lsh_cd(char** args);
int lsh_help(char** args);
int lsh_exit(char** args);

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char**) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int lsh_num_builtins() 
{
    return sizeof(builtin_str) / sizeof(char*);
}

int lsh_cd(char ** args)
{
    if(args[1] == NULL)
    {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");)
    }
    else
    {
        if(chdir(args[1]) != 0)
        {
            perror("lsh");
        }
    }

    return 1;
}
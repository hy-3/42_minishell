#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <limits.h>

// gcc test.c -lreadline -o test2
//  FUNCION VALIDA
//extern void add_history PARAMS((const char *));

// FUNCIONES NO VALIDAS ?¿
//extern int write_history PARAMS((const char *));
//extern int read_history PARAMS((const char *));
//_______________________________

// COLORS https://misc.flogisoft.com/bash/tip_colors_and_formatting
#define CLOSE "\001\033[0m\002"
#define BLOD "\001\033[1m\002"
#define BEGIN(x) "\001\033[38;5;" #x "m\002"
// INTERESANTE
//------

// https://www.delftstack.com/es/howto/c/sigint-in-c/

//------

//**env, enverioment test
// int main(int argc, char **argv, char **envp)
// {
//     while(*envp)
//         printf("%s\n",*envp++);
// }

char *promt()
{
    char *buf;
    char str_path[PATH_MAX + 1];
    char *str[2];
    int i;
    //getcwd(str_path, PATH_MAX);
    str[0] = BEGIN(107)"Mini🐒Shell💮\n"CLOSE;
    str[1] = BEGIN(30) BLOD "$ " CLOSE;
    buf = calloc(strlen(str[0]) + 1 + strlen(str[1]) + 1, sizeof(char));
    i = 0;
    while (i < 2)
        strcat(buf, str[i++]);
    return (buf);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    int exit;
    char *str;

    char buf[PATH_MAX + 1];

    exit = 0;
    read_history(".ms_hst");
    while (!exit)
    {
        str = readline(promt());
        // printf("minishell: %s: command not found\n",str);
        add_history(str);
        write_history(".ms_hst");
        free(str);
        // chdir("");
    }
}


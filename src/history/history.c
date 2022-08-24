#include "../minishell.h"

void ft_add_history(char *str)
{
    int file;

    file = open(".ms_hst", O_CREAT | O_RDWR | O_APPEND, 0777);
    if (file == -1)
        return;
    add_history(str);
    ft_putstr_fd(str, file);
    ft_putstr_fd("\n", file);
    close(file);
}

void ft_get_history(void)
{
    int file;
    int len;
    char *str;
    char *ax;

    file = open(".ms_hst", O_CREAT | O_RDWR, 0777);
    if (file == -1)
        return;
    str = get_next_line(file);
    while (str)
    {
        str[ft_strlen(str) - 1] = '\0';
        add_history(str);
        free(str);
        str = get_next_line(file);
    }
    close(file);
}
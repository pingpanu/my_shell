#include "myshell.h"

int main(void)
{
    char    *cmd_str;
    char    *dis_str;
    t_list  *cmd_list;

    g_envpath = getenv("PATH");
    dis_str = ft_strjoin(getenv("USER"), ": ");
    //printf("%s\n", dis_str);
    //printf("%s\n", g_envpath);
    while (1) {
        cmd_str = readline(dis_str);
        //cmd_list = lexer(cmd_str);
        /*
        if (cmd_str != NULL)
            free(cmd_str);
        if (arr_cmd != NULL)
            free_char_arr(arr_cmd);
            */
    }
    return (0);
}
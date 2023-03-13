#ifndef MYSHELL_H
# define MYSHELL_H
# define _XOPEN_SOURCE 700
# include "libft.h" //already have unistd.h and stdlib.h
# include <stdio.h> //printf
# include <readline/readline.h> //readline, rl_*, and add_history
# include <readline/history.h> //readline, rl_*, and add_history
# include <fcntl.h> //open, unlink, dup, dup2, 
# include <sys/types.h> //fork
# include <sys/wait.h> //wait, waitpid, wait3, wait4
# include <sys/stat.h> //stat, lstat, and fstat
# include <sys/ioctl.h> //ioctl
# include <signal.h> //signal, sigaction, sigemptyset, sigaddset, and kill
# include <dirent.h> //opendir, readdir, and closedir
# include <errno.h> //stderror, and perror
# include <termio.h> //support ioctl
# include <termios.h> //tc*

/*This is struct to store the computer systems*/
typedef struct s_system 
{
    char    **env_path; //path variable array
    char    *dis_str; //User displayed at readline function
}   t_system;

/*This is struct to get parameter for cmd_ll*/
typedef struct s_cmd_param
{
    int     is_pipe; //check if there is '|'
    int     is_amp; //check if there is '&'
    int     is_gg; //check if there is '>>'
    int     is_ga; //check if there is '>&'
}   t_cmd_param;

void    lexer(t_list **cmd_ll, char* str);
char    **parser(t_list *cmd_ll);
int     executor(t_system my_env, char **cmd);
#endif
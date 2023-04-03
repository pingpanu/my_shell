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
# include <termio.h>
# include <termios.h> //tc*
# define BASH_IN 0
# define BASH_OPT 1
# define BASH_OUT 2

/*This is struct to store the computer systems*/
typedef struct s_system 
{
    char    **env_cop; //copy to store env for execution
    char    **env_path; //path variable array
    char    dis_str[500]; //User displayed at readline function
    struct  sigaction   act;
    struct  sigaction   quit;
    struct  termios     *sh_terminal;
    struct  termios     *myshell_term;
}   t_system;

/*This is command node to store all cmds*/
typedef struct s_cmd_node
{
    char    **cmd_arr;
    struct s_cmd_node   *next;
}   t_cmd_node;

/*This is struct to get parameter for cmd_ll*/
typedef struct s_cmd_table
{
    t_cmd_node  *cmds;
    char        *infile;
    char        *outfile;
    char        *hdoc_delim;  
}   t_cmd_table;

typedef struct s_executor
{
    int     in_fd;
    int     out_fd;
    int     node_ptr;
    pid_t   pid;
    int     nodesize;
    int     pipe_no;
    int     *pipe;
}   t_executor;

/*in myshell_main.c*/
void        sighandler(int signal);
/*in lexer.c*/
void        lexer(t_list **cmd_ll, char* str);
void        free_token(void *content);
/*in parser.c*/
t_cmd_table *parser(t_list *cmd_ll);
void        expander(t_cmd_table *cmdt);
/*for executor.c*/
int         executor(t_system my_env, t_cmd_table *cmd_table);
char        *find_path(char *cmd, char **env_path);
void        signal_operator(t_system *my_env, int status);
int         single_executor(t_system *env, t_cmd_table *cmdt, t_executor *exe);
int         pipe_executor(t_system *env, t_cmd_table *cmdt, t_executor *exe);
int         buildins(t_system *env, t_cmd_node *node, t_executor *exe);
int         exe_echo(t_executor *exe, t_cmd_node *node);
int         exe_env(t_system *env, t_cmd_node *node);
#endif

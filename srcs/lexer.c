/*Note: this is based on BoxofNote lexical analyzer
https://boxofnotes.com/lexical-analyzer-in-c-program-to-detect-tokens*/

#include "myshell.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//make token and send to linked list
static char    *newtoken(char *str)
{
    if (ft_strncmp(str, ">", 2) == 0)
        return (ft_strdup("GREAT"));
    else if (ft_strncmp(str, "<", 2) == 0)
        return (ft_strdup("LESS"));
    else if (ft_strncmp(str, ">>", 3) == 0)
        return (ft_strdup("GREATGREAT"));
    else if (ft_strncmp(str, ">&", 3) == 0)
        return (ft_strdup("GREATAMP"));
    else if (ft_strncmp(str, "<<", 3) == 0)
        return (ft_strdup("LESSLESS"));
    else if (ft_strncmp(str, "|", 2) == 0)
        return (ft_strdup("PIPE"));
    else if (ft_strncmp(str, "&", 2) == 0)
        return (ft_strdup("AMPERSAND"));
    else
        return (ft_strdup(str));
}

//Return true if its quote
bool    isQUOTE(char ch)
{
    if (ch == '"' || ch == 39)
        return (true);
    return (false);
}
// Extracts the SUBSTRING.
char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(
                sizeof(char) * (right - left+2));
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}
// Parsing the input STRING.
void    lexer(t_list **cmd_ll, char *str)
{
    int     left = 0, right = 0;
    int     len = strlen(str);
    char    *substr;

    while (right < len && left <= right)
    {
        if (isspace(str[right])) {
            right++;
            left = right;
        }
        else if (isQUOTE(str[right]) == true)
        {
            int quote = str[right];
            right++;
            while (str[right] != quote && right < len)
                right++;
            substr = subString(str, left, right);
            ft_lstadd_back(cmd_ll, ft_lstnew(newtoken(substr)));
            right++;
            left = right;
            free(substr);
        }
        else
        {
            right++;
            while (isspace(str[right]) == 0 && right < len)
                right++;
            {
                substr = subString(str, left, right - 1);
                ft_lstadd_back(cmd_ll, ft_lstnew(newtoken(substr)));
                left = right;
                free(substr);
            }
        }
    }
}
/*check function
void    print_arr(char **str)
{
    int     i = -1;

    while(str[++i])
        printf("%d = %s\n", i, str[i]);
}

void    check_table(t_cmd_table *table)
{
    t_cmd_node  *ptr;

    ptr = table->cmds;
    while(ptr)
    {
        print_arr(ptr->cmd_arr);
        ptr = ptr->next;
    }
    printf("infile = %s\n", table->infile);
    printf("outfile = %s\n", table->outfile);
}

DRIVER FUNCTION -> TO BE DELETED
int main()
{
    // maximum length of string is 100 here
    char str[100];
    t_list  *ll;
    t_cmd_table *cmd_table;

    ll = NULL;
    printf("Enter the String: \n");
    scanf("%[^\n]s", str);
    lexer(&ll, str);
    /*printf("Size of ll = %d\n", ft_lstsize(ll));
    int i = 1;
    while (ll != NULL)
    {
        printf("token number %d = %s\n", i, ll->token);
        i++;
        ll = ll->next;
    }
    cmd_table = parser(ll);
    check_table(cmd_table);
    return (0);
}*/
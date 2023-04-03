/*Note: this is based on BoxofNote lexical analyzer
https://boxofnotes.com/lexical-analyzer-in-c-program-to-detect-tokens*/

#include "myshell.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static char     *newtoken(char *str)
{
    if (ft_strncmp(str, ">", 2) == 0)
        return (ft_strdup("GREAT"));
    else if (ft_strncmp(str, "<", 2) == 0)
        return (ft_strdup("LESS"));
    else if (ft_strncmp(str, ">>", 3) == 0)
        return (ft_strdup("GREATGREAT"));
    else if (ft_strncmp(str, "<<", 3) == 0)
        return (ft_strdup("HDOC"));
    else if (ft_strncmp(str, "|", 2) == 0)
        return (ft_strdup("PIPE"));
    else
        return (str);
}

//Return true if its quote
bool    isQUOTE(char ch)
{
    if (ch == '"' || ch == 39)
        return (true);
    return (false);
}
//delete token
void    free_token(void *content)
{
    free(content);
}

// Parsing the input STRING.
void    lexer(t_list **cmd_ll, char *str)
{
    int     left = 0, right = 0;
    int     len = strlen(str);
    char    *substr;

    while (right < len && left <= right)
    {
        if (isspace(str[right]))
        {
            right++;
            left++;
        }
        else if (isQUOTE(str[right]) == true)
        {
            int quote = str[right];
            right++;
            while (str[right] != quote && right < len)
                right++;
            substr = ft_substr(str, left, (right - left + 1));
            ft_lstadd_back(cmd_ll, ft_lstnew(newtoken(substr)));
            right++;
            left++;
            free(substr);
        }
        else
        {
            right++;
            while (isspace(str[right]) == 0 && right < len)
                right++;
            substr = ft_substr(str, left, (right - left));
            ft_lstadd_back(cmd_ll, ft_lstnew(newtoken(substr)));
            left = right;
            free(substr);
        }
    }
}
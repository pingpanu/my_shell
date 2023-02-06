/*Note: this is based on BoxofNote lexical analyzer
https://boxofnotes.com/lexical-analyzer-in-c-program-to-detect-tokens*/

#include "myshell.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
t_list *parse(char* str)
{
    int     left = 0, right = 0;
    int     len = strlen(str);
    char    *substr;
    t_list *ret;

    while (right < len && left <= right)
    {
        //shift left and right if str[right] is space
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
            //printf("'%s'\n", substr);
            ft_lstadd_back(&ret, ft_lstnew(substr));
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
                //printf("'%s'\n", substr);
                ft_lstadd_back(&ret, ft_lstnew(substr));
                left = right;
                free(substr);
            }
        }
    }
    return (ret);
}
// DRIVER FUNCTION
int main()
{
    // maximum length of string is 100 here
    char str[100];
    t_list *ll;

    printf("Enter the String: \n");
    scanf("%[^\n]s", str);
    ll = parse(str);
    /*ll = ft_cmdll_new(str);
    printf("str cmd is %s\n", ll->cmd_str);
    printf("str token is %d\n", ll->token);*/
    printf("Size of ll = %d\n", ft_lstsize(ll));
    /*int i = 0;
    while (ll->next != NULL)
    {
        i++;
        printf("cmd %d = %s\n", i, ll->content);
        printf("cmd %d token = %d\n", i, ll->token);
        ll = ll->next;
    }*/
    return (0);
}
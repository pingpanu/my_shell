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
void    parse(t_list **cmd_ll, char* str)
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
            ft_lstadd_back(cmd_ll, ft_lstnew(substr));
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
                ft_lstadd_back(cmd_ll, ft_lstnew(substr));
                left = right;
                free(substr);
            }
        }
    }
}
// DRIVER FUNCTION -> TO BE DELETED 
int main()
{
    // maximum length of string is 100 here
    char str[100];
    t_list  *ll;

    ll = NULL;
    printf("Enter the String: \n");
    scanf("%[^\n]s", str);
    parse(&ll, str);
    printf("Size of ll = %d\n", ft_lstsize(ll));
    int i = 1;
    while (ll != NULL)
    {
        printf("token number %d = %s\n", i, ll->token);
        i++;
        ll = ll->next;
    }
    return (0);
}
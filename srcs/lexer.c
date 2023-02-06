/*Note: this is based on BoxofNote lexical analyzer
https://boxofnotes.com/lexical-analyzer-in-c-program-to-detect-tokens*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
void parse(char* str)
{
    int     left = 0, right = 0;
    int     len = strlen(str);
    char    *substr;

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
            while (str[right] != quote)
                right++;
            substr = subString(str, left, right);
            printf("'%s'\n", substr);
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
                printf("'%s'\n", substr);
                left = right;
                free(substr);
            }
        }
    }
    return;
}
// DRIVER FUNCTION
int main()
{
    // maximum length of string is 100 here
    char str[100];

    printf("Enter the String: \n");
    scanf("%[^\n]s", str);
    parse(str); // calling the parse function
    return (0);
}
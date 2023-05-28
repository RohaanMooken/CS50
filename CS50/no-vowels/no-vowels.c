// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void replace(string s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("[ERROR] Only one commandline argument is accepted.");
        return 1;
    }

    string s = argv[1];
    replace(s);
    return 0;
}

void replace(string s)
{
    int l = strlen(s);
    char replaced[l + 1];

    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == 'a')
        {
            replaced[i] = (char) '6';
        }
        else if (s[i] == 'e')
        {
            replaced[i] = (char) '3';
        }
        else if (s[i] == 'i')
        {
            replaced[i] = (char) '1';
        }
        else if (s[i] == 'o')
        {
            replaced[i] = (char) '0';
        }
        else
        {
            replaced[i] = s[i];
        }
    }

    replaced[l] = '\0';
    s = (string) replaced;
    printf("%s\n", s);
}
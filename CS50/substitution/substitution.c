#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    // Checks to see if there is a sufficient amount of arguments i.e the command: .\substituion.exe 'key'
    if (argc != 2)
    {
        printf("Insufficient amount or to many arguments given.\n");
        return 1;
    }

    // Checks to see if the 'key' contains 26 characters, the number of characters in the alphabet
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Checks to see if the 'key' contains a non alphabetical character and if there exists any duplicate characters in the key
    for (int i = 0; i < strlen(argv[1]) - 1; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Key contains a non alphabetical character.\n");
            return 1;
        }

        for (int j = i + 1; j < strlen(argv[1]); j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key includes duplicate characters.\n");
                return 1;
            }
        }
    }

    // defines the alphabet variable, gets th plaintext input from user and defines the string cipher with the same length as plain
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string plain = get_string("Plaintext : ");
    int l = strlen(plain);
    char cipher[l + 1];

    // Iterates over all the characters in the plain text
    for (int i = 0; i < strlen(plain); i++)
    {
        for (int j = 0; j < strlen(alphabet); j++)
        {
            // Checks to see if the character is lower case, if yes then put it through the key
            if (plain[i] == alphabet[j])
            {
                cipher[i] = tolower(argv[1][j]);
            }
            // Checks to see if the character is upper case, if yes then put it through the key
            else if (plain[i] == alphabet[j] - 32)
            {
                cipher[i] = toupper(argv[1][j]);
            }
            // Last three for loops uses the ASCII table to return the special symbols as is
            for (int k = 32; k < 65; k++)
            {
                if (plain[i] == k)
                {
                    cipher[i] = plain[i];
                }
            }
            for (int k = 91; k < 97; k++)
            {
                if (plain[i] == k)
                {
                    cipher[i] = plain[i];
                }
            }
            for (int k = 123; k < 127; k++)
            {
                if (plain[i] == k)
                {
                    cipher[i] = plain[i];
                }
            }
        }
    }

    // Adds the null character to the end of the array to make it a string
    cipher[l] = '\0';
    // prints the Ciphertext
    printf("ciphertext: %s\n", cipher);
    return 0;
}
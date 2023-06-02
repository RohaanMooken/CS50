// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool uppercase;
    bool lowercase;
    bool number;
    bool symbol;

    // iterate over all the characters in the string password
    for (int i = 0; i < strlen(password); i++)
    {
        // check wether character is alphabetical
        if (isalpha(password[i]) != 0)
        {
            // check wether character is uppercase else it is lowercase
            if (isupper(password[i]) != 0)
            {
                uppercase = true;
            }
            else
            {
                lowercase = true;
            }
        }
        // check wether character is a digit
        else if (isdigit(password[i]) != 0)
        {
            number = true;
        }
        // else the character is a symbol
        else
        {
            symbol = true;
        }
    }

    // if all the boolean varibales are true, function returns true
    if (uppercase && lowercase && number && symbol)
    {
        return true;
    }

    return false;
}

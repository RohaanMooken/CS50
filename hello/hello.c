#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompts the user for a name and stores it in the name variable
    string name = get_string("Name: ");

    // Prints out "Hello" then the name the user inputed earlier
    printf("hello, %s\n", name);
}
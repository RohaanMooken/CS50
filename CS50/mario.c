#include <stdio.h>
#include <cs50.c>

int main(int argc, string argv[]){

    // Declare variable n
    int n;

    // Prompt the user for a value between 1 and 8
    do
    {
        n = get_int("Height: ");
    } while (n < 1 || n > 8);

    // Create n number of rows
    for(int i = 0; i < n; i++){

        // Create spaces for drawing a pyramid
        for(int j = n-1; j > i; j--){
            printf(" ");
        }

        // Draw left side of the pyramid
        for(int k = 0; k <= i; k++){
            printf("#");
        }

        // Draw the space between the to halves of the pyramid
        printf(" ");

        // Draw the right side of the pyramid
        for(int l = 0; l <= i; l++){
            printf("#");
        }
        
        // Create a new line
        printf("\n");
    }
}

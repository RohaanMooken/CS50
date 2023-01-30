#include <stdio.h>
#include <cs50.c>
#include <string.h>

int main(void){

    long long card = get_long_long("Number: ");
    long long l = card;
    int i = 0;

    while (l > 1){
        l /= 10;
        i++;
    }

    if (i != 13 && i!= 15 && i != 16){
        printf("INVALID\n");
        return 0;
    }

    // Check wether the card is valid, bu using Luhn's algorithm

    int mod1;
    int mod2;
    int sum1 = 0;
    int sum2 = 0;
    int d1;
    int d2;
    int total = 0;
    long long x = card;

    do
    {
        mod1 = x % 10;
        x /= 10;
        sum1 += mod1;

        mod2 = x % 10;
        x /=10;
        
        mod2 *= 2;
        d1 = mod2 % 10;
        d2 = mod2 / 10;
        sum2 = sum2 + d1 + d2;

    } while (x > 0);
    
    total = sum1 + sum2;

    if (total % 10 != 0){
        printf("INVALID\n");
        return 0;
    }

    long long start = card;
    do
    {
        start /= 10;
    } while (start > 100);
    

    // Print out what type of card it is based on the starting numbers
    // AMEX, 34 37
    // Mastercard 51-55
    // Visa 4

    if ((start / 10 == 5) && (0 < start % 10 && start % 10 < 6)){
        printf("MASTERCARD\n");
    }
    else if ((start / 10 == 3) && (start % 10 == 4 || start % 10 == 7)){
        printf("AMEX\n");
    }
    else if (start / 10 == 4){
        printf("VISA\n");
    }
    else{
        printf("INVALID\n");
    }

}

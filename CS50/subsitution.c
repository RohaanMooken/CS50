#include <stdio.h>
#include <cs50.c>
#include <string.h>
#include <ctype.h>

// Got these to lines from the cs50 header file because couldn't use the library on my local computer using the header file
// Thus I am using the C file
string get_string(va_list *args, const char *format, ...) __attribute__((format(printf, 2, 3)));
#define get_string(...) get_string(NULL, __VA_ARGS__)


int main(int argc, string argv[]){

    // Checks to see if there is a sufficient amount of arguments i.e the command: .\substituion.exe 'key'
    if (argc != 2){
        printf("Insufficient amount or to many arguments given.\n");
        return 1;
    }

    // Checks to see if the 'key' contains 26 characters, the number of characters in the alphabet
    if (strlen(argv[1]) != 26){
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string arg = argv[1];

    // Checks to see if the 'key' contains a non alphabetical character and if there exists any duplicate characters in the key
    for(int i = 0; i < strlen(arg)-1; i++){
        if(isalpha(arg[i]) == 0){
            printf("Key contains a non alphabetical character.\n");
            return 1;
        }

        for(int j = i + 1; j < strlen(arg); j++){
            if(arg[i] == arg[j]){
                printf("Key includes duplicate characters.\n");
                return 1;
            }
        }
    }

    // defines the alphabet variable, gets th plaintext input from user and defines the string cipher with the same length as plain
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string plain = get_string("Plaintext : ");
    string cipher[strlen(plain)];

    // Iterates over all the characters in the plain text
    for(int i = 0; i < strlen(plain); i++){
        for(int j = 0; j < strlen(alphabet); j++){
                // Checks to see if the character is lower case, if yes then put it through the key
                if(plain[i] == alphabet[j]){
                    cipher[i] = arg[j];
                }
                // Checks to see if the character is upper case, if yes then put it through the key
                else if (plain[i] == alphabet[j]-32){
                    cipher[i] = arg[j]-32;
                }
                // Last three for loops uses the ASCII table to return the special symbols as is
                for(int k = 32; k < 65; k++){
                    if(plain[i] == k){
                        cipher[i] = plain[i];
                    }
                }
                for(int k = 91; k < 97; k++){
                    if(plain[i] == k){
                        cipher[i] = plain[i];
                    }
                }
                for(int k = 123; k < 127; k++){
                    if(plain[i] == k){
                        cipher[i] = plain[i];
                    }
                }
        }
    }

    // prints the Ciphertext
    printf("Ciphertext: ");
    // Iterates over the characters instead f using %s because I couldn't get it to work on my local computer
    for(int i = 0; i < strlen(plain); i++){
            printf("%c", cipher[i]);
    }

    printf("\n");
    return 0;
}

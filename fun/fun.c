#include <stdio.h>
#include <cs50.h>

int main(void){
    string a = "12";
    int l = 2;

    for(int i = 0; i < l; i++){
        for(int j = 0; j < l; j++){
            for(int k = 0; k < l; k++){
                for(int m = 0; m < l; m++){
                    for(int o = 0; o < l; o++){
                        for(int p = 0; p < l; p++){
                            for(int q = 0; q < l; q++){
                                printf("%c%c%c%c%c%c%c", a[i], a[j], a[k], a[l], a[m], a[o], a[p], a[i]);
                            }
                        }
                    }
                }
            }
        }
    }
}
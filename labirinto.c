#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fptr;

    fptr = fopen("labirinto.txt", "r");

    char labirinto[300];

    while(fgets(labirinto, sizeof labirinto, fptr)){
        printf("%s", labirinto);
    }
}
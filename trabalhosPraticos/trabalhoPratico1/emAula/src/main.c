#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool haveConflict(char ** evento1, int evento1Tamanho, char ** evento2, int evento2Tamanho);

int main(){
    
    char **evento1[2][5] = {"01:15", "02:00"};
    char **evento2[2][5] = {"02:00", "03:00"};
    int evento1tamanho = 2;
    int evento2tamanho = 2;

    haveConflict(evento1, evento1tamanho, evento2, evento2tamanho);

    return 0;
}

bool haveConflict(char ** evento1, int evento1Tamanho, char ** evento2, int evento2Tamanho){
    
    if(evento1[1] == evento2[0]) //tem conflito quando o evento 1 termina no horario que o evento 2 começa
        return true;

    return false;
}
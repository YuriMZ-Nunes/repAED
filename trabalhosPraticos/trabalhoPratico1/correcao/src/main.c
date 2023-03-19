#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool haveConflict(char ** evento1, int evento1tamanho,char ** evento2, int evento2tamanho);

int minutos(char * tempo);

int main(){
    
    char **evento1[2][5] = {"01:15", "02:00"};
    char **evento2[2][5] = {"02:30", "03:00"};

    int evento1tamanho = 2;
    int evento2tamanho = 2;
    
    haveConflict(evento1, evento1tamanho,evento2, evento2tamanho);

}

bool haveConflict(char ** evento1, int evento1tamanho,char ** evento2, int evento2tamanho){
    int comeco1 = 0, fim1 = 0;
    int comeco2 = 0, fim2 = 0;

    if(evento1[1] == evento2[0] || evento1[0] == evento2[1]) //tem conflito quando o evento termina no horario que o outro evento começa
        return true;

    //transforma os horário em inteiro
    comeco1 = transformarInt(evento1[0]);          
    fim1 = transformarInt(evento1[1]);

    comeco2 = transformarInt(evento2[0]);
    fim2 = transformarInt(evento2[1]);

    if(comeco1 > fim2 || comeco2 > fim1) //verifica se não há conflito 
        return false;

    return true;
}

//transforma para inteiro
int transformarInt(char * tempo){
    int transf = 0;
    for(int i = 0; i < 5; i++){
        if(tempo[i] != ':'){
            transf = transf * 10 + (tempo[i] - '0');
        }
    }
    return transf;
}


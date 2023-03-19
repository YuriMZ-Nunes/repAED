#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int minOperations(char **logs, int logsSize);

int main(){
    int logsSize = 6;
    char **logs = malloc(logsSize);

    //Exemplo 2
    logs[0] = "d1/";
    logs[1] = "d2/";
    logs[2] = "./";
    logs[3] = "d3/";
    logs[4] = "../";
    logs[5] = "d31/";

    minOperations(logs, logsSize);

    free(logs);
}

int minOperations(char **logs, int logsSize){
    
    int stepsToBack = 0; //num de operações para voltar

    for(int i = 0; i < logsSize; i++){
        if(stepsToBack == 0 && (strcmp(logs[0], "../")!= 0 || strcmp(logs[0], "./")!= 0 )){ //verifica se logs[0] é uma operação de entrar na pasta
            stepsToBack++;
        }else{
            if(strcmp(logs[i], "../") == 0 ) //verifica se logs[i] é uma operação para voltar
                stepsToBack--;
            else if(strcmp(logs[i], "./") != 0 ){ //se não for para voltar, verifica se é para entrar na pasta
                stepsToBack++;
            }
        }
    } 

    return stepsToBack;
}

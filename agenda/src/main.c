#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEXT (sizeof(char) * 10 + sizeof(int) * 2)
#define PREV (sizeof(char) * 10 + sizeof(int) * 3)

void *push(void **pFirst, void **pCurrent, void **pPrev);
void *pop(void **pFirst);
void *search(void **pFirst, void **pCurrent);
void *list(void **pFirst, void **pCurrent);
void *exitAgenda(void **pFirst, void **pCurrent, void **pPrev);

int main(){
    void **pFirst = malloc(sizeof(int)); //ponteiro para o topo
    void **pCurrent = malloc(sizeof(int)); //ponteiro para percorrer
    void **pPrev = malloc(sizeof(int)); //ponteiro para o nó anterior, usado para inserir um novo nó entre dois nós

    *pFirst = NULL;

    while(1){
        printf("\n\n1. ADD\n2. DELETE\n3. SEARCH\n4. LIST\n5. EXIT\n");
        switch(getchar()){
            case '1':
                push(pFirst, pCurrent, pPrev);
                getchar();
                break;
            case '2':
                pop(pFirst);
                getchar();
                break;
            case '3':
                search(pFirst, pCurrent);
                getchar();
                break;
            case '4':
                list(pFirst, pCurrent);
                getchar();
                break;
            case '5':
                exitAgenda(pFirst, pCurrent, pPrev);
                getchar();
                break;
        }
    }
}

void *push(void **pFirst, void **pCurrent, void **pPrev){
    void *infos = malloc(sizeof(char) * 10 + sizeof(int) * 4); //criação de ponteiro para as informações de cadastro

    *pCurrent = *pFirst;

    printf("\nNome: ");
    scanf("%s", (char *)infos);
    printf("\nIdade: ");
    scanf("%d", (int *)(infos + (sizeof(char) * 10)));
    printf("\nTelefone: ");
    scanf("%d", (int *)(infos + (sizeof(char) * 10) + sizeof(int)));

    if(!*pFirst){ //verifica se a fila esta vazia
        *pFirst = infos; //ponteiro para o primeiro nó aponta para o cadastro
        *(int *)(infos + NEXT) = 0; 
        *(int *)(infos + PREV) = 0; 
    }else{
        while((strcmp((char *)infos, (char *)*pCurrent) > 0 )){ //percorre o buffer para encontrar a posição em que o novo nó será inserido
            if(*(int *)(*pCurrent + NEXT) == 0) //se chegar ao fim, para de percorrer
                break;
            *(int *)pCurrent = *(int *)(*pCurrent + NEXT); //incrementa
        }
        if(*(int *)(*pCurrent + NEXT) == 0 && strcmp((char *)infos, (char *)*pCurrent) > 0){ //verifica se será inserido na ultima posição
            *(int *)(infos + NEXT) = 0; 
            *(int *)(infos + PREV) = *(int *)pCurrent; 
            *(void **)(*pCurrent + NEXT) = infos;
        }else if(strcmp((char *)infos, (char *)*pFirst) < 0){ //se não for na ultima, verifica será inserido na primeira posição
            *(int *)(infos + NEXT) = *(int *)pCurrent;
            *(int *)(infos + PREV) = 0;
            *(void **)(*pCurrent + PREV) = infos;
            *pFirst = infos;
        }else{
            *(int *)(infos + NEXT) = *(int *)pCurrent; //se não for na primeira nem na ultima, será inserido entre dois nós
            *(int *)pPrev = (int)*(int *)(*pCurrent + PREV);
            *(int *)(infos + PREV) = *(int *)pPrev;
            *(void **)(*pCurrent + PREV) = infos;
            *(void **)(*pPrev + NEXT) = infos;
        }
    }
    return 0;
}

void *pop(void **pFirst){
    void *delete; //ponteiro para liberar a memória

    if(*pFirst != NULL){ //verifica se a fila está vazia
        delete = *(void **)pFirst;
        if(*(int *)(*pFirst + NEXT) == 0){ //verifica se não há mais que um nó na fila
            free(delete);
            printf("\n--No removido--");
            *pFirst = NULL;
            return 0;
        }

        *(int *)pFirst = *(int *)(*pFirst + NEXT); //incrementa
        *(int *)(*pFirst + PREV) = 0;
        free(delete);
        printf("\n--No removido--");
        return 0;
    }
    printf("\nNao ha nada para deletar. ");
    return 0;
}

void *search(void **pFirst, void **pCurrent){
    char *name = malloc(sizeof(char) * 10); //ponteiro para armazenar o nome para busca

    printf("\nDigite o nome que deseja buscar: ");
    scanf("%s", name);

    *pCurrent = *pFirst;

    while(*(int *)pCurrent){ //percorre até o fim
        if(strcmp((char *)*pCurrent, (char *)name) == 0){ //se encontrar o nome, mostra as informações encontradas
            printf("\nO(A) %s esta cadastrado(a) e aqui estao seus dados: \n", (char *)*pCurrent);
            printf("\nNome: %s", (char *)*pCurrent);
            printf("\nIdade: %d", *(int *)(*pCurrent + sizeof(char) * 10));
            printf("\nTelefone: %d", *(int *)(*pCurrent + (sizeof(char) * 10) + sizeof(int)));
            free(name);
            return 0;
        }
        *(int *)pCurrent = *(int *)(*pCurrent + NEXT); //incrementa
    }
    printf("\n%s nao esta cadastrado.\n", name); //aviso caso não encontre
    free(name);
    return 0;
}

void *list(void **pFirst, void **pCurrent){
    *pCurrent = *pFirst;

    while(*(int *)pCurrent){ //percorre até o fim mostrando os dados cadastrados
        printf("\n");
        printf("\nNome: %s", (char *)*pCurrent);
        printf("\nIdade: %d", *(int *)(*pCurrent + sizeof(char) * 10));
        printf("\nTelefone: %d", *(int *)(*pCurrent + (sizeof(char) * 10) + sizeof(int)));

        *(int *)pCurrent = *(int *)(*pCurrent + NEXT); //incrementa
    }
    return 0;
}

void *exitAgenda(void **pFirst, void **pCurrent, void **pPrev){
    void *delete; //ponteiro para liberar memória
    
    if(pFirst){ //percorre até o ponteiro para a primeira posição ficar vazio
        while(1){
            delete = *(void **)pFirst; // ponteiro delete aponta para o primeiro nó
            if(*(int *)(*pFirst + NEXT) == 0){ //caso seja o ultimo nó a ser deletado, libera toda a memória e sai do programa
                free(delete);
                free(pFirst);
                free(pCurrent);
                free(pPrev);
                exit(0);
            }
            *(int *)pFirst = *(int *)(*pFirst + NEXT); //incrementa
            free(delete);
        }
    }
    return 0;
}

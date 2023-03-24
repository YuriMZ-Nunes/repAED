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
    void **pPrev = malloc(sizeof(int)); //ponteiro para o nó anterior

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
    void *infos = malloc(sizeof(char) * 10 + sizeof(int) * 4);

    *pCurrent = *pFirst;

    printf("\nNome: ");
    scanf("%s", (char *)infos);
    printf("\nIdade: ");
    scanf("%d", (int *)(infos + (sizeof(char) * 10)));
    printf("\nTelefone: ");
    scanf("%d", (int *)(infos + (sizeof(char) * 10) + sizeof(int)));

    if(!*pFirst){
        *pFirst = infos;
        *(int *)(infos + NEXT) = 0;
        *(int *)(infos + PREV) = 0;
    }else{
        while((strcmp((char *)infos, (char *)*pCurrent) > 0 )){
            if(*(int *)(*pCurrent + NEXT) == 0)
                break;
            *(int *)pCurrent = *(int *)(*pCurrent + NEXT);
        }
        if(*(int *)(*pCurrent + NEXT) == 0 && strcmp((char *)infos, (char *)*pCurrent) > 0){
            *(int *)(infos + NEXT) = 0;
            *(int *)(infos + PREV) = *(int *)pCurrent;
            *(void **)(*pCurrent + NEXT) = infos;
        }else if(strcmp((char *)infos, (char *)*pFirst) < 0){
            *(int *)(infos + NEXT) = *(int *)pCurrent;
            *(int *)(infos + PREV) = 0;
            *(void **)(*pCurrent + PREV) = infos;
            *pFirst = infos;
        }else{
            *(int *)(infos + NEXT) = *(int *)pCurrent;
            *(int *)pPrev = (int)*(int *)(*pCurrent + PREV);
            *(int *)(infos + PREV) = *(int *)pPrev;
            *(void **)(*pCurrent + PREV) = infos;
            *(void **)(*pPrev + NEXT) = infos;
        }
    }
    return 0;
}

void *pop(void **pFirst){
    void *delete;

    if(*pFirst != NULL){
        delete = *(void **)pFirst;
        if(*(int *)(*pFirst + NEXT) == 0){
            free(delete);
            printf("\n--No removido--");
            *pFirst = NULL;
            return 0;
        }

        *(int *)pFirst = *(int *)(*pFirst + NEXT);
        *(int *)(*pFirst + PREV) = 0;
        free(delete);
        printf("\n--No removido--");
    }
    printf("\nNao ha nada para deletar. ");
    return 0;
}

void *search(void **pFirst, void **pCurrent){
    char *name = malloc(sizeof(char) * 10);

    printf("\nDigite o nome que deseja buscar: ");
    scanf("%s", name);

    *pCurrent = *pFirst;

    while(*(int *)pCurrent){
        if(strcmp((char *)*pCurrent, (char *)name) == 0){
            printf("\nO(A) %s esta cadastrado(a) e aqui estao seus dados: \n", (char *)*pCurrent);
            printf("\nNome: %s", (char *)*pCurrent);
            printf("\nIdade: %d", *(int *)(*pCurrent + sizeof(char) * 10));
            printf("\nTelefone: %d", *(int *)(*pCurrent + (sizeof(char) * 10) + sizeof(int)));
            free(name);
            return 0;
        }
        *(int *)pCurrent = *(int *)(*pCurrent + NEXT);
    }
    printf("\n%s nao esta cadastrado.\n", name);
    free(name);
    return 0;
}

void *list(void **pFirst, void **pCurrent){
    *pCurrent = *pFirst;

    while(*(int *)pCurrent){
        printf("\n");
        printf("\nNome: %s", (char *)*pCurrent);
        printf("\nIdade: %d", *(int *)(*pCurrent + sizeof(char) * 10));
        printf("\nTelefone: %d", *(int *)(*pCurrent + (sizeof(char) * 10) + sizeof(int)));

        *(int *)pCurrent = *(int *)(*pCurrent + NEXT);
    }
    return 0;
}

void *exitAgenda(void **pFirst, void **pCurrent, void **pPrev){
    void *delete;
    
    if(pFirst){
        while(1){
            delete = *(void **)pFirst;
            if(*(int *)(*pFirst + NEXT) == 0)
                free(delete);
            free(pFirst);
            free(pCurrent);
            free(pPrev);
            exit(0);
        }

        *(int *)pFirst = *(int *)(*pFirst + NEXT);
        free(delete);
    }
    return 0;
}

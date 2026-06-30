#include <stdio.h>
#include <stdlib.h>

int main() {
    int m;
    
    printf("Qual o tamanho do vetor?\n");
    scanf("%d", &m);
    int vet[m], i;
    printf("agora digite os elementos do vetor:\n");
    for(i = 0; i < m; i++){
        scanf("%d", &vet[i]);
    }
    //system("cls");
    for(i = 0; i < m; i++){
        printf("%d ", vet[i]);
    }

    return 0;
}


#include <stdio.h>

int main(){
    int a, b, i, j;
    printf("Digite quantidade de linhas e colunas:\n");
    scanf("%d %d", &a, &b);
    int A[a][b];
    printf("digite os elementos da matriz:");
    for(i = 0; i < a; i++){
        for(j = 0; j < b; j++){
            scanf("%d", A[i][j]);
        }
    }
    for(j = 0; j < b; j++){
    for(i = 0; i < a; i++){
    printf("%d ", A[i][j]);
    
    }
    printf("\n");
}
    return 0;
}
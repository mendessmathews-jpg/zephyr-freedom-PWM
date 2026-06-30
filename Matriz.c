#include <stdio.h>
#include <stdlib.h>

int main(){
int a, b;
printf("Quantidade de linha e colunas?");
scanf("%d %d", &a, &b);
int M[a][b], i, j;
printf("Escreva os elementos da matriz:\n");
for(i = 0; i < a; i++){
    for(j = 0; j < b; j++){
    scanf("%d", &M[i][j]);
    }
}
for(j = 0; j < b; j++){
    for(i = 0; i < a; i++){
    printf("%d ", M[i][j]);
    
    }
    printf("\n");
}
    return 0;
}
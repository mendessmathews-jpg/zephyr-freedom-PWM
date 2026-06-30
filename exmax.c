#include <stdio.h>
#include <stdlib.h>

int main() {
    float T[5], s = 0, m, a;
    int n;
    printf("Digite as notas dos alunos:\n");
    for(n = 0; n < 5; n++){
        scanf("%f", &T[n]);
        s += T[n];
    }
    m = s / 5;
    printf("%f", m);
    printf("\n");

    for(n = 0; n < 5; n++){
        if(T[n] > m){
        printf("%1.f:Nota acima da media\n", T[n]);

    }
}
a = T[0];
    for(n = 0; n < 5; n++){
        if(T[n] > a){
            a = T[n];
        }

    }        printf("%1.f:Maior nota registrada\n", a);

    return 0;

}

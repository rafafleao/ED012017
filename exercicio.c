#include <stdio.h>

int main(){
    
    int vetor[10];
    int matriz[3][4];
    int i,j;
    
    printf("\nVamos fazer o VETOR!\n\n");
    
    for(i=0;i<10;i++){
        printf("Informe o valor da posicao [%d]: ", i+1);
        scanf("%d", &vetor[i]);
    }
    
    for(i=0;i<10;i++){
        printf("O valor da posicao [%d] eh: %d \n", i+1, vetor[i]);
    }
    
    printf("\nVamos fazer a MATRIZ!\n\n");
    
    for(i=0;i<3;i++){
        for(j=0;j<4;j++){
            printf("Informe o valor da linha [%d] e coluna [%d]: ", i+1, j+1);
            scanf("%d", &matriz[i][j]);
        }
    }
    
    for(i=0;i<3;i++){
        for(j=0;j<4;j++){
            printf("O valor da linha [%d] e coluna [%d] eh respectivamente: %d \n ", i+1, j+1, matriz[i][j]);
        }
    }
        return 0;
}

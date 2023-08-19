#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sparse.h"
#include <time.h>

int main(void)
{
    int menu = 1;
    char matrixName[5];
    do{
        printf("Qual operacao voce deseja realizar:\n");
        printf("1- Criar uma matriz.\n");
        printf("2- Destruir uma matriz.\n");
        printf("3- Printar uma matriz.\n");
        printf("4- Somar duas matrizes.\n");
        printf("5- Multilpicar duas matrizes.\n");
        printf("6- Transpor uma matriz.\n");
        printf("7-Buscar um elemento.\n");
        printf("8- Alterar um elemento.\n");
        printf("9- Sair.\n");
        printf("Resposta: ");
        scanf("%d", &menu);
        getchar();

        switch (menu)
        {
            case 1:
                printf("Como deseja chamar a matriz(até 4 caracteres): ");
                scanf("%4s", matrixName);
                MatrixList* matrixName = matrix_create();
                printf("Matriz criada com sucesso!\n");
                break;

            case 2:
                printf("Qual matriz deseja destruir? ");
                scanf("%4s", matrixName);
                matrix_destroy(matrixName);
                printf("Matriz destruída!\n");
                free(matrixName);
                break;
            
            case 3:
                printf("Qual matriz deseja printar? ");
                scanf("%4s", matrixName);
                matrix_print(matrixName);
                break;

            case 4:
                break;

            case 9:
                printf("Obrigado por usar nosso programa!\n\n");
                break;
        }
    }while(menu != 9);

    return 0;
}

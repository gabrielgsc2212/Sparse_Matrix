#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "sparse.h"
/*
LIMITAÇÕES DO CÓDIGO:

- Para a soma de matrizes, você deve criar a terceira matriz do mesmo tamanho das descritas anteriormente e não adicionar valores nela;
- Foi usado uma segunda struct com ponteiro para a célula cabeça e armazena o tamanho da matriz proposta;
- 

*/
int main(void)
{
    MatrixList* A = matrix_create();
    matrix_print(A);
    MatrixList* B = matrix_create();
    matrix_print(B);
    MatrixList* C = matrix_add(A, B);
    matrix_print(C);
    matrix_destroy(A);
    matrix_destroy(B);
    matrix_destroy(C);

    return 0;
}
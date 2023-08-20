#include "matrix.h"

/*
LIMITAÇÕES DO CÓDIGO:

- Foi usado uma segunda struct com ponteiro para a célula cabeça e armazena o tamanho da matriz proposta;
- 

*/
int main(void)
{
    MatrixList* A = matrix_create();
    matrix_print(A);
    MatrixList* B = matrix_create();
    matrix_print(B);   
    MatrixList* C = matrix_multiply(A, B);
    matrix_print(C);

    matrix_destroy(A);
    matrix_destroy(B);
    matrix_destroy(C);

    return 0;
}
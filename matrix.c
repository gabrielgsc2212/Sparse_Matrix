#include "matrix.h"
/*
    Alunos: Gabriel Gonzaga Seabra Câmara e Pedro Paulo Moreira de Freitas

    Trabalho AED 1:
    Desenvolver um TAD de matriz esparsa, com funções de criação, print, destruição, adição, multiplicação e transposição das mesmas aplicando listas circulares e com o uso de uma célula cabeça localizada em -1 -1.

    OBS:  Todos os requisitos das funções solicitadas foram cumpridas em relação à precisão de resultados, parâmetros e retornos, assim como quase todas as exceções. No entanto, foi utilizado uma segunda struct, denominada MatrixList -que aponta diretamente para a célula cabeça e armazena o tamanho denominado da matriz- que foi usada na criação de todas as matrizes e suas respectivas operações.

    Não há nenhum desperdício de memória, a destruição garante que nenhum dado sobre na memória e seja desperdiçado.
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
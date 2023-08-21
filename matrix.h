#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

struct matrix 
{
      int line;
      int column;
      float info;
      struct matrix* right;
      struct matrix* below;
}; 
typedef struct matrix Matrix;

struct MatrixList 
{
      int linha;
      int coluna;
      Matrix* head;
};
typedef struct MatrixList MatrixList;

float matrix_getelem(MatrixList* m, int x, int y)
{
      if (x - 1 < -1 || x - 1 >= m->linha || y - 1 < -1 || y - 1 >= m->coluna)
      {
            printf("Posicao fora dos limites da matriz(GETELEM).\n");
            exit(EXIT_FAILURE);
      }

      Matrix* currentNode = m->head->right;

      while (currentNode != m->head)
      {
            if (currentNode->line == x - 1 && currentNode->column == y - 1)
            {
                  return currentNode->info;
            }
            currentNode = currentNode->right;
      }

      return 0.0;
}

void matrix_setelem(MatrixList* m, int x, int y, float elem)
{
      if (x - 1 < -1 || x - 1 >= m->linha || y - 1 < -1 || y - 1 >= m->coluna)
      {
            printf("Posicao fora dos limites da matriz(SETELEM).\n");
            exit(EXIT_FAILURE);
      }

      Matrix* currentNode = m->head->right;

      while (currentNode != m->head)
      {
            if (currentNode->line == x - 1 && currentNode->column == y - 1)
            {
                  currentNode->info = elem;
                  return;
            }
            currentNode = currentNode->right;
      }

      // Se o elemento não existir, criar um novo nó para atribuir o valor
      Matrix* newNode = (Matrix*)malloc(sizeof(Matrix));
      if (newNode == NULL) 
      {
            printf("Falha ao alocar memória para o nó da matriz");
            exit(EXIT_FAILURE);
      }

      newNode->line = x - 1;
      newNode->column = y - 1;
      newNode->info = elem;

      newNode->below = m->head->below;
      m->head->below = newNode;

      newNode->right = m->head->right;
      m->head->right = newNode;
      printf("\n");
}

MatrixList* matrix_create() 
{
      MatrixList* matrixList = (MatrixList*)malloc(sizeof(MatrixList));

      if (matrixList == NULL) 
      {
            printf("Falha ao alocar memória para a lista de matriz");
            exit(EXIT_FAILURE);
      }

      printf("Digite o numero de linhas e colunas: ");
      scanf("%d %d", &matrixList->linha, &matrixList->coluna);
      getchar();

      if (matrixList->linha < 1 || matrixList->coluna < 1)
      {
            printf("Valores nao aceitos para a criacao de uma matriz.");
            exit(EXIT_FAILURE);
      }

      matrixList->head = (Matrix*)malloc(sizeof(Matrix));

      if (matrixList->head == NULL) 
      {
            printf("Falha ao alocar memória para o nó cabeça da matriz");
            exit(EXIT_FAILURE);
      }
      
      matrixList->head->line = -1;
      matrixList->head->column = -1;
      matrixList->head->info = 0;
      matrixList->head->right = matrixList->head;
      matrixList->head->below = matrixList->head;

      int line, column;
      float info;
      char input[1000];

      printf("Digite a linha, coluna e valor (digite '.' para sair):\n");
      while (1) 
      {
            fgets(input, sizeof(input), stdin);

            if (input[0] == '.') 
            {
                  break;
            }
            sscanf(input, "%d %d %f", &line, &column, &info);

            if (line <= 0 || column <= 0 || line > matrixList->linha || column > matrixList->coluna)
            {
                  printf("Valor fora dos limites da matriz.\n");
                  continue;
            }

            matrix_setelem(matrixList, line, column, info);
      }

      printf("\n");
      return matrixList;
}


void matrix_destroy(MatrixList* m) 
{
      Matrix* currentNode = m->head->right;
      while (currentNode != m->head) 
      {
            Matrix* temp = currentNode;
            currentNode = currentNode->right;
            free(temp);
      }

      free(m->head);

      free(m);
}

void matrix_print(MatrixList* m) 
{
    printf("Matriz:\n");

      for (int line = 0; line < m->linha; line++) {
            for (int column = 0; column < m->coluna; column++) {
                  Matrix* currentNode = m->head->right;

                  while (currentNode != m->head) 
                  {
                        if (currentNode->line == line && currentNode->column == column) 
                        {
                              printf("%.1f\t", currentNode->info);
                              break;
                        }
                        currentNode = currentNode->right;
                  }

                  if (currentNode == m -> head) 
                  {
                        printf("0.0\t");
                  }
            }
      printf("\n");
      }
      printf("\n");
}

MatrixList* matrix_add(MatrixList* m, MatrixList* n)
{
            if (m->linha != n->linha || m->coluna != n->coluna)
            {
                  printf("As matrizes não possuem as mesmas dimensões para realizar a soma.");
                  return NULL;
            }

            MatrixList* result = (MatrixList*)malloc(sizeof(MatrixList));
            if (result == NULL)
            {
                  printf("Falha ao alocar memória para a matriz de resultado.");
                  exit(EXIT_FAILURE);
            }

            result->linha = m->linha;
            result->coluna = m->coluna;

            result->head = (Matrix*)malloc(sizeof(Matrix));
            if (result->head == NULL)
            {
                  printf("Falha ao alocar memória para o nó cabeça da matriz de resultado.");
                  exit(EXIT_FAILURE);
            }
            result -> head -> line = -1;
            result -> head -> column = -1;
            result->head->info = 0;
            result->head->right = result->head;
            result->head->below = result->head;

            for (int line = 0; line < m -> linha; line++)
            {
                  for (int column = 0; column < m -> coluna; column++)
                  {
                        float soma = matrix_getelem(m, line + 1, column + 1) + matrix_getelem(n, line + 1, column + 1);

                        if (soma != 0)
                        {
                              matrix_setelem(result, line + 1, column + 1, soma);
                        }
                  }
            }

            printf("\n");
            return result;
}

MatrixList* matrix_transpose(MatrixList* m)
{
      MatrixList* result = (MatrixList*)malloc(sizeof(MatrixList));

      if (result == NULL)
      {
            printf("Falha ao alocar memória para a matriz transposta.");
            exit(EXIT_FAILURE);
      }

      result->linha = m->coluna;
      result->coluna = m->linha;

      result->head = (Matrix*)malloc(sizeof(Matrix));
      if (result->head == NULL)
      {
            printf("Falha ao alocar memória para o nó cabeça da matriz transposta.");
            exit(EXIT_FAILURE);
      }
      result->head->line = -1;
      result->head->column = -1;
      result->head->info = 0;
      result->head->right = result->head;
      result->head->below = result->head;

      for (int line = 0; line < m->linha; line++)
      {
            for (int column = 0; column < m->coluna; column++)
            {
                  float elem = matrix_getelem(m, line + 1, column + 1);
                  if (elem != 0)
                  {
                        matrix_setelem(result, column + 1, line + 1, elem);
                  }
            }
      }

      return result;
}

MatrixList* matrix_multiply(MatrixList* m, MatrixList* n)
{
      if (m->coluna != n->linha)
      {
            printf("Número de colunas da primeira matriz não é igual ao número de linhas da segunda matriz.");
            return NULL;
      }

      MatrixList* result = (MatrixList*)malloc(sizeof(MatrixList));

      if (result == NULL)
      {
            printf("Falha ao alocar memória para a matriz resultante da multiplicação.");
            exit(EXIT_FAILURE);
      }

      result->linha = m->linha;
      result->coluna = n->coluna;

      result->head = (Matrix*)malloc(sizeof(Matrix));
      if (result->head == NULL)
      {
            printf("Falha ao alocar memória para o nó cabeça da matriz resultante da multiplicação.");
            exit(EXIT_FAILURE);
      }

      result->head->line = -1;
      result->head->column = -1;
      result->head->info = 0;
      result->head->right = result->head;
      result->head->below = result->head;

      // Matriz intermediária para auxiliar na multiplicação
      float** intermediate = (float**)malloc(m->linha * sizeof(float*));
      for (int i = 0; i < m->linha; i++)
      {
            intermediate[i] = (float*)calloc(n->coluna, sizeof(float));
      }

      for (int i = 0; i < m->linha; i++)
      {
            for (int j = 0; j < n->coluna; j++)
            {
                  for (int k = 0; k < m->coluna; k++)
                  {
                  intermediate[i][j] += matrix_getelem(m, i + 1, k + 1) * matrix_getelem(n, k + 1, j + 1);
                  }

                  if (intermediate[i][j] != 0)
                  {
                  matrix_setelem(result, i + 1, j + 1, intermediate[i][j]);
                  }
            }
      }

      for (int i = 0; i < m->linha; i++)
      {
            free(intermediate[i]);
      }
      free(intermediate);

      return result;
}

#endif
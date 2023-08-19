#ifndef SPARSE_H
#define SPARSE_H

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
      char input[100];

      printf("Digite a linha, coluna e valor (digite '.' para sair):\n");
      while (1) 
      {
            fgets(input, sizeof(input), stdin);
            if (input[0] == '.') 
            {
                  break;
            }
            sscanf(input, "%d %d %f", &line, &column, &info);

            Matrix* newNode = (Matrix*)malloc(sizeof(Matrix));
            if (newNode == NULL) 
            {
                  printf("Falha ao alocar memória para o nó da matriz");
                  exit(EXIT_FAILURE);
            }

            newNode->line = line - 1;
            newNode->column = column - 1;
            newNode->info = info;

            newNode->below = matrixList->head->below;
            matrixList->head->below = newNode;

            newNode->right = matrixList->head->right;
            matrixList->head->right = newNode;
      }

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
}

MatrixList* matrix_add(MatrixList* m, MatrixList* n)
{
      if (m->linha != n->linha || m->coluna != n->coluna)
      {
            printf("As matrizes não possuem as mesmas dimensões para realizar a soma.");
            return NULL;
      }

      MatrixList* result = matrix_create();

      for (int line = 0; line < m->linha; line++)
      {
            for (int column = 0; column < m->coluna; column++)
            {
                  Matrix* currentNodeM = m->head->right;
                  Matrix* currentNodeN = n->head->right;
                  float sum = 0;

                  while (currentNodeM != m->head || currentNodeN != n->head)
                  {
                  if (currentNodeM->line == line && currentNodeM->column == column)
                  {
                        sum += currentNodeM->info;
                        currentNodeM = currentNodeM->right;
                  }

                  if (currentNodeN->line == line && currentNodeN->column == column)
                  {
                        sum += currentNodeN->info;
                        currentNodeN = currentNodeN->right;
                  }

                  if (currentNodeM != m->head)
                  {
                        currentNodeM = currentNodeM->right;
                  }
                  if (currentNodeN != n->head)
                  {
                        currentNodeN = currentNodeN->right;
                  }


                  if (currentNodeM == m->head && currentNodeN == n->head)
                  {
                        break;
                  }
                  }

                  if (sum != 0)
                  {
                  Matrix* newNode = (Matrix*)malloc(sizeof(Matrix));
                  if (newNode == NULL)
                  {
                        printf("Falha ao alocar memória para o nó da matriz de resultado");
                        exit(EXIT_FAILURE);
                  }

                  newNode->line = line;
                  newNode->column = column;
                  newNode->info = sum;

                  newNode->below = result->head->below;
                  result->head->below = newNode;

                  newNode->right = result->head->right;
                  result->head->right = newNode;
                  }
            }
      }

      return result;
}

#endif
#include <stdio.h>
#include <stdlib.h>

#define N_MAX 10
#define M_MAX 10

struct matrix {
  int filas;
  int columnas;
  float mat[N_MAX][M_MAX];
};

typedef struct matrix matrix_t;

void imprimir_matriz(matrix_t);
void cargar_matriz(matrix_t *, char *);
void sumar_matrices(matrix_t, matrix_t, matrix_t *);
matrix_t sumar_matrices_r(matrix_t, matrix_t);
void guardar_matriz(matrix_t, char *);

int main(void)
{
  matrix_t A = {0}, B = {0}, C = {0};

  cargar_matriz(&A, "mat_A.txt");
  cargar_matriz(&B, "mat_B.txt");

	printf("Matriz A:\n");
  imprimir_matriz(A);
	printf("\nMatriz B:\n");
  imprimir_matriz(B);

  sumar_matrices(A, B, &C);
  // C = sumar_matrices_r(A, B);
	printf("\nMatriz C: (Suma de A y B)\n");
  imprimir_matriz(C);
  guardar_matriz(C, "mat_C.txt");
	printf("\nMatriz C guardada en mat_C.txt\n");

  return 0;
}

void cargar_matriz(matrix_t *p, char *file)
{
	FILE *f = fopen(file, "r");
	if(f == NULL)
	{
		printf("Error!! No se pudo abrir el archivo %s\n", file);
		exit(1);
	}

	if(fscanf(f, "%d %d",&p->filas ,&p->columnas) != 2)
	{
		printf("Error!! Formato incorrecto en archivo %s\n", file);
		fclose(f);
		exit(1);
	}

	for(int i = 0; i < p->filas; i++)
	{
		for(int j = 0; j < p->columnas; j++)
		{
			if(fscanf(f, "%f", &p->mat[i][j]) != 1)
			{
				printf("Error!! Faltan datos en archivo %s\n", file);
				fclose(f);
				exit(1);
			}
		}
	}
	fclose(f);
}

void imprimir_matriz(matrix_t m) {
  for (int i = 0; i < m.filas; i++) {
    for (int j = 0; j < m.columnas; j++)
      printf("%9.2f", m.mat[i][j]);
    printf("\n");
  }
}

void sumar_matrices(matrix_t A, matrix_t B, matrix_t *pC)
{
	if(A.filas != B.filas || A.columnas != B.columnas)
	{
		printf("Error!! Las matrices no tienen las mismas dimensiones\n");
		exit(1);
	}

	pC->filas = A.filas;
	pC->columnas = A.columnas;

	for(int i = 0; i < A.filas; i++)
	{
		for(int j = 0; j < A.columnas; j++)
		{
			pC->mat[i][j] = A.mat[i][j] + B.mat[i][j];
		}
	}
}

void guardar_matriz(matrix_t m, char *file)
{
	FILE *f = fopen(file, "w");
	if(f == NULL)
	{
		printf("Error!! No se pudo crear el archivo %s\n", file);
		exit(1);
	}
	fprintf(f, "%d %d\n", m.filas, m.columnas);

	for(int i = 0; i < m.filas; i++)
	{
		for(int j = 0; j < m.columnas; j++)
		{
			fprintf(f, "%.2f\t", m.mat[i][j]);
		}
		fprintf(f, "\n");
	}

	fclose(f);
}

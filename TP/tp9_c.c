#include <stdio.h>
#include <stdlib.h>

#define TAM_NOMBRE_ESTUDIANTE 80
#define TAM_NOMBRE_MATERIA 80

typedef struct {
  char nombre[TAM_NOMBRE_MATERIA];
  int cantidad_parciales;
  int *parcial;
  float promedio;
} materia_t;

struct estudiante {
  int legajo;
  char nombre[TAM_NOMBRE_ESTUDIANTE];
  int cantidad_materias;
  materia_t *materia;
};

struct estudiante cargar_estudiante(void);
void imprimir_estudiante(struct estudiante);
materia_t* reservar_materias(int);
int* reservar_parciales(int);
void liberar_parciales(int*);
void liberar_materias(materia_t*, int);
void cargar_materia(materia_t*);
void cargar_materias(materia_t*, int);
void cargar_parciales(materia_t*);
void calcular_promedio(materia_t*);


int main(void)
{
  struct estudiante est1;

  est1 = cargar_estudiante();
  cargar_materias(est1.materia, est1.cantidad_materias);

  imprimir_estudiante(est1);

  liberar_materias(est1.materia, est1.cantidad_materias);

  return 0;
}

struct estudiante cargar_estudiante(void)
{
  struct estudiante e;

  printf("Ingrese legajo del estudiante: ");
  scanf("%d", &e.legajo);

  printf("Ingrese nombre del estudiante: ");
  scanf(" %80[^\n]s", e.nombre);

	printf("¿Cuantas materias va a cargar? ");
	scanf("%d", &e.cantidad_materias);

  e.materia = reservar_materias(e.cantidad_materias);

  return e;
}

void imprimir_estudiante(struct estudiante e)
{
  printf("%10d", e.legajo);
  printf(" %s\n", e.nombre);

	for (int i = 0; i < e.cantidad_materias; i++)
	{
		printf("%s:\t", e.materia[i].nombre);
  	for (int j = 0; j < e.materia[i].cantidad_parciales; j++)
    	printf("%5d", e.materia[i].parcial[j]);
		printf(" Promedio: %.2f\n", e.materia[i].promedio);
  }
  printf("\n");
}

void cargar_materia(materia_t *p)
{
  printf("Ingrese el nombre de la materia: ");
  scanf(" %80[^\n]s", p->nombre);
  printf("¿Cuántos parciales tiene %s? ", p->nombre);
  scanf("%d", &p->cantidad_parciales);

  p->parcial = reservar_parciales(p->cantidad_parciales);

  cargar_parciales(p);
}

void cargar_materias(materia_t* materias, int cant)
{
	for(int i = 0; i < cant; i++)
	{
		cargar_materia(&materias[i]);
	}
}


void cargar_parciales(materia_t *p)
{
  for (int i = 0; i < p->cantidad_parciales; i++)
  {
    printf("Ingrese calificación del %d° parcial: ", i + 1);
    do
    {
    	scanf("%d", p->parcial+i);
    	if((p->parcial[i] > 10) || (p->parcial[i] < 1))
    		printf("ERROR! La calificacion es entre 1 y 10\nIngrese nuevamente: ");
    }while((p->parcial[i] > 10) || (p->parcial[i] < 1));
  }

  calcular_promedio(p);
}

materia_t* reservar_materias(int n)
{
  materia_t *p = NULL;

  p = malloc(n * sizeof(materia_t));
  if (p == NULL)
  {
    printf("No se pudo reservar memoria. Fin del programa.\n");
    exit(1);
  }

  return p;
}

int* reservar_parciales(int n)
{
  int *p = NULL;

  p = malloc(n * sizeof(int));
  if (p == NULL)
  {
    printf("No se pudo reservar memoria. Fin del programa.\n");
    exit(1);
  }

  return p;
}

void liberar_parciales(int *p)
{
  if (p != NULL)
    free(p);
}

void liberar_materias(materia_t *p, int cant)
{
  for(int i = 0; i < cant; i++)
  {
		liberar_parciales(p[i].parcial);
  }
    free(p);
}

void calcular_promedio(materia_t* p)
{
	float suma = 0;
	for(int i = 0; i < p->cantidad_parciales; i++)
	{
		suma += p->parcial[i];
	}
	p->promedio = suma / p->cantidad_parciales;

}

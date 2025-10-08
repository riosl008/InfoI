#include <stdio.h>
#include <stdlib.h>

#define TAM 20

int cuantas_piezas(int);
int rectificable(float, float);
int rechazada(float, float);

void cargar_piezas(float *, int);
int contar(int (*)(float, float), float, float *, int);
float* reservar_memoria(int);
void segregar(int (*)(float, float), float, float *, int, float *);
void mostrar_piezas(char *, float *, int);

int main (void)
{
	float diametros[TAM] = {0};
	int n, n_rectificar, n_rechazar;
	float max = 12, min = 10;
	float *p_rectificables, *p_rechazadas;

	n = cuantas_piezas(TAM);

	cargar_piezas(diametros, n);

	n_rectificar = contar(rectificable, max, diametros, n);
	p_rectificables = reservar_memoria(n_rectificar);
	segregar(rectificable, max, diametros, n, p_rectificables);

	n_rechazar = contar(rechazada, min, diametros, n);
	p_rechazadas = reservar_memoria(n_rechazar);
	segregar(rechazada, min, diametros, n, p_rechazadas);

	mostrar_piezas("rectificables", p_rectificables, n_rectificar);
	mostrar_piezas("rechazadas", p_rechazadas, n_rechazar);

	free(p_rectificables);
	free(p_rechazadas);

	return 0;
}

int cuantas_piezas(int max)
{
	int n;

	do
	{
		printf("Cuantas piezas agregará? ");
		scanf("%d", &n);
	}while(n < 0 || n > max);

	return n;
}

int rectificable(float diametro, float valor)
{
	if(diametro > valor)
		return 1;
	else
		return 0;
}

int rechazada(float diametro, float valor)
{
	if(diametro < valor)
		return 1;
	else
		return 0;
}

void cargar_piezas(float *p, int n)
{
	for(int i = 0; i < n; i++)
	{
		float valor;
		printf("Ingrese diametro de pieza %d: ", i);
		do
		{
			scanf("%f", &valor);
			if(valor <= 0)
				printf("ERROR! El diametro debe ser mayor a 0.\nIngrese nuevamente: ");
		}while(valor <= 0);
	*(p+i) = valor;

	}
}

int contar(int (*criterio)(float, float), float valor, float *p, int n)
{
	int cuenta = 0;
	for(int i = 0; i < n; i++)
	{
		if(criterio(*(p + i), valor))
			cuenta++;

	}
	return cuenta;
}

float* reservar_memoria(int n)
{
	float *puntero = (float*) malloc(n*sizeof(float));
	if(puntero == NULL)
	{
		printf("ERROR: No se pudo reservar memoria\n");
		exit(1);
	}
	return puntero;
}
void segregar(int (*criterio)(float, float), float valor, float *p, int n, float *q)
{
	int j = 0;
	for(int i = 0; i < n; i++)
	{
		if(criterio(*(p+i), valor))
		{
			*(q + j) = *(p + i);
			j++;
		}
	}
}

void mostrar_piezas(char *mensaje, float *p, int n)
{
	printf("\nPiezas %s: \n", mensaje);
	if(n == 0)
		printf("No hay piezas %s\n", mensaje);
	else
	{
		for(int i = 0; i < n; i++)
		{
			printf("Diametro: %.2f\n", *(p + i));
		}
	}
}

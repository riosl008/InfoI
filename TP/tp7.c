
//URL:https://github.com/riosl008/InfoI

#include <stdio.h>
#define TAM 100

int main (void)
{
	int cod[TAM];
	float precio[TAM];
	int n, min, max, posMin = 0, posMax = 0, rep;

	printf("Ingrese la cantidad de productos a cargar: ");
	scanf("%d", &n);

	printf("\n\nIngrese %d productos, se solicitará el código y precio\n\n", n);
	for(int i = 0; i < n; i++)
	{
		printf("Ingrese el código de barras(1-999999999): ");
		do
		{
			scanf("%d", &cod[i]);
			rep = 0;
			if((cod[i] < 1) || (cod[i] > 999999999))
			{
				printf("Error. El código de barras debe estar entre 1 y 999999999\nIngrese nuevamente: ");
				rep = 1;
			}

			for(int j = 0; j < i; j++)
			{
				if(cod[i] == cod[j])
				{
					printf("Error. El código de barras %d ya fue ingresado\nIngrese nuevamente: ", cod[i]);
					rep = 1;
					break;
				}


			}
		}while(rep == 1);

		printf("\n\nIngrese el precio: $");
		do
		{
			scanf("%f", &precio[i]);
			if(precio[i] < 0)
				printf("Error. El precio debe ser positivo\nIngrese nuevamente: ");

		}while(precio[i] < 0);
		if(i == 0)
		{
			min = precio[i];
			max = precio[i];
		}
		if (min > precio[i])
		{
			min = precio[i];
			posMin = i;
		}
		if (max < precio[i])
		{
			max = precio[i];
			posMax = i;
		}
	}

	printf("Código\t\tPrecio\n");
	for(int i = 0; i < n; i++)
	{
		printf("%d\t\t%.2f\n", cod[i], precio[i]);
	}

	printf("\n\nMás caro: [%d] $%.2f\n", cod[posMax], precio[posMax]);
	printf("Más barato: [%d] $%.2f\n", cod[posMin], precio[posMin]);

	return 0;
}

/*
REPOSITORIO:
https://github.com/riosl008/InfoI.git
*/


#include <stdio.h>

int main (void)
{
	int cant, nota, notas = 0, min = 100, max = 0;
	float prom;

	printf("Ingresar la cantidad de alumnos a evaluar: ");
	do
	{
		scanf("%d", &cant);
		if (cant < 0)
			printf("ERROR\nIngresar nuevamente: ");
	}while (cant < 0);

	for (int i = 0; i < cant; i++)
	{
		printf("Ingresar la calificacion del alumno N°%d: ", i+1);
		do
		{
			scanf("%d", &nota);
			if ((nota > 100) || (nota < 0))
				printf("FUERA DE RANGO\nIngresar nuevamente: ");
		}while ((nota > 100) || (nota < 0));
		if (nota < min)
			min = nota;
		if (nota > max)
			max = nota;
		notas += nota;
	}
	prom = (float) notas / cant;
	printf("El promedio de las calificaciones es %.2f\n", prom);
	printf("La nota mayor fue %d y la nota menor es %d\n", max, min);
	return 0;
}

#include <stdio.h>
#include <math.h>
#define PI 3.1415

float calcularAreaRectangulo(float, float);
float calcularPerimetroRectangulo(float, float);
float calcularDiagonalRectangulo(float, float);
float calcularAreaCirculo(float);
float calcularPerimetroCirculo(float);
void imprimirResultados(float, float);

int op;

int main (void)
{

	float lon, alt, rad;
	printf("Ingrese la figura que desea calcular:\n1_\tRectangulo\n2_\tCirculo\n");
	do
	{
		scanf("%d", &op);
		if((op < 1) || (op > 2))
			printf("ERROR!! Ingrese 1 o 2\nIngrese nuevamente: ");
	}while((op < 1) || (op > 2));

	switch(op)
	{
		case 1:
			printf("Opcion de rectangulo seleccionada");
			printf("\n\nIngrese la longitud del rectangulo: ");
			do
			{
				scanf("%f", &lon);
				if(lon <= 0)
					printf("La longitud debe ser mayor a 0\nIngrese nuevamente: ");
			}while(lon <= 0);
			printf("\n\nIngrese la altura del rectangulo: ");
			do
			{
				scanf("%f", &alt);
				if(alt <= 0)
					printf("La altura debe ser mayor a 0\nIngrese nuevamente: ");
			}while(alt <= 0);
			imprimirResultados(calcularAreaRectangulo(lon, alt), calcularPerimetroRectangulo(lon, alt));
			break;
		case 2:
			printf("Opcion de circulo seleccionada");
			printf("\n\nIngrese radio del circulo: ");
			do
			{
				scanf("%f", &rad);
				if(rad <= 0)
					printf("El radio debe ser mayor a 0\nIngrese nuevamente: ");
			}while(rad <= 0);
			imprimirResultados(calcularAreaCirculo(rad), calcularPerimetroCirculo(rad));
			break;
		default:
			printf("¡¡¡¡ERROR!!!!\n");
			break;
	}

	return 0;
}

float calcularAreaRectangulo(float l, float h)
{
	float a = l*h;

	return a;
}

float calcularPerimetroRectangulo(float l, float h)
{
	float p = 2*l + 2*h;

	return p;
}

float calcularDiagonalRectangulo(float a, float p)
{
	float d = sqrt((p/2)*(p/2) - 2*a);

	return d;
}

float calcularAreaCirculo(float r)
{
	float a = PI * r * r;

	return a;
}

float calcularPerimetroCirculo(float r)
{
	float p = 2 * r * PI;

	return p;
}

void imprimirResultados(float a, float p)
{
	float d;
	switch(op)
	{
		case 1:
			printf("\n\nEl area del rectangulo es: %.2f", a);
			printf("\n\nEl perimetro del rectangulo es: %.2f", p);
			d = calcularDiagonalRectangulo(a, p);
			printf("\n\nLa diagonal del rectangulo es: %.2f\n", d);
			break;
		case 2:
			printf("\n\nEl area del ciculo es: %.2f", a);
			printf("\n\nEl perimetro del ciculo es: %.2f\n", p);
			break;
		default:
			printf("¡¡¡¡ERROR!!!!\n");
			break;

	}

}




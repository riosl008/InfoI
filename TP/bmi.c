#include <stdio.h>

int main (void)
{
float peso, alt, bmi;

printf("Ingrese el peso: (Kg)\n");
scanf("%f", &peso);

printf("Ingrese la altura: (metros)\n");
scanf("%f", &alt);

bmi = peso / (alt * alt);

printf("Su indice de masa corporal es %.2f\n\n", bmi);

printf("\n\t\"TABLA\"\n");
printf("Índice\t\tCondición\n<18.5\t\tBajo peso\n18.5 a 24.9\tNormal\n25.0 a 29.9\tSobrepeso\n30.0 a 34.9\tObesidad grado I\n35.0 a 39.9\tObesidad grado II\n>=40.0\t\tObesidad grado III\n");

return 0;
}

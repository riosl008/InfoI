#include <stdio.h>

int main (void)
{
  int calif;
  char letra;

  printf("Ingresar la calificación: ");
  scanf("%d", &calif);

  if (calif >= 90)
    letra = 'A';
  else
    if ((calif >= 80) && (calif < 90))
      letra = 'B';
    else
      if ((calif >= 70) && (calif < 80))
        letra = 'C';
      else
        if ((calif >= 60) && (calif < 70))
          letra = 'D';
        else
	  if (calif < 60)
	    letra = 'F';


  printf("Calificación: %c\n", letra);

return 0;
}

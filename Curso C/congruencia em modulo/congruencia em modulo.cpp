#include<stdio.h>
#include<stdlib.h>
int main()
{
  int n,j,m,cont=0;
  printf("Digite um inteiro n:\n");
  scanf("%d",&n);

  printf("Digite um inteiro j:\n");
  scanf("%d",&j);

  printf("Digite um inteiro m:\n");
  scanf("%d",&m);

  printf("Os %d primeiros numeros congruente modulo m a j sao:\n",n);

  while(n!=0)
  {
      ++cont;
      if(cont%m == j%m)
      {
           printf("%d\n",cont);
           --n;
      }


  }

  system("pause");
  return 0;


}

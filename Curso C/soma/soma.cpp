#include<stdio.h>
#include<stdlib.h>
int main()
{
   int i=0,n,soma=0;
   printf("Digite um numero n: ");
   scanf("%d",&n);

   while(i<=n)
   {
       soma=soma + i;
       ++i;
   }

   printf("A soma dos n primeiros numeros inteiros e':%d\n",soma);
   system("pause");
   return 0;
}

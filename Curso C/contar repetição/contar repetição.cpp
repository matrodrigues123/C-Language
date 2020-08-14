#include<stdio.h>
#include<stdlib.h>
int main()
{
   int n,atual,anterior,cont=1,rep=0;
   printf("Digite o numero de termos:");
   scanf("%d",&n);

   printf("Digite os termos:");

   scanf("%d",&anterior);
   while(cont<n)
   {
       scanf("%d",&atual);
       ++cont;
       if(anterior == atual) ++rep;
       anterior = atual;
   }

   printf("O numero de segmentos de algarismos distintos digitados e':%d",n - rep);
}

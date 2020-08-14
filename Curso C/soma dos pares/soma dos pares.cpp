#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n,num=0,i=1,soma=0;
    printf("Digite um inteiro n:");
    scanf("%d",&n);

    while(i<n)
    {
       num=num + 2;
       soma=soma + num;
       ++i;

    }
    printf("A soma dos n primeiros numeros pares e':%d\n",soma);
    system("pause");
    return 0;
}

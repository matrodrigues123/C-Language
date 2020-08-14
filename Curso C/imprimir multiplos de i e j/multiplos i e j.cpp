#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n,i,j,num=0,contador=1;

    printf("Digite um inteiro positivo n:");
    scanf("%d",&n);

    printf("Digite um inteiro positivo i:");
    scanf("%d",&i);

    printf("Digite um inteiro positivo j:");
    scanf("%d",&j);

    while(contador<=n)
    {
       if(num%i==0 || num%j==0) printf("%d\n",num);
       num=num + 1;
       ++contador;
       if(num%i!=0 && num%j!=0) --contador;

    }

    system("pause");
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
int main()
{
    int num,result=1,exp;

    printf("Digite um numero inteiro: ");
    scanf("%d",&num);

    printf("Digite um numero expoente: ");
    scanf("%d",&exp);

    while(exp!=0)
    {
        result=result*num;
        --exp;
    }

    printf("O inteiro elevado ao expoente e' igual a:%d\n",result);

    system("pause");

    return 0;


}

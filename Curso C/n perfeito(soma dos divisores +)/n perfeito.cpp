#include<stdio.h>
#include<stdlib.h>
int main()
{
    int num,divisor=1,soma=0;
    printf("Digite um inteiro:\n");
    scanf("%d",&num);


    while(divisor<num)
    {
        if(num%divisor==0) soma=soma+divisor;
        ++divisor;

    }
    if(soma==num) printf("O numero e' perfeito\n");
    else printf("O numero nao e perfeito\n");

    system("pause");
    return 0;


}

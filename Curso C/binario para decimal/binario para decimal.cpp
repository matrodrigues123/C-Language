#include<stdio.h>
#include<stdlib.h>
int main()
{
    int num,pot2=1,result=0;
    printf("Digite um numero na base binaria:");
    scanf("%d",&num);

    printf("O numero dado na base 10 e':%d",num);

    while(num!=0)
    {
        result = result + num%10*pot2;
        num = num/10;
        pot2=2*pot2;

    }

    printf("O numero na base 10 e':%d",result);

}

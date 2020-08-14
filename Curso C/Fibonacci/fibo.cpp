#include<stdio.h>
#include<stdlib.h>
int main()
{
    int num1=1,num2=1,numn,contador=3,n;
    printf("Esse programa calcula o enesimo termo da sequencia de Fibonacci\n");

    printf("Digite a ordem do enesimo termo:");
    scanf("%d",&n);

    if(n<3)
    {
        printf("Errado, a ordem deve ser maior ou igual a 3. Digite novamente:");
        scanf("%d",&n);
    }

    while(contador<=n)
    {
        ++contador;
        numn = num1 + num2;
        num1 = num2;
        num2 = numn;
    }
    printf("O enesimo termo e':%d\n",numn);


    system("pause");
    return 0;

}

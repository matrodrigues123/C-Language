#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n,i=1;
    printf("Digite um inteiro n: ");
    scanf("%d",&n);

    while(i*(i+1)*(i+2)<n)
    {
        i++;
    }

    if (i*(i+1)*(i+2)==n) printf("O numero 'n' e' triangular\n");
    else printf("O numero 'n' nao e' triangular\n");

    system("pause");
    return 0;

}

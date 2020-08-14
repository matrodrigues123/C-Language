#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n,divisor,cont=0;
    printf("Digite um numero: ");
    scanf("%d",&n);

    for(divisor=1;divisor<=n;++divisor)
    {
        if(n%divisor == 0) ++cont;
    }

    if(cont == 2) printf("O numero e' primo\n");
    else printf("O numero nao e' primo\n");

    printf("Vai toma no cu");

    system ("pause");
    return 0;

}

#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n,num=1,i=1;
    printf("Digite um inteiro n:");
    scanf("%d",&n);

    printf("%d\n",num);

    while(i<n)
    {
       num=num + 2;
       ++i;
       printf("%d\n",num);

    }

    system("pause");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
    
    FILE * entrada;
    entrada = fopen("teste.txt","r");

    int a,b,c;
    int numA,numB;
    char numC;

    a = fscanf (entrada,"%d",&numA);
    b = fscanf (entrada,"%d",&numB);
    c = fscanf (entrada,"%c",&numC);

    printf ("%d %d %c",a, b, numC);


}
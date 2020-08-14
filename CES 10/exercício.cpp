#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 0;
    int maior,numE;
    FILE * entrada;

    entrada = fopen("entrada.txt","r");

    while (i < 500)
    {
        fscanf (entrada, "%d", &numE);

        if (i == 0 || maior < numE)
        {
            maior = numE;
        }

        i++;
    }

    printf ("O maior e': %d",maior);
    


    

    
}
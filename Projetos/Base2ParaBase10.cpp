#include <stdio.h>
#include <math.h>

int main ()
{
    int bin,num,sum = 0,i = 0;

    scanf ("%d",&bin);

    while (bin > 0)
    {
        num = bin % 10;
        sum += num*pow(2,i);
        ++i;
        bin = bin/10;
        
    }

    printf ("%d",sum);


}
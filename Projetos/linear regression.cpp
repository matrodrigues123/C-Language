#include <stdio.h>

int main()
{
    int i,n;
    double sumx = 0,sumy = 0,sumxx = 0,sumxy = 0;
    printf ("y = ax + b\n");

    printf ("Digite o numero de dados experimentais(coordenadas x,y)\n");
    scanf ("%d",&n);
    double x[n],y[n];
    double a,b;

    for (i = 0; i < n; i++)
    {
        printf ("digite o termo x%d\n",i+1);
        scanf ("%lf",&x[i]);
        printf ("digite o termo y%d\n",i+1);
        scanf ("%lf",&y[i]);

        sumx += x[i];
        sumy += y[i];
        sumxx += x[i] * x[i];
        sumxy += x[i] * y[i];

        printf ("\n");
    }
    
    a = (n * sumxy - sumx * sumy)/(n * sumxx - sumx * sumx);
    b = (sumy * sumxx - sumxy * sumx)/(n * sumxx - sumx * sumx);
    printf ("y = %lfx + %lf",a,b);
}
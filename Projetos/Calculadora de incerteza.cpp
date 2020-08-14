#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main ()
{   
    char type[20];
    printf ("Digite soma ou multiplicacao\n");
    scanf ("%s",&type);
    if (type[0] == 'm')
    {
        printf ("(dx/x)^2 = (dv1/v1)^2 + (dv2/v2)^2 + ... + (dvn/vn)^2\n");

        int n,i;
        
        double dx,x,sum = 0;
        printf ("Digite o valor x\n");
        scanf ("%lf",&x);

        printf ("\n");

        printf ("Digite o numero n de termos\n");
        scanf ("%d",&n);
        double incert[n];
        double values[n];

        printf ("\n");

        for (i = 0;i < n;++i)
        {
            printf ("Digite o valor %d\n",i+1);
            scanf ("%lf",&values[i]);

            printf ("Digite sua incerteza\n");
            scanf ("%lf",&incert[i]);

            printf ("\n");

            sum += (incert[i]/values[i]) * (incert[i]/values[i]);
        }


        dx = sqrt(x * x * sum);

        printf ("A incerteza do valor x e': %lf",dx);
    }

    if (type[0] == 's')
    {
        printf ("dx^2 = dv1^2 + dv2^2 + ... + dvn^2");
        double dx,sum = 0;
        int n,i;

        printf ("\n");

        printf ("Digite o numero n de termos\n");
        scanf ("%d",&n);
        double incert[n];

        printf ("\n");

        for (i = 0;i < n;++i)
        {
            printf ("Digite a incerteza do valor %d \n",i+1);
            scanf ("%lf",&incert[i]);

            sum += incert[i] * incert[i];

            printf ("\n");
        }

        dx = sqrt(sum);

        printf ("A incerteza do valor x e' :%lf\n",dx);
    }

    system ("pause");
    return 0; 
}
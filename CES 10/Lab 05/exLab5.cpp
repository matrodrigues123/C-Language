#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    //Está dando um erro muito estranho, retornando coeficiente lixo especificamente quando há termo máximo de grau 5 na soma de polinomios

    int i,k,j,quant,verify;
    char tipo;
    float coef[7];
    float sumCoef[7] = {0};
    float derivada[7];

    float valorX;
    float valorPol;

    float maiorExpo = 0;
    


    FILE * entrada;
    entrada = fopen("entrada5.txt","r");

    quant = 1;
    i = 0;
    valorPol = 0;

    verify = fscanf (entrada, "%c", &tipo);
    while (tipo != 'F')
    {
        if (tipo == 's' || tipo == 'S')
        {
            //Esse loop possui um problema, não funciona quando só uma operação é feita 
            tipo = 'n';
            while (tipo != 's' && tipo != 'S' && tipo != 'd' && tipo != 'D' && tipo != 'v' && tipo != 'V')
            {
                //Armazenar os coeficientes do polinomio enquanto não chega no ponto e vírgula 
                //Ao chegar no ponto e vírgula, são armazenados os coeficientes de um novo polinômio
                if (quant > 0)
                {
                    quant = fscanf (entrada,"%f",&coef[i]);
                    sumCoef[i] += coef[i];
                    coef[i] = 0;
                    i++;
                }
                else
                {
                    i = 0;
                    quant = 1;
                }
                
                verify = fscanf (entrada, "%c", &tipo);
                
            }
            


            for (k = 7; k >= 0; k--)
            {
                //Verifica se o termo analisado é o de maior expoente do polinômio
                //'maiorExpo' é sempre inicializada com o grau 0
                if (k > maiorExpo && sumCoef[k] != 0)
                {
                    maiorExpo = k;
                }
                
                if (sumCoef[k] != 0)
                {

                    if (k == maiorExpo)
                    {
                        switch (k)
                        {
                            case 0:
                                printf ("%g ",sumCoef[k]);
                                break;

                            case 1:
                                printf ("%gx ",sumCoef[k]);
                                break;
                            
                            default:
                                printf ("%gx^%d ",sumCoef[k],k);
                                break;
                        }
                    }
                    else if (sumCoef[k] > 0)
                    {
                        switch (k)
                        {
                            case 0:
                                printf (" + %g ",sumCoef[k]);
                                break;

                            case 1:
                                printf (" + %gx ",sumCoef[k]);
                                break;
                            
                            default:
                                printf (" + %gx^%d ",sumCoef[k],k);
                                break;
                        }
                    }
                    else
                    {
                        printf ("%gx^%d ",sumCoef[k],k);
                    }
                    
                }
                
                
            }
            if (maiorExpo == 0 && sumCoef[0] == 0)
            {
                printf ("0");
            }

            i = 0;
            printf ("\n");
        }
        if (tipo == 'd' || tipo == 'D')
        {
            while (tipo != ';')
            {
                //Armazenar os coeficientes do polinomio até chegar no ponto e vírgula
                //Ao chegar no ponto e vírgula, calcula-se a derivada
                quant = fscanf (entrada,"%f",&coef[i]);
                derivada[i] = i * coef[i];
                coef[i] = 0;
                i++;

                verify = fscanf (entrada, "%c", &tipo);
                 
            }

            for (k = 7; k >= 0; k--)
            {
                if (k > maiorExpo && derivada[k] != 0)
                {
                    maiorExpo = k;
                }
                
                if (derivada[k] != 0)
                {

                    if (k == maiorExpo)
                    {
                        switch (k - 1)
                        {
                            case 0:
                                printf ("%g ",derivada[k]);
                                break;

                            case 1:
                                printf ("%gx ",derivada[k]);
                                break;
                            
                            default:
                                printf ("%gx^%d ",derivada[k],k - 1);
                                break;
                        }
                    }
                    else if (derivada[k] > 0)
                    {
                        switch (k - 1)
                        {
                            case 0:
                                printf (" + %g ",derivada[k]);
                                break;

                            case 1:
                                printf (" + %gx ",derivada[k]);
                                break;
                            
                            default:
                                printf (" + %gx^%d ",derivada[k],k - 1);
                                break;
                        }
                    }
                    else
                    {
                        printf ("%gx^%d ",derivada[k],k - 1);
                    }
                    
                }
                
                
            }

            if (maiorExpo == 0 && derivada[0] == 0)
            {
                printf ("0");
            }

            i = 0;
            printf ("\n");
        }
        if (tipo == 'v' || tipo == 'V')
        {
            //Armazena os coeficientes do polinômio até chegar no ponto e vírgula
            while (tipo != ';')
            {
                quant = fscanf (entrada,"%f",&coef[i]);
                i++;
                verify = fscanf (entrada, "%c", &tipo);
            }


            //Armazena o valor a ser substituido no polinômio
            quant = fscanf (entrada, "%f", &valorX);

            for (j = i; j >= 0; j--)
            {
                valorPol += coef[j] * pow (valorX,j);
            }

            printf ("%g",valorPol);
            
            i = 0;
            printf ("\n");
        }
        
        
        verify = fscanf (entrada, "%c", &tipo);

    }

    fclose (entrada);
    return 0;
}
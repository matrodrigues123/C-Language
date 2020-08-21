/*  Matheus Rodrigues Araújo                        */
/*  Turma 24.1                                      */
/*  Exercício 5 : Polinômios                        */
/*                                                  */
/*  Programa compilado com Code Blocks 17.12        */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{

    //Declaração de variáveis
    int i,j,k,cont; //Variáveis referentes à contagem
    int quant; //Variável referente ao retorno de scanf dos coeficientes
    int quantTeste; //Variável referente ao retorno de scanf do teste 
    char pontoVirg; //Variável presente apenas para detectar se há ponto e vírgula
    char operacao;
    float coef[8] = {0}; 
    float sumCoef[8] = {0};
    float derivada[8] = {0};
    float teste; //Armazena o float apenas para testar se há um novo polinômio
    float valorX; 
    float valorPol;
    float maiorExpo;

    //Declaração das variáveis e explicitação do caminho para os arquivos de entrada e saída
    FILE * entrada;
    FILE * saida;
    entrada = fopen("C:\\Lab5\\entrada5.txt", "r");
    saida = fopen("C:\\Lab5\\Matheus_Rodrigues5.txt", "w");
    
    //Inicialização de algumas variáveis
    cont = 1;
    quant = 1;
    quantTeste = 1;
    i = 0;
    valorPol = 0;
    maiorExpo = 0;
    pontoVirg = ';';
    
    //Identificar o tipo de operação
    fscanf (entrada, "%c", &operacao);

    //Enquanto não for identificado o 'F' no arquivo de entrada, fazer
    while (operacao != 'F')
    {
        
        //Para a operação de soma, fazer
        if (operacao == 's' || operacao == 'S')
        {
            //Enquanto houver float no início e ponto e vírgula no final, fazer
            while (pontoVirg == ';' && quantTeste == 1)
            {
                //Armazena os coeficientes do polinômio até alcançar o ponto e vírgula
                while (quant > 0)
                {
                    quant = fscanf (entrada, " %f", &coef[i]);
                    sumCoef[i] += coef[i];
                    coef[i] = 0;
                    //Garante que o grau máximo do polinômio é 7
                    if (i < 7)
                    {
                        i++;
                    }
                    
                }

                //Verifica se há ponto e vírgula seguido de float
                fscanf (entrada, " %c", &pontoVirg);
                quantTeste = fscanf (entrada, "%f", &teste);

                if (quantTeste == 1)
                {
                    sumCoef[0] += teste; //Casa haja um próximo polinômio, seu 'coef[0]' já foi armazenado em 'teste'
                    i = 1; //O loop anterior deve ser repetido a partir do 'coef[1]'
                    quant = 1;
                }
                else
                {
                    i = 0;
                    quant = 1;
                }
                
            }
            
            fprintf (saida,"%3d: ",cont);

            //Escreve a resposta no arquivo de saída
            for (k = 8; k >= 0; k--)
            {
                //Verifica se o termo analisado é o de maior expoente do polinômio
                //'maiorExpo' é sempre inicializada com o grau 0
                if (k > maiorExpo && sumCoef[k] != 0)
                {
                    maiorExpo = k;
                }
                //Garante que no arquivo de saída só aparece os termos com coeficiente diferente de zero
                if (sumCoef[k] != 0)
                {
                    //Garante que o termo de maior expoente vem primeiro e não acompanhado de '+', caso seja positivo
                    if (k == maiorExpo)
                    {
                        switch (k)
                        {
                            case 0:
                                fprintf (saida, "%g",sumCoef[k]);
                                break;

                            case 1:
                                fprintf (saida, "%gx",sumCoef[k]);
                                break;
                            
                            default:
                                fprintf (saida, "%gx^%d",sumCoef[k],k);
                                break;
                        }
                    }
                    else if (sumCoef[k] > 0)
                    {
                        switch (k)
                        {
                            case 0:
                                fprintf (saida, " + %g",sumCoef[k]);
                                break;

                            case 1:
                                fprintf (saida, " + %gx",sumCoef[k]);
                                break;
                            
                            default:
                                fprintf (saida, " + %gx^%d",sumCoef[k],k);
                                break;
                        }
                    }
                    //Garante espaçamento adequado para o sinal em coeficientes negativos
                    else
                    {
                        fprintf (saida, " - %gx^%d",-sumCoef[k],k);
                    }
                    
                }
                
            }
            //Escreve zero no arquivo de saída para o polinômio nulo
            if (maiorExpo == 0 && sumCoef[0] == 0)
            {
                fprintf (saida, "0");
            }

            //Variáveis reinicializadas em preparação para o próximo loop e contagem
            i = 0;
            maiorExpo = 0;
            pontoVirg = ';';
            quantTeste = 1;
            for (k = 0; k < 8; k++)
            {
                sumCoef[k] = 0;
            }
            cont++;

            fprintf (saida, "\n");
        }

        //Para a operação de derivada, fazer
        if (operacao == 'd' || operacao == 'D')
        {
            while (operacao != ';')
            {
                //Armazenar os coeficientes do polinomio até chegar no ponto e vírgula
                //Para cada termo, obtém-se a derivada
                quant = fscanf (entrada,"%f",&coef[i]);
                derivada[i] = i * coef[i];
                
                coef[i] = 0;
                i++;

                fscanf (entrada, "%c", &operacao);
                 
            }

            //Garante que o termo de expoente 7 não apareça na derivada
            derivada[8] = 0;

            fprintf (saida, "%3d: ", cont);
            //Análogo ao caso anterior
            for (k = 8; k >= 0; k--)
            {
                if (k > maiorExpo && derivada[k] != 0)
                {
                    maiorExpo = k;
                }
                
                if (derivada[k] != 0)
                {
                    //A operação é efetuada com 'k - 1' ao invés de 'k', pela condição da derivada
                    if (k == maiorExpo)
                    {
                        switch (k - 1)
                        {
                            case 0:
                                fprintf (saida, "%g",derivada[k]);
                                break;

                            case 1:
                                fprintf (saida, "%gx",derivada[k]);
                                break;
                            
                            default:
                                fprintf (saida, "%gx^%d",derivada[k],k - 1);
                                break;
                        }
                    }
                    else if (derivada[k] > 0)
                    {
                        switch (k - 1)
                        {
                            case 0:
                                fprintf (saida, " + %g",derivada[k]);
                                break;

                            case 1:
                                fprintf (saida, " + %gx",derivada[k]);
                                break;
                            
                            default:
                                fprintf (saida, " + %gx^%d",derivada[k],k - 1);
                                break;
                        }
                    }
                    else
                    {
                        fprintf (saida, " - %gx^%d",-derivada[k],k - 1);
                    }
                    
                }
                
                
            }

            if (maiorExpo == 0 && derivada[0] == 0)
            {
                fprintf (saida, "0");
            }

            //Variáveis reinicializadas em preparação para o próximo loop e contagem
            i = 0;
            maiorExpo = 0;
            for (k = 0; k < 8; k++)
            {
                derivada[k] = 0;
            }
            cont++;

            fprintf (saida, "\n");
        }

        //Para a operação de calcular o valor em um dado ponto, fazer
        if (operacao == 'v' || operacao == 'V')
        {
            //Armazena os coeficientes do polinômio até chegar no ponto e vírgula
            while (operacao != ';')
            {
                quant = fscanf (entrada,"%f",&coef[i]);
                i++;
                fscanf (entrada, "%c", &operacao);
            }


            //Armazena o valor a ser substituido no polinômio
            quant = fscanf (entrada, "%f", &valorX);

            //Calcula o valor do polinômio no ponto obtido anteriormente
            for (j = i; j >= 0; j--)
            {
                valorPol += coef[j] * pow (valorX,j);
                coef[j] = 0;
            }

            //Escreve a resposta no arquivo de saída
            fprintf (saida, "%3d: ",cont);
            fprintf (saida, "%g",valorPol);
            
            //Variáveis reinicializadas em preparação para o próximo loop e contagem
            i = 0;
            valorPol = 0;
            maiorExpo = 0;
            cont++;

            fprintf (saida, "\n");
        }
        
        
        fscanf (entrada, "%c", &operacao);

    }

    //Fecha os arquivos de entrada e saída
    fclose (entrada);
    fclose (saida);

    //Pausa + fim do programa
    system ("pause");
    return 0;
}
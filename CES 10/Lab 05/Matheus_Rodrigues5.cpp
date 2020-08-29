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
    
    int i,k,cont, //Variáveis referentes à contagem
        quant, //Variável referente ao retorno de scanf dos coeficientes
        quantTeste; //Variável referente ao retorno de scanf do teste 

    char pontoVirg, 
         operacao;

    float entCoef[8] = {0}, //Vetor que armazena os coeficientes da entrada
          resultCoef[8] = {0}, //Vetor que armazena o coeficientes do polinômio resultante das operações
          teste, //Armazena o float apenas para testar se há um novo polinômio
          valorX, 
          valorPol,
          maiorExpo;

    FILE * entrada,
         * saida;


    //Explicitação do caminho para os arquivos de entrada e saída
    entrada = fopen("C:\\Lab5\\entrada5.txt", "r");
    saida = fopen("C:\\Lab5\\Matheus_Rodrigues5.txt", "w");
    

    //Inicialização de algumas variáveis
    i = 0;
    cont = 1;
    quant = 1;
    quantTeste = 1;
    pontoVirg = ';';
    valorPol = 0;
    maiorExpo = 0;
    

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
                    quant = fscanf (entrada, " %f", &entCoef[i]);
                    resultCoef[i] += entCoef[i];
                    entCoef[i] = 0;

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
                    resultCoef[0] += teste; //Casa haja um próximo polinômio, seu 'coef[0]' já foi armazenado em 'teste'
                    i = 1; //O loop anterior deve ser repetido a partir do 'coef[1]'
                }
                else
                {
                    i = 0;
                }


                //Reinicialização da variável
                quant = 1;
            }
            

            fprintf (saida,"%3d: ",cont);


            //Escreve a resposta no arquivo de saída
            for (k = 8; k >= 0; k--)
            {
                //Verifica se o termo analisado é o de maior expoente do polinômio
                //'maiorExpo' é sempre inicializada com o grau 0
                if (k > maiorExpo && resultCoef[k] != 0)
                {
                    maiorExpo = k;
                }
                //Garante que no arquivo de saída só aparece os termos com coeficiente diferente de zero
                if (resultCoef[k] != 0)
                {
                    //Garante que o termo de maior expoente vem primeiro e não acompanhado de '+', caso seja positivo
                    //Caso seja negativo, garante espaçamento adequado
                    if (k == maiorExpo)
                    {
                        if (resultCoef[k] > 0)
                        {
                            switch (k)
                            {
                                case 0:
                                    fprintf (saida, "%g",resultCoef[k]);
                                    break;

                                case 1:
                                    fprintf (saida, "%gx",resultCoef[k]);
                                    break;
                                
                                default:
                                    fprintf (saida, "%gx^%d",resultCoef[k],k);
                                    break;
                            }
                        }
                        else
                        {
                            fprintf (saida, "- %gx^%d",-resultCoef[k],k);
                        }
                    }
                    else if (resultCoef[k] > 0)
                    {
                        switch (k)
                        {
                            case 0:
                                fprintf (saida, " + %g",resultCoef[k]);
                                break;

                            case 1:
                                fprintf (saida, " + %gx",resultCoef[k]);
                                break;
                            
                            default:
                                fprintf (saida, " + %gx^%d",resultCoef[k],k);
                                break;
                        }
                    }
                    else
                    {
                        fprintf (saida, " - %gx^%d",-resultCoef[k],k);
                    }
                    
                }
                
            }
            //Escreve zero no arquivo de saída para o polinômio nulo
            if (maiorExpo == 0 && resultCoef[0] == 0)
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
                resultCoef[k] = 0;
            }
            cont++;


            fprintf (saida, "\n");
        }

        //Para a operação de resultCoef, fazer
        if (operacao == 'd' || operacao == 'D')
        {
            while (operacao != ';')
            {
                //Armazenar os coeficientes do polinomio até chegar no ponto e vírgula
                //Para cada termo, obtém-se a resultCoef
                quant = fscanf (entrada,"%f",&entCoef[i]);
                resultCoef[i] = i * entCoef[i];
                
                entCoef[i] = 0;
                i++;

                fscanf (entrada, "%c", &operacao);
                 
            }


            //Garante que o termo de expoente 7 não apareça na resultCoef
            resultCoef[8] = 0;


            fprintf (saida, "%3d: ", cont);


            //Análogo ao caso anterior
            for (k = 8; k >= 0; k--)
            {
                if (k > maiorExpo && resultCoef[k] != 0)
                {
                    maiorExpo = k;
                }
                
                if (resultCoef[k] != 0)
                {
                    //A operação é efetuada com 'k - 1' ao invés de 'k', pela condição da resultCoef
                    if (k == maiorExpo)
                    {
                        if (resultCoef [k] > 0)
                        {
                                switch (k - 1)
                            {
                                case 0:
                                    fprintf (saida, "%g",resultCoef[k]);
                                    break;

                                case 1:
                                    fprintf (saida, "%gx",resultCoef[k]);
                                    break;
                                
                                default:
                                    fprintf (saida, "%gx^%d",resultCoef[k],k - 1);
                                    break;
                            }
                        }
                        else
                        {
                            fprintf (saida, "- %gx^%d",-resultCoef[k],k - 1);
                        }
                    }
                    else if (resultCoef[k] > 0)
                    {
                        switch (k - 1)
                        {
                            case 0:
                                fprintf (saida, " + %g",resultCoef[k]);
                                break;

                            case 1:
                                fprintf (saida, " + %gx",resultCoef[k]);
                                break;
                            
                            default:
                                fprintf (saida, " + %gx^%d",resultCoef[k],k - 1);
                                break;
                        }
                    }
                    else
                    {
                        fprintf (saida, " - %gx^%d",-resultCoef[k],k - 1);
                    }
                    
                }
            }
            if (maiorExpo == 0 && resultCoef[0] == 0)
            {
                fprintf (saida, "0");
            }


            //Variáveis reinicializadas em preparação para o próximo loop e contagem
            i = 0;
            maiorExpo = 0;
            for (k = 0; k < 8; k++)
            {
                resultCoef[k] = 0;
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
                quant = fscanf (entrada,"%f",&entCoef[i]);
                i++;
                fscanf (entrada, "%c", &operacao);
            }


            //Armazena o valor a ser substituido no polinômio
            quant = fscanf (entrada, "%f", &valorX);


            //Calcula o valor do polinômio no ponto obtido anteriormente
            for (k = i; k >= 0; k--)
            {
                valorPol += entCoef[k] * pow (valorX,k);
                entCoef[k] = 0;
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
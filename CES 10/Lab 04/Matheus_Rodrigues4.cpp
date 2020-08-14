/*  Matheus Rodrigues Araújo                        */
/*  Turma 24.1                                      */
/*  Exercício 4 : Contagem de Dias                  */
/*                                                  */
/*  Programa compilado com Code Blocks 17.12        */


#include <stdio.h>
#include <stdlib.h>

int main()
{
    //Declaração de variáveis
    int i, quant; //Contagem de casos
    int diaI,mesI,anoI; //Data inicial da entrada
    int diaF,mesF,anoF; //Data final da entrada
    int diasTot; //Número total de dias
    FILE * entrada;
    FILE * saida;

    //Abrir os arquivos de entrada e saída
    entrada = fopen("C:\\Lab4\\entrada4.txt", "r");
    saida = fopen("C:\\Lab4\\Matheus_Rodrigues4.txt", "w");

    //Ler o número 'quant' de vezes em que
    //uma linha da entrada será lida
    fscanf (entrada, "%d", &quant);

    printf("\n");

    //Inicialização de algumas variáveis
    diasTot = 0;
    i = 1;

    //Escreve um mensagem inicial no arquivo
    fprintf (saida, "  Esse é o Lab 04 : Contagem de Dias.\n");
    fprintf (saida, "  O programa calcula o número de dias entre duas datas lidas.\n");
    fprintf (saida,"  Para efeitos de cálculo, são considerados os anos bissextos.\n");
    fprintf (saida, "  ----\n");

    //Para cada um dos 'quant' casos, fazer
    while (i <= quant)
    {
        //Leitura de uma linha da entrada
        fscanf (entrada, "%d", &diaI);
        fscanf (entrada, "%d", &mesI);
        fscanf (entrada, "%d", &anoI);
        fscanf (entrada, "%d", &diaF);
        fscanf (entrada, "%d", &mesF);
        fscanf (entrada, "%d", &anoF);

        //Verifica se o mês final é maior
        if (mesF > mesI)
        {
            //Conta o numero de dias até o fim do mesI
            if (mesI == 1 || mesI == 3 || mesI == 5 || mesI == 7 || mesI == 8 || mesI == 10 || mesI == 12)
            {
                diasTot += 31 - diaI;
            }
            else if (mesI == 2)
            {
                //Verificar se o ano é bissexto para definir a quantidade de dias do mês
                if ((anoI%4 == 0 && anoI%100 != 0) || (anoI%4 == 0 && anoI%100 == 0 && anoI%400 == 0))
                {
                    diasTot += 29 - diaI;
                }
                else
                {
                    diasTot += 28 - diaI;
                }
            }
            else
            {
                diasTot += 30 - diaI;
            }

            //Passagem de mês
            mesI = mesI + 1;

            //Dia passa a ser zero matematicamente, apenas para reinicilizar a contagem
            diaI = 0;
        }

        //Verifica se o ano final é maior
        if (anoF > anoI)
        {
            //Conta o numero de dias até o fim do ano
            while (mesI <= 12)
            {
                //Verifica o numero de dias até o fim do mesI
                if (mesI == 1 || mesI == 3 || mesI == 5 || mesI == 7 || mesI == 8 || mesI == 10 || mesI == 12)
                {
                    diasTot += 31;
                }
                else if (mesI == 2)
                {
                    //Verifica se o ano é bissexto para definir a quantidade de dias do mês
                    if ((anoI%4 == 0 && anoI%100 != 0) || (anoI%4 == 0 && anoI%100 == 0 && anoI%400 == 0))
                    {
                        diasTot += 29;
                    }
                    else
                    {
                        diasTot += 28;
                    }
                }
                else
                {
                    diasTot += 30;
                }

                //Passagem de mês
                mesI = mesI + 1;
            }

            //Passagem de ano
            anoI = anoI + 1;

            //Mês passa a ser um com início do novo ano
            mesI = 1;
        }

        //Verifica o número de dias até o ano final, não ocorrendo caso seja o mesmo ano
        while (anoI < anoF)
        {
            //Verifica se o ano é bissexto para contagem dos dias
            if ((anoI%4 == 0 && anoI%100 != 0) || (anoI%4 == 0 && anoI%100 == 0 && anoI%400 == 0))
            {
                diasTot += 366;
            }
            else
            {
                diasTot += 365;
            }

            //Passagem de ano
            anoI = anoI + 1;
        }

        //Conta os dias até o mês desejado no ano final, não ocorrendo caso seja o mesmo mês
        while (mesI < mesF)
        {
            if (mesI == 1 || mesI == 3 || mesI == 5 || mesI == 7 || mesI == 8 || mesI == 10 || mesI == 12)
            {
                diasTot += 31;
            }
            else if (mesI == 2)
            {
                //Verifica se o ano é bissexto para definir a quantidade de dias do mês
                if ((anoI%4 == 0 && anoI%100 != 0) || (anoI%4 == 0 && anoI%100 == 0 && anoI%400 == 0))
                {
                    diasTot += 29;
                }
                else
                {
                    diasTot += 28;
                }
            }
            else
            {
                diasTot += 30;
            }

            //Passagem de mês
            mesI = mesI + 1;
        }
        //Conta os dias até o dia dejesado no ano final
        diasTot += diaF - diaI;

        //Escreve o valor no arquivo de saída
        fprintf (saida,"%4d:%8d dias. \n",i,diasTot);

        //Quantidade total de dias é zerada em preparação pra o próximo loop
        diasTot = 0;

        //Contagem de casos
        i++;

    }


    //Fecha os arquivos + pausa
    fclose (entrada);
    fclose (saida);
    system ("pause");


    //Finalização
    return 0;

}

/*  Matheus Rodrigues Araújo                 */
/*  Turma 24.1                               */
/*  Exercício 3: Conversor de Medidas        */
/*                                           */
/*  Programa compilado com Code Blocks 17.12 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Declaração de variáveis
    float numE;
    int i,n,contK,contM,contC;
    int numS;
    int maiorK,menorC;
    int polegada, pe, jarda, milha;
    char unidade;
    FILE * entrada;
    FILE * saida;


    // Abrir arquivos de entrada e saída
    entrada = fopen("entrada3.txt","r");
    saida = fopen("Matheus_Rodrigues3.txt","w");


    // Escrever a mensagem inicial no arquivo
    fprintf (saida,"-------------------------------------- \n          PROGRAMA CONVERSOR          \n      Exemplo de arquivo de saida     \n--------------------------------------\n");


    // Atribuição inicial para algumas variáveis
    i = 1;
    contK = 0;
    contM = 0;
    contC = 0;
    maiorK = 0;


    // Ler a quantidade n de casos
    fscanf (entrada,"%d", &n);


    // Para cada um dos n casos, fazer:
    while (i <= n)
    {
        // Ler um float e um char com a unidade
        fscanf (entrada, "%f", &numE);
        fscanf (entrada, "%c", &unidade);


        // Se unidade m (metros)
        if (unidade == 'M' || unidade == 'm')
        {
            // Converter distancia
            milha = (100 * numE)/(2.54 * 12 * 3 * 1760);
            jarda = ((100 * numE)/(2.54 * 12 * 3 * 1760) - milha) * 1760;
            pe = ((((100 * numE)/(2.54 * 12 * 3 * 1760) - milha) * 1760) - jarda) * 3;
            polegada = ((((((100 * numE)/(2.54 * 12 * 3 * 1760) - milha) * 1760) - jarda) * 3) - pe) * 12;


            // Escrever o valor no arquivo
            fprintf (saida,"%.2f metros = \n %8d milhas + \n %8d jardas + \n %8d pes    + \n %8d polegadas \n\n",numE,milha,jarda,pe,polegada);


            // Contar termos
            contM++;
            i++;
        }


        // Se unidade k (kilogramas)
        if (unidade == 'K' || unidade == 'k')
        {
            // Converter massa
            numS = numE/0.453592;


            // Escrever o valor no arquivo
            fprintf (saida, "%.2f kilogramas = \n %8d libras \n\n",numE,numS);


            // Verifica se é a maior ate o momento
            if (numS >= maiorK)
            
                maiorK = numS;
            

            // Contar termos
            contK++;
            i++;
        }


        // Se unidade c (celsius)
        if (unidade == 'C' || unidade == 'c')
        {
            // Converter a temperatura
            numS = (9 * numE)/5 + 32;


            // Escrever o valor no arquivo
            fprintf (saida, "%.2f graus Celsius = \n %8d graus Fahrenheit \n\n",numE,numS);


            // Verifica se é a menor ate o momento, 
            // garantindo que menorC é inicilizado com o primeiro valor de temperatura da entrada 
            if (contC == 0 || numS <= menorC)
            
                menorC = numS;


            // Contar termos
            contC++;
            i++;
        }

    }


    // Ao terminar o arquivo de entrada,
    // escrever as informações (a), (b) e (c) 
    fprintf (saida, "--------------------------------------\n");
    fprintf (saida,"(a) Quantidade de casos de cada tipo: \n    Massa      : %3d vezes. \n    Temperatura: %3d vezes. \n    Distancia  : %3d vezes. \n\n",contK,contC,contM);


    // Verificar se a contagem dos casos não é zero,
    // escrevendo no arquivo seu valor em seguida
    if (contK != 0)
    
        fprintf (saida,"(b) Qual a maior massa: \n    %d libras. \n\n",maiorK);
    
    else
    
        fprintf (saida,"(b) Qual a maior massa: \n    Não ocorre. \n\n");
    


    if (contC != 0)
    
        fprintf (saida,"(c) Qual a menor temperatura: \n    %d graus Fahrenheit. \n\n",menorC);
    
    else
    
        fprintf (saida,"(c) Qual a menor temperatura: \n    Não ocorre \n\n");
    

    // Mensagem final na tela + Pausa
    fprintf (saida, "--------------------------------------\nFim do Arquivo.");
    system ("pause");


    //Fechar arquivos de entrada e saida
    fclose (entrada);
    fclose (saida);


    //finalizar
    return 0;

}
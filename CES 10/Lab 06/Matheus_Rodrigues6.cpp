/*  Matheus Rodrigues Araújo                        */
/*  Turma 24.1                                      */
/*  Exercício 6 : Strings                           */
/*                                                  */
/*  Programa compilado com Code Blocks 17.12        */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FALSE 0
#define TRUE 1
#define boolean int

int main()
{
    //Declaração de variáveis
    char localArq[30],
         localArqAnt[30],
         nomeArq[15],
         nomeArqAnt[15],
         palavraEnt[15],
         palavra[15],
         marcas [80]; //char que armazena as marcações no arquivo, como "--" e "|"
    
    int cont = 0,
        i;

    boolean rptLoc = FALSE, //booleans referentes à repetição de local e nome do arquivo
            rptNom = FALSE;

    FILE * entrada,
         * saida,
         * local;
    

    //Abertura dos arquivos de entrada e saída
    entrada = fopen("C:\\Lab6\\entrada6.txt", "r");
    saida = fopen("C:\\Lab6\\Matheus_Rodrigues6.txt", "w");


    //Pula as primeiras linhas
    for (i = 0; i < 7; i++)
    {
        fgets (marcas, 80, entrada);
    }


    //Escreve as mensagens iniciais no arquivo
    fprintf (saida," Esse é o resultado da contagem\n");
    fprintf (saida," O programa lê um arquivo de entrada contendo o local e nome do arquivo\n");
    fprintf (saida," Para palavras em um mesmo local e arquivo, não é repetido o endereço na saída.\n");
    fprintf (saida," ----------------------------------------\n");

    //Armazena o "|" para que o próximo string lido seja relevante 
    //Aparece várias vezes com mesma finalidade
    fscanf (entrada, "%s", &marcas);

    //Enquanto não for identificado o próximo traço no arquivo, fazer
    while (strcmp(marcas, "---------------------------------------------------------------") != 0)
    {
        //Leitura da localização do arquivo
        fscanf (entrada, "%s", localArq);

        //Faz a variável assumir o valor anteriormente armazenado 
        //e faz o boolean assumir "TRUE" caso 'localArq' seja lido como "=" ou esteja repetido
        if (strcmp(localArq, "=") == 0 || strcmp(localArq, localArqAnt) == 0) 
        {
            rptLoc = TRUE;
            strcpy (localArq, localArqAnt);
        }

        fscanf (entrada, "%s", marcas);

        //Leitura do nome do arquivo 
        fscanf(entrada, "%s", nomeArq);

        //Análogo ao anterior
        if (strcmp(nomeArq, "=") == 0 || strcmp (nomeArq, nomeArqAnt) == 0)
        {
            rptNom = TRUE;
            strcpy (nomeArq, nomeArqAnt);
        }

        fscanf (entrada, "%s", marcas);

        //Leitura da palavra a ser buscada
        fscanf(entrada, "%s", palavraEnt);

        fscanf (entrada, "%s", marcas);

        //Armazena o último string lido nas variáveis 'Ant'
        strcpy (localArqAnt, localArq);
        strcpy (nomeArqAnt, nomeArq);

        //Estruturação do caminho do arquivo
        strcat (localArq,"\\");
        strcat (localArq,nomeArq);
        strcat (localArq,".txt");

        //Abertura do local do arquivo previamente estruturado
        local = fopen(localArq, "r");

        //Verifica se o endereço referente a 'local' é válido
        if (local == NULL)
        {
            fprintf (saida, "\n");
            fprintf (saida, " %s\n", localArq);
            fprintf (saida, "             ARQUIVO NAO ENCONTRADO.\n");

            //Fecha o arquivo em preparação para o próximo loop
            fclose (local);

            //Reinicialização
            cont = 0;
            rptLoc = FALSE;
            rptNom = FALSE;

            fscanf (entrada, "%s", marcas); 
        }
        else
        {
            //Verifica se houve repetição de endereço,
            //garantindo que este só é escrito no arquivo de saída uma vez
            if (rptLoc == FALSE || rptNom == FALSE)
            {
                fprintf (saida, "\n");
                fprintf (saida, " %s\n", localArq);
            }

            //Contagem da palavra no arquivo aberto
            while (!feof(local))
            {
                fscanf (local,"%s ", palavra);
                if (strcmp(palavra, palavraEnt) == 0)
                {
                    cont++;
                }
            }

            //Fecha o arquivo em preparação para o próximo loop
            fclose(local);
            
            //Escreve na saída a palavra e seu respectivo número de ocorrências
            fprintf (saida, "             %s : %d ocorrencias\n", palavraEnt, cont);

            //Reinicialização
            cont = 0;
            rptLoc = FALSE;
            rptNom = FALSE;

            fscanf (entrada, "%s", marcas);
        }

    }
    
    //Fecha todos os arquivos
    fclose (entrada);
    fclose (saida);
    fclose (local);

    //Pausa + finalização
    system ("pause");
    return 0;

}
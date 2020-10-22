/*  Matheus Rodrigues Araújo                        */
/*  Turma 24.1                                      */
/*  Exercício 7 : Bases Numéricas                   */
/*                                                  */
/*  Programa compilado com Code Blocks 17.12        */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*----------------------------------------*/
//Função que converte cada char do string a um numero correspondente da tabela ASCII
//Recebe um char e devolve seu inteiro correspondente
int char_to_int (char carac)
{
    int numero;

    if (carac >= '0' && carac <= '9')
    {
        numero = carac - '0';
    }
    else if (carac >= 'A' && carac <= 'U') //Como a base máxima é 30, o char vai no máximo até 'U'
    {
        numero = carac - 'A' + 10;
    }

    return numero;
}
/*----------------------------------------*/


/*----------------------------------------*/
//Função que converte o número lido a um char correspondente da string da tabela ASCII
//Recebe um inteiro e devolve seu char correspondente
char int_to_char (int numero)
{
    char carac;

    if (numero >= 0 && numero <= 9)
    {
        carac = numero + '0';
    }
    else if (numero >= 10)
    {
        carac = numero + 'A' - 10;
    }
    
    return carac;
}
/*----------------------------------------*/


/*----------------------------------------*/
//Função que efetua a operação de potenciação para inteiros
//Recebe um numero e o expoente ao qual será elevado, devolvendo o resultado da conta
int potencia (int numero, int expo)
{
    int j;
    int result = 1;
    for (j = 0; j < expo; j++)
    {
        result = result * numero;
    }

    return result;
    
}
/*----------------------------------------*/


/*----------------------------------------*/
//Função que escreve a mensagem inicial na tela
void mensagem_inicial_na_tela ()
{
    printf ("Inicio do programa\n");
}
/*----------------------------------------*/


/*----------------------------------------*/
//Função que escreve a mensagem final na tela e efetua a pausa
void mensagem_final_na_tela_e_pausa ()
{
    printf ("Fim do programa\n");
    system ("pause");
}
/*----------------------------------------*/


int main ()
{
    //Declaração de variáveis
    char numString[30],
         marcas[70]; //String que armazena as linhas a serem puladas

    int i, //Variáveis referentes à contagem
        k,
        cont; 

    int baseEnt,
        baseSaida;
    
    int numRest, //Variáveis referentes ao resto da divisão e ao número na base 10 
        num10;

    FILE * entrada,
         * saida;
    

    //Inicialização de algumas variáveis
    cont = 1;
    k = 0;
    num10 = 0;

    //Abertura dos arquivos de entrada e saída
    entrada = fopen("C:\\Lab7\\entrada7.txt", "r");
    saida = fopen("C:\\Lab7\\Matheus_Rodrigues7.txt", "w");

    mensagem_inicial_na_tela ();

    //Pula as primeiras linhas
    for (i = 0; i < 4; i++)
    {
        fgets (marcas, 80, entrada);
    }

    //Escreve a mensagem incial no arquivo
    fprintf (saida, "Esse programa é um conversor de bases numéricas\n");
    fprintf (saida, "Converte entre quaisquer duas bases entre 2 e 30\n");
    fprintf (saida, "Os números convertidos são sempre inteiros\n");
    fprintf (saida, "----\n");


    //Enquanto não chega o fim do arquivo, fazer
    while (!feof(entrada))
    {
        //Leitura das bases e do número
        fscanf (entrada, "%d", &baseEnt);
        fscanf (entrada, "%d", &baseSaida);
        fscanf (entrada, "%s ", &numString);


        //Qualquer que seja a base de entrada, passar para a base 10
        for (i = strlen(numString) - 1; i >= 0; i--)
        {
            num10 += char_to_int (numString[k]) * potencia(baseEnt, i);
            k++;
        }
        k = 0;
    
        //Caso a baseSaida seja 10, a conversão termina aqui
        //Nesse caso, num10 é escrito no arquivo de saida
        if (baseSaida == 10)
        {
            fprintf (saida, "%2d : %d\n", cont, num10);
            cont++;
        }

        //Caso contrário, é efetuada a conversão da base 10 para a base desejada
        else
        {
            //Passar para a base de saída pelo método das divisões sucessivas,
            //armazenando os valores obtidos em uma string
            while (num10 >= baseSaida)
            {
                numRest = num10 % baseSaida;
                num10 = num10 / baseSaida;

                numString[k] = int_to_char(numRest);
                k++;
            }
            numString[k] = int_to_char(num10); //Armazenado o valor referente ao último resto

            //Escrever no arquivo de saída o número convertido para baseSaida,
            //atentando para a ordem correta
            fprintf (saida, "%2d : ", cont);
            for (i = k; i >= 0; i--)
            {
                fprintf (saida, "%c",numString[i]);
            }
            cont++;
            fprintf (saida, "\n");
        }

        //Reinicialização de variáveis
        num10 = 0;
        k = 0;
    }

    // Pausa + finalização
    mensagem_final_na_tela_e_pausa ();
    return 0;
}
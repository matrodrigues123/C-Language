#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    //Criação e definição do struct
    typedef struct aluno aluno;;
    struct aluno
    {
        char nome[20];
        char respostas[10];
        int nota = 0;
        int classific;

    };


    //Declaração de variáveis
    int i = 0;
    char gab[10];
    aluno al1,al2,al3;
    FILE * entrada,
         * gabarito;
         
    entrada = fopen("entrada.txt", "r");
    gabarito = fopen("gabarito.txt","r");


    //Ler o gabarito e printar na tela
    while (!feof(gabarito))
    {
        fscanf (gabarito, "%c ", &gab[i]);
        i++;
    }
    i = 0;

    printf ("O gabarito e:\n");
    for (i = 0; i < 10; i++)
    {
        printf ("%c\n",gab[i]);
    }

    //Ler a entrada com os dados dos alunos e armazenar em seus respectivos structs
    while (!feof(entrada))
    {
        fgets (al1.nome, 20, entrada);
        for (i = 0; i < 10; i++)
        {
            fscanf (entrada, "%c ", &al1.respostas[i]);
            if (al1.respostas[i] == gab[i])
            {
                
                al1.nota ++;
            }
            
        }
        
    }
    printf ("Nome: %sNota:%d",al1.nome,al1.nota);
    

    
    
}

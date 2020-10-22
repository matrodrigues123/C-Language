/* Matheus Rodrigues Araújo                */
/* Turma 24.1                              */
/*                                         */
/* Exercício 1: Encadeamento de Estruturas */
/* Programa compilado com CodeBlocks 17.12 */

#include <stdio.h>
#include <stdlib.h>

//Declaração dos tipos
typedef struct st st;
struct st {int elem; st *prox;};
typedef st *lista;
typedef st *posicao;

typedef int boolean;
#define true 1
#define false 0


lista NovoEncadeamento()
{
    int i, n;
    lista E;
    posicao pont1;

    //Alocação da estrutura líder
    E = (lista) malloc (sizeof(st));

    //Leitura do número de estruturas
    printf ("Digite o numero de elementos do encadeamento: ");
    scanf ("%d", &n);

    //Formação e preenchimento do encadeamento de estruturas
    if (n > 0)
    {
        printf ("\nDigite os elementos: ");
        for (pont1 = E, i = 1; i <= n; i++)
        {
            pont1->prox = (lista) malloc (sizeof(st));
            pont1 = pont1->prox;
            scanf ("%d", &pont1->elem);
        }

        pont1->prox = NULL;
        
    }
    else E->prox = NULL;

    return E;

}

/*---------------------------------------------------------------*/

void EscreverEncadeamento (lista E)
{
    posicao pont1;

    for (pont1 = E->prox; pont1 != NULL; pont1 = pont1->prox)
    {
        printf ("%4d", pont1->elem);
    }
    
}

/*---------------------------------------------------------------*/

void EliminarRepeticao(lista E)
{
    //Declaração de variáveis
    posicao inicio, 
            percorre, 
            apaga;

    int aux;

    //A variável auxiliar é inicializada com 
    //o primeiro elemento da estrutura
    inicio = E;
    percorre = inicio->prox;
    aux = percorre->elem;

    if (inicio->prox != NULL && inicio != NULL)
    {
        while (inicio->prox != NULL)
        {
            while (percorre->prox != NULL)
            {
                //Caso o prox do ponteiro que percorre a estrutura aponte
                //para um elemento igual à variável auxiliar
                if (percorre->prox->elem == aux)
                {
                    //Garante que o ponteiro 'apaga' aponta para aquele cujo
                    //elemento é igual a aux
                    apaga = percorre->prox;
                    if (apaga->prox != NULL)
                    {
                        percorre->prox = apaga->prox;
                    }
                    else
                    {
                        percorre->prox = NULL;
                    }

                    //Desaloca o local da estrutura para o qual 'apaga' aponta
                    free(apaga);
                    
                }
                else
                {
                    percorre = percorre->prox;
                }
            }
            
            //aux assume o próximo elemento a ser procurado
            inicio = inicio->prox;
            percorre = inicio->prox;
            if (percorre != NULL)
            {
                aux = percorre->elem;
            }
            
        }
    }
    
}

/*---------------------------------------------------------------*/

//Função que transforma E1 na união e transforma E2 na intersecção
void UniInt(lista E1, lista E2)
{
    //Declaração de variáveis
    posicao pontAux, 
            pontE2, 
            pontE1;

    boolean achouIntersec = false;

    //Colocar o pontAux  na última posição
    pontAux = E1->prox;
    while (pontAux->prox != NULL)
    {
        pontAux = pontAux->prox;
    }

    pontE2 = E2;

    //Enquanto 'pontE2' não chega no final de E2
    while (pontE2->prox != NULL && pontE2 != NULL)
    {
        pontE1 = E1;
        //Enquanto 'pontE1' não chega no final de E1
        //e não for encontrada intersecção
        while (pontE1->prox != NULL && achouIntersec == false)
        {
            if (pontE2->prox->elem == pontE1->prox->elem)
            {
                pontE2 = pontE2->prox;
                achouIntersec = true;
            }
            else
            {
                pontE1 = pontE1->prox;
            }
            
        }
        //Caso o elemento de pontE2 não esteja em E1,
        //ele é removido de E2(intersec) e colocado em E1(união)
        if (achouIntersec == false)
        {
            pontAux->prox = pontE2->prox;
            pontE2->prox = pontAux->prox->prox;
            pontAux->prox->prox = NULL;
            pontAux = pontAux->prox;
        }
        
        achouIntersec = false;
        
    }
    pontAux->prox = NULL;
    
    
}

/*---------------------------------------------------------------*/

void Circularizar(lista E1)
{

    //Declaração de variáveis
    posicao contaLista,
            percorreLista,
            pontAux,
             ultimo;

    int contadorE1 = 0, 
        contadorE2 = 0, 
        i = 0;

    //Contar os elementos de E1
    contaLista = E1;
    percorreLista = E1;
    while (contaLista->prox != NULL)
    {
        contadorE1++;
        contaLista = contaLista->prox;
    }

    //Circularizar E1
    contaLista->prox = percorreLista;
    percorreLista = contaLista;
    ultimo = percorreLista; //Armazena a última posição da estrutura


    while (percorreLista != E1)
    {
        //pontAux percorre a lista,
        //parando em uma posição cada vez mais próxima do início, conforme contadorE1 diminui
        pontAux = E1;
        if (contadorE1 > 0)
        {
            contadorE1--;
            if (contadorE1 != 0)
            {
                for (pontAux = E1; i < contadorE1; i++)
                {
                    pontAux = pontAux->prox;
                }
            }
            //Quando pontAux chega na posição desejada, 
            //percorreLista->prox assume seu valor, voltando uma casa a cada loop 
            percorreLista->prox = pontAux;
        }
        
        percorreLista = percorreLista->prox;
        i = 0;
        
    }

    //Finaliza a circularização
    E1->prox = ultimo;
}

/*---------------------------------------------------------------*/

void EscreverInvertido (lista E)
{
    posicao pont1;

    for (pont1 = E->prox; pont1 != E; pont1 = pont1->prox)
    {
        printf ("%4d", pont1->elem);
    }
    
}

/*---------------------------------------------------------------*/

int main()
{
    //Declaração de variáveis
    lista E1, 
          E2;

    //Formação dos encadeamentos
    printf ("Formacao do primeiro encadeamento:\n\n");
    E1 = NovoEncadeamento();
    printf("\n");

    printf ("\nFormacao do segundo encadeamento:\n\n");
    E2 = NovoEncadeamento();
    printf("\n\n");


    //Escrita dos encadeamentos 
    printf ("\nConteudo do primeiro encadeamento: \n\n\t");
    EscreverEncadeamento(E1);
    printf ("\n");

    printf ("\nConteudo do segundo encadeamento: \n\n\t");
    EscreverEncadeamento(E2);
    printf ("\n\n");


    //Eliminar repetições dos encadeamentos
    EliminarRepeticao(E1);

    EliminarRepeticao(E2);


    //Escrever os encadeamentos sem repetições
    printf ("\nPrimeiro encadeamento sem repeticoes: \n\n\t");
    EscreverEncadeamento(E1);
    printf ("\n");

    printf ("\nSegundo encadeamento sem repeticoes: \n\n\t");
    EscreverEncadeamento(E2);
    printf ("\n\n");


    //União e intersecção dos encadeamentos
    UniInt(E1,E2);

    printf ("Uniao dos conjuntos: \n\n\t");
    EscreverEncadeamento(E1);
    printf("\n");

    printf("\nIntersec dos conjuntos: \n\n\t");
    EscreverEncadeamento(E2);
    printf("\n\n");


    //Realiza circularização de E1
    Circularizar(E1);


    //Escreve E1 invertido
    printf("Uniao dos conjuntos invertida: \n\n\t");
    EscreverInvertido(E1);


    //Encerramento
    printf ("\n\n");
    system ("pause");
    return 0;
    
}

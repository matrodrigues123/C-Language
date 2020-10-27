#include <stdio.h>
#include <stdlib.h>

typedef struct noh noh;
typedef noh *posicao;
typedef noh *lista;
struct noh {
    int elem;
    noh *prev, *prox;
};

lista EncadeamentoDuplo()
{
    lista E;
    posicao pont1,pont2;
    int num = 1;
    int i;

    E = (lista) malloc (sizeof(noh));

    for (pont1 = E, i = 1; i <= 5; i++)
    {
        pont1->prox = (lista) malloc (sizeof(noh));
        pont2 = pont1->prox;
        pont2->prev = pont1;
        pont2->elem = num;
        pont1 = pont1->prox;

        num += 2;
    }
    pont1->prox = E;
    E->prev = pont1;
    

    return E;
}

void EscreverEncadeamento (lista E)
{
    int i;
    posicao pont1;

    for (pont1 = E->prox, i = 1; i <= 5; pont1 = pont1->prox)
    {
        printf ("%4d", pont1->elem);
        i++;
    }
    printf ("\n");
    
}

void MudarPosicao(lista E)
{
    posicao pont1, pont2, aux1, aux2;

    //Coloca pont1 no '3' e pont2 no '9'
    pont1 = E->prox->prox;
    pont2 = pont1->prox->prox->prox;

    //Ponteiros auxiliares guardam as posições de pont1
    aux1 = pont1->prox;
    aux2 = pont1->prev;

    //Troca as posições de pont1 e pont2
    pont1->prox = pont2->prox;
    pont2->prox = aux1;
    pont1->prev = pont2->prev;
    pont2->prev = aux2;

    //Organiza o resto da estrutura
    pont2->prev->prox = pont2;
    pont1->prev->prox = pont1;
    
}

int main ()
{
    lista E1;

    //Forma o encadeamento duplo
    E1 = EncadeamentoDuplo();

    //Escreve na tela o encadeamento
    EscreverEncadeamento(E1);

    //Mudança de posição
    MudarPosicao(E1);

    //Escreve na tela o encadeamento
    EscreverEncadeamento(E1);

    system ("pause");
    return 0;

    
}



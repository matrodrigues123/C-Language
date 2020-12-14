#include <stdio.h>
#include <stdlib.h>

typedef char logic;
const logic TRUE = 1, FALSE = 0;

struct celulaadj {int vertice; celulaadj *prox;};

struct digrafo {
	celulaadj *Vertices [101]; 
	int nvert;
};

digrafo G;


int main ()
{
    Pontos (&G);
}

void Pontos (digrafo &A)
{
    int i, j;
    celulaadj p;
    logic Partida = TRUE;

    for (i = 1; i < A.nvert; i++)
    {
        // Escrever pontos de partida na tela
        for (j = 1; j < A.nvert && Partida == TRUE; j++)
        {
            for (p = A.Vertices[j]->prox; p != NULL; p = p->prox)
            {
                if (p.vertice == A.Vertices[i]->vertice) Partida = FALSE;
            }
            
        }
        if (Partida == TRUE)
        {
            printf ("Ponto de partida: %d\n", A.Vertices[i]->vertice);
        }
        
        // Escrever os pontos finais na tela
        if (A.Vertices[i]->prox == NULL)
        {
            printf ("Ponto final: %d\n", A.Vertices[i]->vertice);
        }
        
        Partida = TRUE;
    }
}

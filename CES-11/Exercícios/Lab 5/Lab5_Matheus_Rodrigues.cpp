#include <stdio.h>
#include <stdlib.h>

typedef int vertice;
typedef struct CelulaAdj CelulaAdj;
typedef struct CelulaVertice CelulaVertice;
typedef struct Grafo Grafo;
typedef int logic;
typedef char boolean;
const boolean TRUE = 1, FALSE = 0;

struct CelulaAdj {
	vertice vert;
	CelulaAdj *prox;
};

struct CelulaVertice {
	logic visit;
	int nvisit;
	CelulaAdj *listadj, *listcontradj;
};

struct Grafo {
	CelulaVertice *EspacoVertices;
	int nvert;
	logic aciclico;
};


/*	 Variaveis globais */

Grafo G;
FILE *filein;

/*		Prototipos de funcoes	*/

void LerGrafo (Grafo *);
void EscreverGrafo (Grafo *);

/*		Programa Principal:  	*/

int main () {

/*		Leitura e escrita do grafo  	*/

	filein = fopen ("DadosGrafo.txt", "r");
	LerGrafo (&G);
	printf ("\nGrafo G em fase inicial\n");
	EscreverGrafo (&G);
  	printf ("\n\n"); system ("pause"); return 0;
}

void LerGrafo (Grafo *G) {
	vertice vert1, vert2;
	CelulaAdj *pont;
	boolean repetido = FALSE;
	int i;

	fscanf (filein, "%d", &G->nvert);
	G->EspacoVertices = (CelulaVertice *) malloc ((G->nvert+1)*sizeof(CelulaVertice));
	for (i = 1; i <= G->nvert; i++)
	{
		G->EspacoVertices[i].nvisit = -1;
		G->EspacoVertices[i].visit = -1;
		G->EspacoVertices[i].listadj = (CelulaAdj *) malloc (sizeof(CelulaAdj));
		G->EspacoVertices[i].listadj->prox = NULL;
	}
	G->aciclico = -1;

	
	fscanf (filein, "%d", &vert1);
	while (vert1 != 0)
	{
		fscanf (filein, "%d", &vert2);
		pont = G->EspacoVertices[vert1].listadj;

		if (vert1 > 0 && vert1 <= G->nvert && vert2 > 0 && vert2 <= G->nvert)
		{
			while (pont->prox != NULL)
			{
				if (pont->vert == vert2) repetido = TRUE;
				pont = pont->prox;
			}
			if (repetido == FALSE)
			{
				pont->vert = vert2;
				pont->prox = (CelulaAdj *) malloc (sizeof(CelulaAdj));
				pont->prox->prox = NULL;
			}
		}
		else
		{
			// Pular linha
			fscanf (filein, "%d", &vert1);
			fscanf (filein, "%d", &vert2);
		}
		
		fscanf (filein, "%d", &vert1);
		repetido = FALSE;
	}

}

void EscreverGrafo (Grafo *G){
	int i;
	CelulaAdj *pont;

	for (i = 1; i <= G->nvert; i++)
	{
		printf ("Vertice %d)  ", i);
		printf("Visitado: %3d; N.o de Visita: %3d;\n", G->EspacoVertices[i].visit, G->EspacoVertices[i].nvisit);
		printf ("\tAdjacentes: ");
		for (pont = G->EspacoVertices[i].listadj; pont->prox != NULL; pont = pont->prox)
		{
			printf ("%3d ", pont->vert);
		}
		printf ("\n\n");
	}
	
}



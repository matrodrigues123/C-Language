/* Matheus Rodrigues Araújo                */
/* Turma 24.1                              */
/*                                         */
/* Exercício 5: Dígrafos                   */
/* Programa compilado com CodeBlocks 17.12 */

#include <stdio.h>
#include <stdlib.h>

typedef int vertice;
typedef struct CelulaAdj CelulaAdj;
typedef struct CelulaVertice CelulaVertice;
typedef struct Grafo Grafo;
typedef char logic;
const logic TRUE = 1, FALSE = 0;

struct CelulaAdj {
	vertice vert;
	CelulaAdj *prox;
};

struct CelulaVertice {
	logic visit;
	int nvisit, noutro;
	CelulaAdj *listadj, *listcontradj;
};

struct Grafo {
	CelulaVertice *EspacoVertices;
	int nvert;
	logic aciclico;
};

typedef struct noh noh;
typedef noh *pilha;
struct noh {vertice elem; noh *prox;};


/*	 Variaveis globais */

Grafo G, Gr;
FILE *filein;
int cont, contOutro; pilha P; logic aciclico;pilha topol;


/*		Prototipos de funcoes	*/

void LerGrafo (Grafo *);
void EscreverGrafo (Grafo *);
void Empilhar (vertice, pilha*);
void Desempilhar (pilha*);
vertice Topo (pilha);
void InicPilha (pilha*);
logic Vazia (pilha);
void Travessia (Grafo*);
logic Procurar (vertice, pilha*);
void BuscaProf (vertice, Grafo*);
void OrdTopologica (pilha);
void FormarGr(Grafo*, Grafo*);
void FortConexos (Grafo*);
void FreeSobras(Grafo*);
void ResetGrafos (Grafo *, Grafo *);

/*		Programa Principal:  	*/

int main () {

/*		Leitura e escrita dos grafos  	*/
	filein = fopen ("DadosGrafo.txt", "r");
	int numGrafos, i;
	fscanf (filein, "%d", &numGrafos);
	for (i = 1; i <= numGrafos; i++)
	{
		LerGrafo (&G);
		printf ("\nGrafo G em fase inicial\n");
		Travessia (&G);
		EscreverGrafo (&G);
		printf ("\n\n");
		if (aciclico == TRUE)
		{
			printf ("Aciclico\n");
			printf ("Ordem topologica: ");
			OrdTopologica(topol);
		}
		else
		{
			printf ("Ciclico\n");
			FormarGr(&G, &Gr);
			FortConexos(&Gr);
			printf ("\n");
		}

		ResetGrafos(&G, &Gr);
		
	}
	
  	printf ("\n\n"); system ("pause"); return 0;
}

void LerGrafo (Grafo *G) {
	vertice vert1, vert2;
	CelulaAdj *pontAdj, *pontContra, *aux;
	logic repetido = FALSE;
	int i;

	// Inicializa o grafo
	fscanf (filein, "%d", &G->nvert);
	G->EspacoVertices = (CelulaVertice *) malloc ((G->nvert+1)*sizeof(CelulaVertice));
	for (i = 1; i <= G->nvert; i++)
	{
		G->EspacoVertices[i].nvisit = -1;
		G->EspacoVertices[i].visit = -1;
		G->EspacoVertices[i].listadj = (CelulaAdj *) malloc (sizeof(CelulaAdj));
		G->EspacoVertices[i].listadj->prox = NULL;
		G->EspacoVertices[i].listcontradj = (CelulaAdj *) malloc (sizeof(CelulaAdj));
		G->EspacoVertices[i].listcontradj->prox = NULL;
	}
	G->aciclico = -1;

	// Forma as listas de adjacência e contra adjacência
	fscanf (filein, "%d", &vert1);
	while (vert1 != 0)
	{
		fscanf (filein, "%d", &vert2);
		pontAdj = G->EspacoVertices[vert1].listadj;

		if (vert1 > 0 && vert1 <= G->nvert && vert2 > 0 && vert2 <= G->nvert)
		{
			while (pontAdj->prox != NULL)
			{
				if (pontAdj->vert == vert2) repetido = TRUE;
				pontAdj = pontAdj->prox;
			}
			if (repetido == FALSE)
			{
				pontAdj->vert = vert2;

				// Contra adjacência
				pontContra = G->EspacoVertices[vert2].listcontradj;
				while (pontContra->prox != NULL)
				{
					pontContra = pontContra->prox;
				}
				pontContra->vert = vert1;
				pontContra->prox = (CelulaAdj *) malloc (sizeof(CelulaAdj));
				pontContra->prox->prox = NULL;
				
				pontAdj->prox = (CelulaAdj *) malloc (sizeof(CelulaAdj));
				pontAdj->prox->prox = NULL;
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

	// Dar free nas sobras
	FreeSobras(G);
	
}

void EscreverGrafo (Grafo *G){
	int i;
	CelulaAdj *pontAdj, *pontContra;

	for (i = 1; i <= G->nvert; i++)
	{
		printf ("Vertice %d)  ", i);
		printf("Visitado: %3d; N.o de Visita: %3d;\n", G->EspacoVertices[i].visit, G->EspacoVertices[i].nvisit);
		printf ("\tAdjacentes: ");
		for (pontAdj = G->EspacoVertices[i].listadj; pontAdj != NULL; pontAdj = pontAdj->prox)
		{
			printf ("%3d ", pontAdj->vert);
		}
		printf ("\n");
		printf ("\tContra adjacentes: ");
		for (pontContra = G->EspacoVertices[i].listcontradj; pontContra != NULL; pontContra = pontContra->prox)
		{
			printf ("%3d ", pontContra->vert);
		}
		printf ("\n\n");
	}
	
}

// Funções operadoras de pilha

void Empilhar (vertice x, pilha *P) { 
    noh *temp;
	temp = *P;  
    *P = (noh *) malloc (sizeof (noh));
	(*P)->elem = x; 
    (*P)->prox = temp;
}

void Desempilhar (pilha *P) {
	noh *temp; 
	if (! Vazia(*P)) 
    {
        temp = *P; 
        *P = (*P)->prox; 
        free (temp); 
    } 
}

vertice Topo (pilha P) {
    if (! Vazia(P)) return P->elem;
}

void InicPilha (pilha *P) { *P = NULL; }

logic Vazia (pilha P) {
	if (P == NULL) return TRUE; 
    else return FALSE; 
}

// Funções de busca em profundidade
void Travessia (Grafo *G)  {
	vertice v;
	InicPilha (&P); aciclico = TRUE;
	for (v = 1; v <= G->nvert; v++)
		G->EspacoVertices[v].visit = FALSE;
	cont = 0;
	contOutro = 0;
	for (v = 1; v <= G->nvert; v++)
		if  (G->EspacoVertices[v].visit == FALSE)
			BuscaProf (v, G);
}
void BuscaProf (vertice v, Grafo *G)  {
	CelulaAdj *p;
	G->EspacoVertices[v].visit = TRUE;  cont++;
	G->EspacoVertices[v].nvisit = cont;
	Empilhar (v, &P);
	p = G->EspacoVertices[v].listadj;
	while (p != NULL)  {
		if (G->EspacoVertices[p->vert].visit == FALSE)
		{
			BuscaProf(p->vert, G);
		}
		else if (Procurar (p->vert, &P) == TRUE)
			aciclico = FALSE;
		p = p->prox;
	}
	contOutro++;
	G->EspacoVertices[v].noutro = contOutro;
	Desempilhar (&P);
	Empilhar (v, &topol);
}
logic Procurar (vertice x, pilha *P)
{
	noh *percorre;
	percorre = *P;

	while (percorre != NULL)
	{
		if (percorre->elem == x) return TRUE;
		percorre = percorre->prox;
	}

	return FALSE;
}

// Ordenação topológica
void OrdTopologica (pilha x){
	while (!Vazia(x))
	{
		printf ("%3d", x->elem);
		Desempilhar (&x);
	}
}

// Funções relacionadas aos vértices fortemente conexos
void FormarGr(Grafo *G, Grafo *Gr){
	int i;
	CelulaAdj *pontG, *pontGr;
	
	// Inicializar Gr
	Gr->nvert = G->nvert;
	Gr->EspacoVertices = (CelulaVertice *) malloc ((Gr->nvert+1)*sizeof(CelulaVertice));
	for (i = 1; i <= Gr->nvert ; i++)
	{
		Gr->EspacoVertices[i].nvisit = G->EspacoVertices[i].nvisit;
		Gr->EspacoVertices[i].noutro = G->EspacoVertices[i].noutro;
		Gr->EspacoVertices[i].visit = FALSE;
		Gr->EspacoVertices[i].listadj = (CelulaAdj *) malloc (sizeof(CelulaAdj));
		Gr->EspacoVertices[i].listadj->prox = NULL;
		Gr->EspacoVertices[i].listcontradj = (CelulaAdj *) malloc (sizeof(CelulaAdj));
		Gr->EspacoVertices[i].listcontradj->prox = NULL;
	}

	// Inverter os arcos de G
	for (i = 1; i <= Gr->nvert ; i++)
	{
		pontG = G->EspacoVertices[i].listcontradj;
		pontGr = Gr->EspacoVertices[i].listadj;

		while (pontG != NULL)
		{
			pontGr->vert = pontG->vert;
			pontGr->prox = (CelulaAdj *) malloc (sizeof(CelulaAdj));
			pontGr = pontGr->prox;
			pontGr->prox = NULL;
			pontG = pontG->prox;
		}
		
		pontG = G->EspacoVertices[i].listadj;
		pontGr = Gr->EspacoVertices[i].listcontradj;

		while (pontG != NULL)
		{
			pontGr->vert = pontG->vert;
			pontGr->prox = (CelulaAdj *) malloc (sizeof(CelulaAdj));
			pontGr = pontGr->prox;
			pontGr->prox = NULL;
			pontG = pontG->prox;
		}
	}

	// Eliminar sobras de Gr
	FreeSobras(Gr);
}

// Percorrer Gr e escrever os fortemente conexos
void FortConexos (Grafo *Gr){
	CelulaVertice max;
	vertice maxVert = 0;
	int i,k, cont = 1;

	// Obter o vértice de maior numeração e efetuar a busca em profundidade a partir dele
	max = Gr->EspacoVertices[1];
	maxVert = 1;
	printf ("Fortemente conexos:\n");
	for (i = 1; i <= Gr->nvert; i++)
	{
		for (k = 1; k <= Gr->nvert; k++)
		{
			if (Gr->EspacoVertices[k].visit == FALSE && Gr->EspacoVertices[k].noutro > max.noutro)
			{
				max = Gr->EspacoVertices[k];
				maxVert = k;
			}
		}
		if  (Gr->EspacoVertices[i].visit == FALSE)
		{
			InicPilha(&topol);
			BuscaProf (maxVert, Gr);
			printf ("%d:",cont);
			while (!Vazia(topol))
			{
				printf ("%3d", topol->elem);
				Desempilhar (&topol);
			}
			printf ("\n");
		}
		max.noutro = 0;
		cont++;
	}
}

// Liberar espaços não utilizados da memória dos grafos
void FreeSobras(Grafo *X){
	int i;
	CelulaAdj *pontAdj, *pontContra, *aux;
	for (i = 1; i <= X->nvert; i++)
	{
		pontAdj = X->EspacoVertices[i].listadj;
		if (pontAdj->prox != NULL)
		{
			while (pontAdj->prox != NULL)
			{
				aux = pontAdj;
				pontAdj = pontAdj->prox;
			}
			aux->prox = pontAdj->prox;
			free(pontAdj);
		}
		else
		{
			free(pontAdj);
			X->EspacoVertices[i].listadj = NULL;
		}

		pontContra = X->EspacoVertices[i].listcontradj;
		if (pontContra->prox != NULL)
		{
			while (pontContra->prox != NULL)
			{
				aux = pontContra;
				pontContra = pontContra->prox;
			}
			aux->prox = pontContra->prox;
			free(pontContra);
		}
		else
		{
			free(pontContra);
			X->EspacoVertices[i].listcontradj = NULL;
		}
	}
}

// Reiniciar os grafos para novo loop
void ResetGrafos (Grafo *G, Grafo *Gr){
	int i;
	CelulaAdj aux;

	for (i = 1; i <= G->nvert; i++)
	{
		free(&G->EspacoVertices[i]);
		free(&Gr->EspacoVertices[i]);
	}
	
}


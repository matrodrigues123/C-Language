#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

typedef char logic;
const logic TRUE = 1, FALSE = 0;

/* Declaracoes de tipos para encadeamento de pais e irmaos para arvores    */

typedef struct celula celula;
const celula *nulo = NULL;
typedef char informacao;
typedef celula *noh;
typedef celula *arvore;
struct celula {informacao info; noh pai, fesq, idir;};

/* Declaracoes de tipos para estrutura encadeada de filas de nohs de arvores   */

typedef struct celfila celfila;
typedef struct fila fila;
struct celfila {noh elem; celfila *prox;};
struct fila {celfila *fr, *tr;};

/* Declaracoes de tipos para floresta, que eh uma lista encadeada de arvores, com elemento-lider    */

typedef char string[100];
typedef struct celfloresta celfloresta;
typedef struct celfloresta *floresta;
typedef struct celfloresta *posicfloresta;
struct celfloresta {
  	arvore elem; celfloresta *prox;
};

/* Variaveis globais  */

floresta F;
floresta pontPai, pontFilho, pontAux;
logic paiEstah = FALSE, filhoEstah = FALSE;
string StrFloresta;  // guarda os caracteres digitados

/* Prototipos das funcoes dependentes da estrutura para arvores  */

void FormarListaNohs (void);
void EscreverFloresta (void);
void LigarPaisFilhos (void);
void ProcuraArvore (char, char);
arvore Criacao (informacao, floresta);

/* Prototipos das funcoes operadoras de arvores  */

logic ArvVazia (arvore);
informacao Elemento (noh, arvore);
void EscreverNoh (informacao);
noh Raiz (arvore);
noh Pai (noh, arvore);
noh FilhoEsquerdo (noh, arvore);
noh IrmaoDireito (noh, arvore);

/* Prototipos das funcoes independentes da estrutura para arvores  */

void EscreverNiveis (arvore);

/* Prototipos das funcoes operadoras de filas  */

void InitFila (fila *);
void EntrarFila (noh, fila *);
noh DeletarFila (fila *);
char FilaVazia (fila);


int main ()
{
    informacao c; arvore A;
    printf ("Leitura e armazenamento dos nohs da floresta F:\n\n");
	FormarListaNohs ();
    if (F->prox != NULL) 
    {
		printf ("\nLeitura e ligacao dos pares pais-filhos:\n\n");
   	    LigarPaisFilhos ();
	} 
	printf ("\n\nArvores da floresta F:\n\n");
	EscreverFloresta ();
	printf ("\n\nCriacao de nova arvore:\n\n\t");
	printf ("Digite a informacao da raiz: "); c = getche ();
    if (isdigit(c) || isalpha(c))
    {
        A = Criacao (c, F);
	    printf ("\n\n"); EscreverNiveis (A);
    }
    else
    {
        printf ("Informacao da nova raiz invalida");
    }
	
	printf ("\n\n"); system ("pause"); return 0;

}

/* Funcao FormarListaNohs: le as informacoes dos nohs de uma floresta armazenando-as em celulas; forma uma 	lista linear de nohs ponteiros para essas celulas; 	essa lista eh a floresta F (global)   */

void FormarListaNohs () 
{
    floresta posicao;
    int i = 0;

    printf ("Digite uma string contendo os caracteres de todos os nohs da floresta: \n");
    scanf ("%s", StrFloresta);

    F = (celfloresta *) malloc (sizeof (celfloresta));

    for (posicao = F; StrFloresta[i] != '\0'; i++)
    {
        posicao->prox = (celfloresta *) malloc (sizeof (celfloresta));
        posicao = posicao->prox;
        posicao->elem = (celula *) malloc (sizeof (celula));

        if (isdigit(StrFloresta[i]) || isalpha(StrFloresta[i]))
        {
            posicao->elem->info = StrFloresta[i];
            posicao->elem->pai = NULL;
            posicao->elem->fesq = NULL;
            posicao->elem->idir = NULL;
        }
    
    }
    posicao->prox = NULL;

}

/* Funcao EscreverFloresta: escreve os nos de todas as arvores da floresta F em ordem de nivel */

void EscreverFloresta () 
{
    floresta percorre;
    for (percorre = F->prox; percorre != NULL; percorre = percorre->prox)
    {
        EscreverNiveis(percorre->elem);
    }
     
}

void EscreverNiveis (arvore A) 
{
	fila fp, fs;
	noh x, y, pai;
	if (ArvVazia (A) == TRUE) printf ("  Arvore vazia");
	else {
		InitFila (&fs);
		EntrarFila (Raiz (A), &fs);
		do {
			fp = fs;
			InitFila (&fs);
			while (FilaVazia(fp) == FALSE) {
				x = DeletarFila(&fp);
				EscreverNoh (Elemento (x, A));
				pai = Pai (x, A); printf ("(");
				if (pai == nulo) EscreverNoh ('#');
				else EscreverNoh (Elemento (pai, A));
				printf (") ");
				for (y = FilhoEsquerdo (x, A); y != nulo; 
							y = IrmaoDireito(y, A))
					EntrarFila (y, &fs);
			}
      		printf ("\n");
		} while (FilaVazia(fs) == FALSE);
	}
    printf ("\n\n");
}

/*		Funcoes operadoras de arvores           */

logic ArvVazia (arvore A) {
	if (A == NULL) return TRUE;
	else return FALSE;
}

informacao Elemento (noh n, arvore A) {return n->info;}

void EscreverNoh (informacao info) {printf ("%c", info);}

noh Raiz (arvore A) {return A;}

noh Pai (noh n, arvore A) {return n->pai;}

noh FilhoEsquerdo (noh n, arvore A) {return n->fesq;}

noh IrmaoDireito (noh n, arvore A) {return n->idir;}

/*		Funcoes operadoras de filas de nos de arvores     */

void InitFila (fila *f) {
	f->fr = (celfila *) malloc (sizeof(celfila));
	f->tr = f->fr; f->fr->prox = NULL;
}

void EntrarFila (noh x, fila *f) {
	f->tr->prox = (celfila *) malloc (sizeof(celfila)); f->tr = f->tr->prox;
	f->tr->elem = x; f->tr->prox = NULL;
}

noh DeletarFila (fila *f) {
	noh x; celfila *p;
	p = f->fr->prox; x = p->elem;
	if (f->tr == p) f->tr = f->fr;
	f->fr->prox = p->prox; free (p);
	return x;
}

char FilaVazia (fila f) {
	char c;
	if (f.fr == f.tr) c = TRUE;
	else c = FALSE;
	return c;
}

/*		Funcoes para ligar pais e filhos    */
void ProcuraArvore (char carac1, char carac2)
{
    floresta percorreArv;

    for (percorreArv = F; percorreArv->prox != NULL; percorreArv = percorreArv->prox)
    {
        if (percorreArv->prox->elem->info == carac1)
        {
            pontPai = percorreArv->prox;
            paiEstah = TRUE;
        }
        if (percorreArv->prox->elem->info == carac2)
        {
            pontAux = percorreArv;
            pontFilho = percorreArv->prox;
            filhoEstah = TRUE;
        }
    }

}

void LigarPaisFilhos ()
{
    int k, n;
    string par;

    printf ("Digite o numero de pares: \n");
    scanf ("%d",&n);
    for (k = 1; k <= n; k++)
    {
        printf ("Digite o par numero %d: \n", k);
        scanf ("%s", par);

        ProcuraArvore (par[0], par[1]);
        if (par[0] != par[1] && strlen (par) == 2 && paiEstah == TRUE && filhoEstah == TRUE && pontFilho->elem->pai == NULL) 
        {
            if (pontPai->elem->fesq == NULL)
            {
                pontPai->elem->fesq = pontFilho->elem;
                pontFilho->elem->pai = pontPai->elem;
                
            }
            else
            {
                pontFilho->elem->idir = pontPai->elem->fesq;
                pontPai->elem->fesq = pontFilho->elem;
                pontFilho->elem->pai = pontPai->elem;

            }

            pontAux->prox = pontFilho->prox;
            free (pontFilho);

            paiEstah = FALSE;
            filhoEstah = FALSE;
        }
        else
        {
            printf ("Par invalido");
        }
    }
}

 /*		Funcao para criar arvore    */
arvore Criacao (informacao carac,floresta selva)
{
    floresta percorreF;
    arvore nova;
    nova = (celula *) malloc (sizeof (celula));

    nova->info = carac;
    nova->pai = NULL;
    nova->fesq = NULL;
    nova->idir = NULL;


    for (percorreF = selva->prox; percorreF != NULL; percorreF = percorreF->prox)
    {
        percorreF->elem->pai = nova;
        if (nova->fesq == NULL) nova->fesq = percorreF->elem;
        if (percorreF->prox != NULL) percorreF->elem->idir = percorreF->prox->elem;
    }

    return nova;
}





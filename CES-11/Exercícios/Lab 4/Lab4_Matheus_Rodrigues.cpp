/* Matheus Rodrigues Araújo                */
/* Turma 24.1                              */
/*                                         */
/* Exercício 4: Árvores                    */
/* Programa compilado com CodeBlocks 17.12 */

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
// floresta pontPai = NULL, pontFilho = NULL, pontAux;
// logic paiEstah = FALSE, filhoEstah = FALSE;
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

/* Prototipos das funcoes que escrevem informacoes da arvore  */
void Parentetica (arvore);
int Altura (noh, arvore);
int NumNohs (noh, arvore);
int MaxLargura (arvore);
int NivelLargura (arvore, int);


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

        if (ArvVazia(A) == FALSE)
        {
            printf ("\nArvore na forma parentetica: \n");
            Parentetica(A);
            printf ("\n");

            printf ("Altura: %d\n", Altura(A,A));
            printf ("Numero de nohs: %d\n", NumNohs(A,A));
            printf ("Largura: %d",MaxLargura(A));
        }
        
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

        // Armazenar o char da string na floresta caso seja válido
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
void LigarPaisFilhos ()
{
    int i, n, numValidos = 1;
    string par;
    floresta pai, filho, percorreSelva, aux;
    logic paiEstah, filhoEstah;

    printf ("Digite o numero de pares: \n");
    scanf ("%d",&n);

    for (i = 1; i <= n; i++)
    {
        printf ("Digite o par numero %d: \n", numValidos);
        setbuf(stdin, NULL);
        scanf ("%s", par);

        // Inicializar as booleanas com false por padrão
        paiEstah = FALSE;
        filhoEstah = FALSE;

        // Verificar se o par esta na floresta e marcar sua posicao
        for (percorreSelva = F->prox; percorreSelva != NULL; percorreSelva = percorreSelva->prox)
        {
            if (percorreSelva->elem->info == par[0])
            {
                pai = percorreSelva;
                paiEstah = TRUE;
            }
            if (percorreSelva->elem->info == par[1])
            {
                filho = percorreSelva;
                filhoEstah = TRUE;
            }
        }

        // Associar pais e filhos caso os pares sejam válidos
        if (par[0] != par[1] && strlen (par) == 2 && paiEstah == TRUE && filhoEstah == TRUE && filho->elem->pai == NULL)
        {
            if (pai->elem->fesq == NULL)
            {
                pai->elem->fesq = filho->elem;
                filho->elem->pai = pai->elem;
            }
            else
            {
                filho->elem->idir = pai->elem->fesq;
                pai->elem->fesq = filho->elem;
                filho->elem->pai = pai->elem;
            }

            numValidos++;
        }
        else
        {
            printf ("Par invalido\n");
            n++;
        }
        
        
    }

    // Dar free nas celulas da floresta que são filhos de alguém
    percorreSelva = F;
    while (percorreSelva->prox != NULL)
    {
        if (percorreSelva->prox->elem->pai != NULL)
        {
            aux = percorreSelva->prox;
            percorreSelva->prox = percorreSelva->prox->prox;
            free (aux);
        }
        else
        {
            percorreSelva = percorreSelva->prox;
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

/*		Funcoes para coletar informacao das arvores    */
void Parentetica (arvore A)
{
    noh pont1;
    printf (" (%c",Elemento(A,A));

    pont1 = FilhoEsquerdo(A, A);
    // Escreve a parentetica recursivamente, até que o filho esquerdo da primeira instância seja nulo
    while (pont1 != NULL)
    {
        if (pont1 != NULL) Parentetica(pont1);
        pont1 = IrmaoDireito(pont1,A);
    }
    printf (")");
}

int Altura (noh n, arvore A) {
	int maxalt, aux; noh f;
	if (n == nulo) return -1;
	f = FilhoEsquerdo (n, A);
	if (f == nulo) return 0;
	for (maxalt = 0; f != nulo; f = IrmaoDireito (f, A)) {
		aux = Altura (f, A);
		if (aux > maxalt) maxalt = aux;
	}
   return maxalt + 1;
}

int NumNohs (noh n, arvore A) {
	int numNohs, aux; noh f;
    if (n == nulo) return 0;
	f = FilhoEsquerdo (n, A);
	if (f == nulo) return 1;
	for (numNohs = 0; f != nulo; f = IrmaoDireito (f, A)) {
		aux = NumNohs (f, A);
		numNohs += aux;
	}
   return numNohs + 1;
	
}

int MaxLargura (arvore A) {
    int maxLargura = 0, largura, i;
    int h = Altura(A,A);

    // Percorrendo a árvore por sua altura, enquanto não chegar no fim
    for (i = 1; i <= h; i++)
    {
        // Comparar a largura do nivel atual com a variável maxLargura
        largura = NivelLargura(A, i);
        if (largura > maxLargura) maxLargura = largura;
    }
    
    return maxLargura + 1;

}

int NivelLargura (arvore A, int nivel)
{
    // Largura 0 para árvore vazia
    if (A == NULL) return 0;
    // Largura 1 para raiz
    if (nivel == 1) return 1;
    // Retorna a largura do nível ao chamar essa função recursivamente
    else if (nivel > 1)
    {
        return NivelLargura(FilhoEsquerdo(A,A), nivel-1) + NivelLargura(IrmaoDireito(FilhoEsquerdo(A,A), A), nivel-1);
    }
}







/*	 Declarações globais  */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef char logic;
const logic TRUE = 1, FALSE = 0;

typedef char string[20];

typedef struct eletrodomestico eletrodomestico;
struct eletrodomestico {
	string nome;
	int unids;
};

typedef struct noh noh;
struct noh {
	eletrodomestico eletro;
	noh *prox;
};

typedef struct lista lista;
struct lista {
	noh *inic, *fim;
};

typedef noh *posicao;

lista Estoque;

/*	Prototipos das funcoes auxiliares		*/

void NovoEstoque (void);
void OrdenarEstoque (void);
void ListarEstoque (void);

/*	Funcao principal             */

int main () 
{
	printf ("Controle do Estoque de Eletrodomesticos\n\n");

	NovoEstoque ();
	OrdenarEstoque ();
	ListarEstoque ();

	printf ("\n\n"); 
    system ("pause"); 
    return 0;
}

void NovoEstoque () 
{
	posicao p;
	int i, n;
 	p = Estoque.inic = (noh *) malloc (sizeof (noh));
	printf ("Numero de aparelhos: "); 
	scanf ("%d", &n);
	if (n > 0)
    {
        for (i = 1; i <= n; i++)
        {
            p->prox = (noh *) malloc (sizeof (noh));
            p = p->prox;
            printf ("\nNome e a quantidade do %d aparelho: ", i);
            setbuf (stdin, NULL);
            scanf ("%s%d", p->eletro.nome, &p->eletro.unids);
		}
    }
		
	p->prox = NULL;
	Estoque.fim = p;
}

void OrdenarEstoque () 
{
	posicao p, q, min; 
    eletrodomestico menor;

	for (p = Estoque.inic->prox; p != NULL && p->prox != NULL; p = p->prox) 
    {
		for (menor = p->eletro, min = p, q = p->prox; q != NULL; q = q->prox) 
        {
			if (strcmp (q->eletro.nome, menor.nome) < 0) 
            {
				menor = q->eletro; 
				min = q;
			}
		}
		if (min != p) 
        {
			min->eletro = p->eletro; 
			p->eletro = menor;
		}
	}
}

void ListarEstoque () 
{
	posicao p;
	if (Estoque.inic->prox == NULL)
    {
        printf ("\nEstoque vazio\n");
    } 	
	else 
    {
		printf ("\n%22s|%10s\n", "Nome        ", "Unidades");
		printf ("-----------------------------------\n");
		for (p = Estoque.inic->prox; p != NULL; p = p->prox)
        {
            printf ("%22s|%10d\n", p->eletro.nome, p->eletro.unids);
        }
	}
	printf ("\n");
}





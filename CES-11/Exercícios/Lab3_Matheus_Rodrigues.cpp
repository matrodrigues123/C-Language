/* Matheus Rodrigues Araújo                */
/* Turma 24.1                              */
/*                                         */
/* Exercício 3: TAD: Pilha                 */
/* Programa compilado com CodeBlocks 17.12 */

/*	Inclusao de bibliotecas de C	*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>

/* Declaracoes para o tipo logic  */

typedef char logic;
const logic TRUE = 1, FALSE = 0;

/*	Definicao dos tipos de atomos	*/

#define NUM 		1
#define OPER		2
#define ABPAR		3
#define FPAR		4
#define INVAL		5

/*	Declaracoes de tipos para as expressoes e listas de atomos	*/

typedef char expressao[50];

typedef union atribatomo atribatomo;
union atribatomo {
	float valor; char carac;
};

typedef struct atomo atomo;
struct atomo {
	int tipo; atribatomo atrib;
};

typedef struct listaatomos listaatomos;
struct listaatomos {
  	int natom; atomo Vetor[50];
};

typedef struct noh noh;
typedef noh *pilha;
struct noh {atomo elem; noh *prox;};

typedef noh *posicao;

/*	Variaveis globais  */

int i; char c; expressao Expr;
listaatomos Parentetica;
listaatomos polonesa;

/*	Prototipos das funcoes auxiliares	*/

void ArmazenarParentetica (void);
void EscreverListaAtomos ();
char ProxNaoBranco (void);
char ProxCarac (void);
void InicExpr (void);
void Empilhar (atomo, pilha*);
void Desempilhar (pilha*);
atomo Topo (pilha);
void InicPilha (pilha*);
logic Vazia (pilha);
void FormarPolonesa();
void Resultado();
logic TesteRecursivo ();
logic ParenteticaCorreta () ;


/*	Funcao main		*/

int main() {
	char c;
	printf ("Armazenar expressao parentetica? (s/n): ");
	do c = getche ();
	while (c!='s' && c!='n' && c!='S' && c!='N');
	while (c == 's' || c == 'S') {
		printf ("\n\n"); printf ("Digite a expressao: ");
		setbuf (stdin, NULL); gets (Expr);
		ArmazenarParentetica ();
        EscreverListaAtomos ();
        if (ParenteticaCorreta() == TRUE)
        {
            printf ("\nA polonesa correspondente a expressao e' dada por: \n");
            FormarPolonesa ();
            Resultado();
        }
        else
        {
            printf ("\nA expressao esta incorreta");
        }
        
		printf 
		   ("\n\nArmazenar expressao parentetica? (s/n): ");
		do c = getche ();
		while (c!='s' && c!='n' && c!='S' && c!='N');
	}
	printf ("\n\n"); printf ("Fim das atividades!");
	printf ("\n\n"); system ("pause"); return 0;
}

/*	 Funcoes para percorrer a expressao		*/

char ProxNaoBranco () {
	while (isspace (Expr[i]) ||
			(iscntrl (Expr[i]) && Expr[i] != '\0')) i++;
	return Expr[i];
}

char ProxCarac () {
	i++;  
	return Expr[i];
}

void InicExpr () { 
	i = 0; 
}


/* Função para armazenar a parentética    */

void ArmazenarParentetica () {
    int k = 0;
    float fact = 1;
    Parentetica.natom = 0;
    
    InicExpr();
    ProxNaoBranco();
    
    while (Expr[i] != '\0')
    {
        if (isdigit(Expr[i]))
        {
            Parentetica.Vetor[k].tipo = NUM;
            Parentetica.Vetor[k].atrib.valor = Expr[i] - '0';
            ProxCarac();
            ProxNaoBranco();
            while (isdigit(Expr[i]))
            {
                Parentetica.Vetor[k].atrib.valor = 10*Parentetica.Vetor[k].atrib.valor + Expr[i] - '0';
                ProxCarac();
                ProxNaoBranco();
            }
            if (Expr[i] == '.')
            {
                ProxCarac();
                ProxNaoBranco();
                if (isdigit(Expr[i]))
                {
                    do
                    {
                        Parentetica.Vetor[k].atrib.valor = 10*Parentetica.Vetor[k].atrib.valor + Expr[i] - '0';
                        fact /= 10;
                        ProxCarac();
                        ProxNaoBranco();
                    } 
                    while (isdigit(Expr[i]));
                    Parentetica.Vetor[k].atrib.valor *= fact;
                    fact = 1;
                }
                
                
            }
            
        }
        else if (Expr[i] == '+' || Expr[i] == '*' || Expr[i] == '~' || Expr[i] == '/' || Expr[i] == '^' || Expr[i] == 'R' || Expr[i] == 'L')
        {
            Parentetica.Vetor[k].tipo = OPER;
            Parentetica.Vetor[k].atrib.carac = Expr[i];
            ProxCarac();
            ProxNaoBranco();
        
        }
        else if (Expr[i] == '(')
        {
            Parentetica.Vetor[k].tipo = ABPAR;
            ProxCarac();
            ProxNaoBranco();
        
        }
        else if (Expr[i] == ')')
        {
            Parentetica.Vetor[k].tipo = FPAR;
            ProxCarac();
            ProxNaoBranco();
        
        }
        else
        {
            Parentetica.Vetor[k].tipo = INVAL;
            Parentetica.Vetor[k].atrib.carac = Expr[i];
            ProxCarac();
            ProxNaoBranco();
        
        }
        k++;
        Parentetica.natom++;
        
    }
    
}

/* Função para escrever a parentética    */

void EscreverListaAtomos (){
    int k;

    printf ("\n%22s|%10s\n", "TIPO       ", "Atributo");
	printf ("-----------------------------------\n");

    for (k = 0; k < Parentetica.natom; k++)
    {
        switch (Parentetica.Vetor[k].tipo)
        {
            case 1:
                printf ("\n%22s|%10g\n", "NUM      ", Parentetica.Vetor[k].atrib.valor);
                break;
            case 2:
                printf ("\n%22s|%10c\n", "OPER      ", Parentetica.Vetor[k].atrib.carac);
                break;
            case 3:
                printf ("\n%22s|%10s\n", "ABPAR      ","");
                break;
            case 4:
                printf ("\n%22s|%10s\n", "FPAR      ","");
                break;
            default:
                printf ("\n%22s|%10c\n", "INVAL     ", Parentetica.Vetor[k].atrib.carac);
                break;
        }
        
    }
    
}

/* Funções para verificar se a parentética está correta    */

logic TesteRecursivo () {
	logic r = TRUE;
	if (Parentetica.Vetor[i].tipo == ABPAR) {
		i++;
        if (Parentetica.Vetor[i].tipo == NUM) i++;
        else if (Parentetica.Vetor[i].tipo == ABPAR) 
            r = TesteRecursivo ();
        else if (Parentetica.Vetor[i].tipo != OPER) r = FALSE;

        if (r && Parentetica.Vetor[i].tipo == OPER) i++;
        else r = FALSE;

        if (r && Parentetica.Vetor[i].tipo == NUM) i++;
        else if (r && Parentetica.Vetor[i].tipo == ABPAR) 
            r = TesteRecursivo ();
        else r = FALSE;
        
        if (r && Parentetica.Vetor[i].tipo == FPAR) i++;
        else r = FALSE;
	}
	else r = FALSE;
  	return r;
}

logic ParenteticaCorreta () {
	logic r;
	i = 0;
	r = TesteRecursivo();
	if (i < Parentetica.natom) r = FALSE;
 	return r;
}

/* Funções operadoras para a pilha */

void Empilhar (atomo x, pilha *P) { 
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

atomo Topo (pilha P) {
    if (! Vazia(P)) return P->elem;
}

void InicPilha (pilha *P) { *P = NULL; }

logic Vazia (pilha P) {
	if (P == NULL) return TRUE; 
    else return FALSE; 
}

/*	Função que forma a polonesa a partir da parentética	*/

void FormarPolonesa (){
    pilha operadores;
    int k, u = 0;

    polonesa.natom = 0;

    InicPilha(&operadores);

    for (k = 0; k < Parentetica.natom; k++)
    {
        if (Parentetica.Vetor[k].tipo != ABPAR)
        {
            if (Parentetica.Vetor[k].tipo == NUM)
            {
                polonesa.Vetor[u] = Parentetica.Vetor[k];
                printf ("%g ",polonesa.Vetor[u].atrib.valor);
                polonesa.natom++;
                u++;
            }
            else if (Parentetica.Vetor[k].tipo == OPER)
            {
                Empilhar(Parentetica.Vetor[k], &operadores);
            }
            else if (Parentetica.Vetor[k].tipo == FPAR)
            {
                polonesa.Vetor[u] = operadores->elem;
                Desempilhar(&operadores);
                printf ("%c ",polonesa.Vetor[u].atrib.carac);
                polonesa.natom++;
                u++;
            }
        }
    }
}

void Resultado(){
    pilha conta;
    int k;
    atomo aux1,aux2;

    InicPilha(&conta);

    for (k = 0; k < polonesa.natom; k++)
    {
        if (polonesa.Vetor[k].tipo == NUM)
        {
            Empilhar(polonesa.Vetor[k], &conta);   
        }
        else
        {
            if (polonesa.Vetor[k].atrib.carac == '+')
            {
                aux1 = conta->elem;
                Desempilhar(&conta);
                aux2 = conta->elem;
                Desempilhar(&conta);
                aux2.atrib.valor += aux1.atrib.valor;

                Empilhar(aux2,&conta);
            }
            else if (polonesa.Vetor[k].atrib.carac == '*')
            {
                aux1 = conta->elem;
                Desempilhar(&conta);
                aux2 = conta->elem;
                Desempilhar(&conta);
                aux2.atrib.valor *= aux1.atrib.valor;

                Empilhar(aux2,&conta);
            }
            else if (polonesa.Vetor[k].atrib.carac == '~')
            {
                aux1 = conta->elem;
                Desempilhar(&conta);
                aux1.atrib.valor = (-1)*aux1.atrib.valor;

                Empilhar(aux1,&conta);

            }
            else if (polonesa.Vetor[k].atrib.carac == '/')
            {
                aux1 = conta->elem;
                Desempilhar(&conta);
                aux2 = conta->elem;
                Desempilhar(&conta);
                aux2.atrib.valor /= aux1.atrib.valor;

                Empilhar(aux2,&conta);
            }
            else if (polonesa.Vetor[k].atrib.carac == '^')
            {
                aux1 = conta->elem;
                Desempilhar(&conta);
                aux2 = conta->elem;
                Desempilhar(&conta);
                aux2.atrib.valor = pow(aux2.atrib.valor, aux1.atrib.valor);

                Empilhar(aux2,&conta);
            }
            else if (polonesa.Vetor[k].atrib.carac == 'R')
            {
                aux1 = conta->elem;
                Desempilhar(&conta);
                aux1.atrib.valor = sqrt(aux1.atrib.valor);

                Empilhar(aux1,&conta);
            }
            else if (polonesa.Vetor[k].atrib.carac == 'L')
            {
                aux1 = conta->elem;
                Desempilhar(&conta);
                aux2 = conta->elem;
                Desempilhar(&conta);
                aux2.atrib.valor = (1/log10(aux1.atrib.valor))*log10(aux2.atrib.valor);

                Empilhar(aux2,&conta);
            }
            
        }
        
    }

    printf ("\n\nO resultado e': %g",conta->elem.atrib.valor);
    


}










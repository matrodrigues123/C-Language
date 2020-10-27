/*	Declaracoes globais   */

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

typedef struct infolocal infolocal;
struct infolocal {
  	posicao posic; logic estah;
};

lista Estoque;               

/*	Prototipos das funcoes independentes da estrutura de dados  */

void ExibirMenu (void);
void AdicionarUnidades (void);
void RetirarUnidades (void);
void NumeroUnidsEletro (void);
void ListarEstoque (void);

/*	Prototipos das funcoes dependentes da estrutura de dados  */

void InicializarEstoque (void);
void Inserir (eletrodomestico, posicao);
void Deletar (posicao);
void MaisUnidades (int, posicao);
void MenosUnidades (int, posicao);
infolocal Local (string);
posicao Primeira (void);
eletrodomestico Elemento (posicao);
posicao Proxima (posicao);
posicao Fim (void);
logic EstoqueVazio (void);

/*	Funcao principal             */

int main () {
	char c;
	printf ("Controle do Estoque de Eletrodomesticos\n\n");
   	InicializarEstoque ();
	ExibirMenu ();
	c = getche ();
	printf ("\n\n");
	printf ("Digitado: %c\n\n", c); 
	while (c != 'F' && c != 'f') {
		switch (c) {
			case 'A': case 'a':
				AdicionarUnidades (); break;
			case 'R': case 'r':
				RetirarUnidades (); break;
			case 'N': case 'n':
				NumeroUnidsEletro (); break;
			case 'L': case 'l':
				ListarEstoque (); break;
		}
		ExibirMenu ();
		c = getche ();
		printf ("\n\n");
		printf ("Digitado: %c\n\n", c);
	}
   	printf ("Fim das operacoes!");
   	printf ("\n\n");
	system ("pause");
	return 0;
}

/*	FUNCOES INDEPENDENTES DA ESTRUTURA DE DADOS  */

/* Funcao para mostrar o menu de operacoes no estoque  */

void ExibirMenu () {
	printf ("A - para adicionar unidades a um eletrodomestico\n");
	printf ("R - para retirar unidades de um eletrodomestico\n");
	printf ("N - para informar o numero de unidades de um eletrodomestico\n");
	printf ("L - para listar todo o estoque\n");
	printf ("F - para encerrar as operacoes:\n");

}

/* Funcao para adicionar no estoque unidades de um eletrodomestico */

void AdicionarUnidades () {
	eletrodomestico eletro; infolocal loc;
   	string nome; int unids;
	printf ("Adicao de unidades a um eletrodomestico\n\n");
	printf ("Nome: ");
	setbuf (stdin, NULL); gets (nome);
	printf ("Unidades adicionadas: "); 
	scanf ("%d", &unids);
   	loc = Local (nome);
	if (loc.estah == TRUE)
		MaisUnidades (unids, loc.posic);
	else {
   		strcpy (eletro.nome, nome); eletro.unids = unids;
		Inserir (eletro, loc.posic);
	}
	printf ("\nDigite algo para continuar: ");
	getch ();
}

/* Funcao para retirar do estoque unidades de um eletrodomestico */

void RetirarUnidades () {
	eletrodomestico eletro; infolocal loc;
   	string nome; int unids;

	printf ("Retirar unidades de um eletrodomestico\n\n");
	printf ("Nome: ");
	setbuf (stdin, NULL); gets (nome);
	printf ("Unidades retiradas: "); 
	scanf ("%d", &unids);
	loc = Local (nome);
	if (loc.estah == TRUE && loc.posic->eletro.unids != unids){
		MenosUnidades (unids, loc.posic);
	}
	else if (loc.estah == TRUE && loc.posic->eletro.unids == unids)
		Deletar (loc.posic);
	else
		printf ("O eletrodomestico nao esta contido no estoque");
	printf ("\nDigite algo para continuar: ");
	getch ();
	
}

/* Funcao para informar o numero de unidades de um eletrodomestico no estoque                                                          */

void NumeroUnidsEletro () {
	eletrodomestico eletro; infolocal loc;
   	string nome; int unids;
	printf ("Nome: ");
	setbuf (stdin, NULL); gets (nome);
	loc = Local (nome);
	if (loc.estah == TRUE)
	{
		eletro = Elemento(loc.posic);
		printf ("O eletrodoméstico procurado possui %d unidades em estoque.", eletro.unids);
	}
	else
	{
		printf ("O eletrodoméstico não está no estoque.");
	}
	printf ("\nDigite algo para continuar: ");
	getch ();
	
	
}

/* Funcao para listar as informacoes de todos os eletrodomesticos no estoque                                     */

void ListarEstoque () {
	posicao p;
	if (EstoqueVazio() == TRUE)
    {
        printf ("\nEstoque vazio\n");
    } 	
	else 
    {
		printf ("\n%22s|%10s\n", "Nome        ", "Unidades");
		printf ("-----------------------------------\n");
		for (p = Proxima(Primeira()); p != NULL && p->prox != NULL; p = Proxima(p))
        {
            printf ("%22s|%10d\n", p->eletro.nome, p->eletro.unids);
        }
	}
	printf ("\nDigite algo para continuar: ");
	getch ();
	printf ("\n");
}

/*	FUNCOES DEPENDENTES DA ESTRUTURA DE DADOS  */

void InicializarEstoque () {
	posicao p;
	p = (noh *) malloc (sizeof (noh));
	Estoque.inic = Estoque.fim = p;
	p->prox = NULL;
}

void Inserir (eletrodomestico eletro, posicao p) {
	Estoque.fim->prox = (noh *) malloc (sizeof (noh));
	Estoque.fim = Estoque.fim->prox;

	p = Estoque.fim;
	p->eletro = eletro;

}

void Deletar (posicao p) {
	posicao percorre,
			apaga;

	percorre = Estoque.inic;
	apaga = p;

	while (percorre->prox != apaga && percorre->prox != NULL)
	{
		percorre = percorre->prox;
	}

	if (apaga != Estoque.fim && apaga != Estoque.inic)
	{
		percorre->prox = apaga->prox;
		free(apaga);
	}
	else
	{
		Estoque.fim = percorre;
		percorre->prox = NULL;
		free(apaga);
	}
	
	
}

void MaisUnidades (int unids, posicao p) {
	p->eletro.unids += unids;
}

void MenosUnidades (int unids, posicao p) {
	p->eletro.unids -= unids;
}

infolocal Local (string nome) {
	posicao pont1;
	infolocal loc1;

	loc1.posic = NULL;
	loc1.estah = FALSE;

	for (pont1 = Estoque.inic; pont1 != Estoque.fim && loc1.estah == FALSE; pont1 = pont1->prox)
	{
		if (strcmp(pont1->eletro.nome, nome) == 0)
		{
			loc1.posic = pont1;
			loc1.estah = TRUE;
		}
		
	}

	return loc1;
	
}

posicao Primeira (void) {
	posicao primeira;
	primeira = Estoque.inic;

	return primeira;
	
}

eletrodomestico Elemento (posicao p) 
{
	eletrodomestico eletroProcurado;
	eletroProcurado = p->eletro;

	return eletroProcurado;

}

posicao Proxima (posicao p) {
	posicao proxima;
	proxima = p->prox;

	return proxima;
}

posicao Fim (void) {
	posicao fim;
	fim = Estoque.fim;

	return fim;
}

logic EstoqueVazio (void) {
	if (Estoque.inic->prox == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}




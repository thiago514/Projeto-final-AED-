#include <stdio.h>
#include <stdlib.h>

typedef struct _no{
	void *e;
	struct _no *prox;
}No;

typedef struct _lista{
	No *primeiro;
	No *ultimo;
	int tamanho;
}Lista;

typedef struct {
    Lista* gibis;
    char nome[20];
}Pessoa;

typedef struct {
    char nome[20];
}Gibis;

Lista* criarLista(){
	Lista *novaLista = (Lista*) malloc(sizeof(Lista));
	novaLista->primeiro = NULL;
	novaLista->ultimo = NULL;
	novaLista->tamanho = 0;
	return novaLista;
}

void inserir(Lista *lista, void *novoElemento){
	No *novoNo = (No*) malloc(sizeof(No));
	novoNo->e = novoElemento;
	novoNo->prox = NULL;

	if(lista->tamanho == 0){
		lista->primeiro = novoNo;
		lista->ultimo = novoNo;
		lista->tamanho++;
	}else{
		lista->ultimo->prox = novoNo;
		lista->ultimo = novoNo;
		lista->tamanho++;
	}
}

int remover(Lista *lista, int pos){
	if(pos < 0 || pos>= lista->tamanho)
		return -1;
	No *removido;
	if(lista->tamanho == 1 && pos == 0){
		removido = lista->primeiro;
		free(removido);
		lista->primeiro = NULL;
		lista->ultimo = NULL;
		lista->tamanho--;
		return 0;
	}
	if(pos == 0){
		removido = lista->primeiro;
		lista->primeiro = lista->primeiro->prox;
		free(removido);
		lista->tamanho--;
		return 0;
	}
	No *aux = lista->primeiro;
	int i;
	for(i=0; i<pos-1; i++){
		aux = aux->prox;
	}
	removido = aux->prox;
	aux->prox = aux->prox->prox;
	free(removido);
	if(lista->tamanho-1 == pos){
		lista->ultimo = aux;
	}
	lista->tamanho--;
	return 0;
}

void listarListaPessoa(Lista* lista){
    No *aux = lista->primeiro;
    Pessoa *a;
	int id = 0;
    printf("id        dados\n");
    while(aux != NULL){
        a = (Pessoa*) aux->e;
        printf("%d - %s\n",id ,a->nome);
        aux = aux->prox;
		id++;
    }
    printf("\n\n");
}

void listarListaGibi(Lista* lista){
    No *aux = lista->primeiro;
    Gibis *a;
	int id = 0;
    printf("id        dados\n");
    while(aux != NULL){
        a = (Gibis*) aux->e;
        printf("%d - %s\n",id ,a->nome);
        aux = aux->prox;
		id++;
    }
    printf("\n\n");
}

Pessoa* buscarPessoa(Lista *lista, int pos){
	int i;
	if(pos < 0 || pos>= lista->tamanho)
		return NULL;
	No *aux = lista->primeiro;
	for(i=0; i<pos; i++)
		aux = aux->prox;
	return aux->e;
}

Gibis* buscarGibi(Lista *lista, int pos){
	int i;
	if(pos < 0 || pos>= lista->tamanho)
		return NULL;
	No *aux = lista->primeiro;
	for(i=0; i<pos; i++)
		aux = aux->prox;
	return aux->e;
}


void menu(){
    puts("1 - adicionar pessoa a lista");
    puts("2 - adicionar um gibi a lista");
    puts("3 - adicionar uma pessoa a fila");
    puts("4 - adicionar um gibi a pilha");
    puts("5 - anexar um gibi a uma pessoa da fila");
	puts("6 - exibir listas");
    puts("7 - Exit");
}

void menuExibirListas(Lista* pessoas, Lista* gibis, Lista* fila_pessoas, Lista* pilha_gibis){
	int op, id;
	puts("1 - Exibir lista Pessoas\n");
	puts("2 - Exibir lista gibis\n");
	puts("3 - Exibir fila Pessoas\n");
	puts("4 - Exibir pilha Gibis\n");
	puts("5 - Exibir gibis de uma pessoa\n");
	scanf("%d", &op);
	switch (op)
	{
	case 1:
		listarListaPessoa(pessoas);
	break;
	case 2:
		listarListaGibi(gibis);
	break;
	case 3:
		listarListaPessoa(fila_pessoas);
	break;
	case 4:
		listarListaGibi(pilha_gibis);	
	default:
	case 5:
		listarListaPessoa(pessoas);
		puts("digite o id da pessoa que deseja visualisar os gibis");
		scanf("%d", &id);
		listarListaGibi(buscarPessoa(pessoas,id)->gibis);
		break;
	}
}


int main (){
    Lista* pessoas = criarLista();
    Lista* gibis = criarLista();
    Lista* fila_pessoas = criarLista();
    Lista* pilha_gibis = criarLista();
    int id, op = 0;
	char choice;
	Pessoa *pessoa;
	Gibis *gibi;
	
    while (op!=7)
    {
        menu();
        scanf("%d", &op);
        switch (op){
            case 1:
			pessoa = malloc(sizeof(Pessoa));
            puts("Digite o nome da pessoa que deseja adicionar");
			scanf("%s", pessoa->nome);
			pessoa->gibis = criarLista();
			inserir(pessoas, (void*)pessoa);
			puts("adicionado com sucesso\n");
            break;
            case 2:
			gibi = malloc(sizeof(Gibis));
            puts("Digite o titulo do gibi que deseja adicionar");
			scanf("%s", gibi->nome);
			inserir(gibis, (void*)gibi);
			puts("adicionado com sucesso\n");
            break;
            case 3:
			listarListaPessoa(pessoas);
            puts("Digite o ID da pessoa que deseja inserir na fila\n");
			scanf("%d", &id);
			inserir(fila_pessoas, buscarPessoa(pessoas, id));
			puts("adicionado com sucesso\n");
            break;
            case 4:
            listarListaGibi(gibis);
            puts("Digite o ID do gibi que deseja inserir na fila\n");
			scanf("%d", &id);
			inserir(pilha_gibis, buscarGibi(gibis, id));
			puts("adicionado com sucesso\n");
            break;
            case 5:
            inserir(buscarPessoa(fila_pessoas,0)->gibis,buscarGibi(pilha_gibis,(pilha_gibis->tamanho-1)));
			// o -1 já que a lista começa com o elemento 0
			remover(pilha_gibis, (pilha_gibis->tamanho-1));
			puts("deseja que a pessoa volte para o final da fila?(s/n)\n");
			scanf("%c", &choice);
			if(choice == 's'){
				inserir(fila_pessoas, buscarPessoa(fila_pessoas,0));
			}
			remover(fila_pessoas, 0);
            break;
			case 6:
			menuExibirListas(pessoas, gibis, fila_pessoas, pilha_gibis);
			break;
			case 7:
			op = 7;
			break;
            default:
                puts("opção invalida\n");
            break;
        }
    }
    



    return 0;
}
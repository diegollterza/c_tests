#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

typedef struct Recurso{
    int cod;
    char tipo;
    int tam;
    float preco;
    struct Recurso *prox;
 } Recurso;

typedef struct Base{
    int capacidade;
    char tipo;
    int espacoOcupado;
    float valorArmazenado;
    Recurso *Recursos;
    struct Base *prox;
    char apelido[255];
    char cod[8];
} Base;

 int verificaCodigo(char cod[8], Base *head){
    Base *aux = head;
    while(aux!=NULL){
        if(strcmp(aux->cod, cod)==0){
            printf("Retornado True \n");
            return true;
        }
        aux = aux->prox;
    }
    return false;
 }

 void imprimeBase(Base base){
        printf("%s \n", base.cod);
        printf("%s \n", base.apelido);
        printf("%c \n", base.tipo);
        printf("%d \n", base.capacidade);
        printf("%d \n", base.espacoOcupado);
        printf("%.2f \n", base.valorArmazenado);
    }
 void imprimeRecurso(Recurso recurso){
    printf("%d \n", recurso.cod);
    printf("%d \n", recurso.tam);
    printf("%c \n", recurso.tipo);
    printf("%.2f \n", recurso.preco);
 }


 Base * cadastrarBase(Base *head){
    Base *aux = head;
    Base *novo = malloc(sizeof(Base));
    printf("Entre com o código \n");
    scanf("%s", novo->cod);
    while(verificaCodigo(novo->cod, head)){
        printf("Codigo ja existente.\n");
        scanf("%s ", novo->cod);
    }

    printf("Entre com o Apelido \n");
    scanf(" %s", novo->apelido);
    printf("Entre com o Tipo \n");
    scanf(" %c", &novo->tipo);
    printf("Entre com a capacidade \n");
    scanf("%d", &novo->capacidade);
    novo->espacoOcupado = 0;
    novo->valorArmazenado = 0;
    novo->Recursos = NULL;
    novo->prox = NULL;
    if(aux == NULL){
        head = novo;
    }
    while(aux != NULL){
        aux = aux->prox;
    }
    aux = novo;
    return head;
 }


Base * cadastrarRecurso(Base *head){
    Base *aux = head;
    Recurso * novo = malloc(sizeof(Recurso));
    char cod[8];
    printf("Digite o codigo da base na qual deseja adcionar o recurso:\n");
    scanf("%s", cod);
    while(!verificaCodigo(cod,head)){
        printf("Codigo nao existe.\n");
        scanf("%s", cod);
    }
    printf("Digite o codigo do Recurso \n");
    scanf("%d", &novo->cod);
    printf("Digite o tipo do Recurso \n");
    scanf(" %c", &novo->tipo);
    printf("Digite o tamanho do Recurso \n");
    scanf("%d", &novo->tam);
    printf("Digite o preco do Recurso \n");
    scanf("%f", &novo->preco);

    while(strcmp(aux->cod,cod)!=0){
        aux = aux->prox;
    }

    novo->prox = aux->Recursos;
    aux->Recursos = novo;
    aux->espacoOcupado = calculaCapacidade(aux);
    return head;
}

 Base * removerUltimoRecurso(Base *head, char cod[8]){
    Base *aux = head;
    Recurso *r_aux = NULL;
    Recurso *r_ant = NULL;
    while(aux!=NULL){
        if(strcmp(aux->cod,cod)==0){
            break;
        }
        aux = aux->prox;
    }

    if(aux == NULL){
        printf("Codigo nao encontrado. \n");
        return;
    }

    if(aux->Recursos==NULL){
        printf("Base nao possui recursos \n");
        return;
    }
    r_aux = aux->Recursos;
    if(r_aux->prox == NULL){
    	printf("%d \n", r_aux->cod);
        aux->Recursos = NULL;
        free(r_aux);
        return;
    }

    while(r_aux->prox!=NULL){
        r_ant = r_aux;
        r_aux = r_aux->prox;
    }
    aux->espacoOcupado = calculaCapacidade(aux);
    printf("%d \n", r_aux->cod);
    free(r_aux);
    r_ant->prox= NULL;
    return head;
 }

int hasRecursoTipo(Base * head, char tipo){
	Recurso * aux = head->Recursos;
	while(aux){
		if(aux->tipo == tipo){
			return true;
		}
		aux = aux->prox;
	}
	return false;
}

void listarBases(Base * head, char tipo){
	while(head){
		if(hasRecursoTipo(head, tipo)){
			printf("%s \n", head->apelido);
		}
		head = head->prox;
	}
}

int calculaCapacidade(Base * head){
	int soma = 0;
	Recurso * aux = head->Recursos;

	while(aux){
		soma += aux->tam;
		aux = aux->prox;
	}
	return soma;
}

void listarBasesLimite(Base * head){
	while(head != NULL){
		if(head->capacidade < head->espacoOcupado){
			printf("%s \n", head->apelido);
		}
		head = head->prox;
	}
}
Base * moverRecursoBase(Base * head, char origem[8], char destino[8]){
	Base * b_origem = NULL;
	Base * b_destino = NULL;
	Base * aux = head;
	Recurso * r_origem = NULL;
	Recurso * r_destino = NULL;
	Recurso * r_aux = NULL;
	while(aux){
		if (strcmp(aux->cod, origem)==0){
			b_origem = aux;
		}
		aux = aux->prox;
	}
	if(!b_origem){
		printf("Base origem nao encontrada. \n");
		return;
	}
	aux = head;
	while(aux){
		if (strcmp(aux->cod, destino)==0){
			b_destino = aux;
		}
		aux = aux->prox;
	}
	if(!b_destino){
		printf("Base destino nao encontrada. \n");
		return;
	}
	r_origem = b_origem->Recursos;
	r_destino = b_destino->Recursos;
	
	while(r_origem){
		r_aux = r_origem;
		r_aux->prox = r_destino;
		r_destino = r_aux;
		r_origem = r_origem->prox;
	}
	return head;
}

void ListarTudo(Base * head){
	Recurso  *aux = NULL;
	while(head){
		printf("%s \n", head->apelido);
		aux = head->Recursos;
		while(aux){
			printf("%d %c \n", aux->cod, aux->tipo);
			aux = aux->prox;
		}
		head = head->prox;
	}
}

void printMenu(){
    printf("############################MENU############################## \n");
    printf("1 - Cadastrar Base\n");
    printf("2 - Cadastrar Recurso\n");
    printf("3 - Remover Ultimo Recurso\n");
    printf("4 - Listar Recursos da Base\n");
    printf("5 - Listar Bases excedido limite\n");
    printf("6 - Mover recursos entre Bases\n");
    printf("7 - Listar todas as Bases e Recursos\n");
    printf("8 - Sair \n");
}

 int main(){
    int menu = 0;
    Base *head = NULL;
    char origem[8];
    char destino[8];
    char tipo;
	char cod[8];
	while(menu!=8){
		printMenu();
		scanf("%d", &menu);
    	switch(menu){
    		case 1:
    			head = cadastrarBase(head);
    		case 2:
    			head = cadastrarRecurso(head);
    		case 3:
    			scanf("%s", cod);
    			head = removerUltimoRecurso(head, cod);
  		  	case 4:
    			scanf(" %c", &tipo);
    			listarBases(head, tipo);
	    	case 5:
    			listarBasesLimite(head);
    		case 6:
    			scanf("%s", origem);
    			scanf("%s", destino);
    			head = moverRecursoBase(head, origem, destino);
    		case 7:
    			ListarTudo(head);
    		case 8:
    			break;
    	}	
    }
    return 0;
 }

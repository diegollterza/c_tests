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
    char cod[8];
    char apelido[255];
    char tipo;
    int capacidade;
    int espacoOcupado;
    float valorArmazenado;
    Recurso *Recursos;
    struct Base *prox;
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
    char cod[8];
    char apelido[255];
    char tipo;
    int capacidade;
    printf("Entre com o código \n");
    scanf("%s", cod);
    /*while(verificaCodigo(cod, head)){
        printf("Codigo ja existente.\n");
        scanf("%s", cod);
    }*/

    printf("Entre com o Apelido \n");
    scanf("%s", apelido);
    printf("Entre com o Tipo \n");
    scanf(" %c", &tipo);
    printf("Entre com a capacidade \n");
    scanf("%d", &capacidade);
    printf("%s \n", cod);
    strcpy(novo->cod,cod);
    //strcpy(novo->apelido,apelido);
    novo->tipo = tipo;
    novo->capacidade = capacidade;
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
    printf("%s \n", aux->cod);
    return head;
 }


Base * cadastrarRecurso(Base *head){
    Base *aux = head;
    Recurso * novo = malloc(sizeof(Recurso));
    char cod[8];
    printf("Digite o codigo da base na qual deseja adcionar o recurso:\n");
    scanf("%s", cod);
    while(verificaCodigo(cod,head)==false){
        printf("Codigo nao existe.\n");
        scanf("%s", cod);
    }
    printf("Digite o codigo do Recurso \n");
    scanf("%d", &novo->cod);
    printf("Digite o tipo do Recurso \n");
    scanf("%c", &novo->tipo);
    printf("Digite o tamanho do Recurso \n");
    scanf("%d", &novo->tam);
    printf("Digite o preco do Recurso \n");
    scanf("%f", &novo->preco);

    while(aux->cod != cod){
        aux = aux->prox;
    }
    novo->prox = aux->Recursos;
    aux->Recursos = novo;
    return head;
}

 void removerUltimoRecurso(Base *head, char cod[8]){
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
        aux->Recursos = NULL;
        free(r_aux);
        return;
    }

    while(r_aux->prox!=NULL){
        r_ant = r_aux;
        r_aux = r_aux->prox;
    }
    free(r_aux);
    r_ant->prox= NULL;
 }

 int main(){
    Base *head = NULL;
    head = cadastrarBase(head);
    //printf("%s",head->apelido);
    head = cadastrarRecurso(head);
    removerUltimoRecurso(head, "12345678");
    return 0;
 }

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

 int verificaCodigo(char *codigo, Base *head){
    Base *aux = head;
    while(aux!=NULL){
        if(strcmp(aux->cod, codigo)==0){
            return true;
        }
        printf("%s", aux->apelido);
        aux = aux->prox;
    }
    return false;
 }

 void imprimeBases(Base *head){
    Base *aux = head;
    while(aux!=NULL){
        printf("%s \n", aux->cod);
        aux = aux->prox;
    }



 }

 Base * cadastrarBase(Base *head){
    Base *aux = head;
    Base *novo = malloc(sizeof(Base));
    printf("Entre com o código \n");
    scanf("%s", novo->cod);
    while(verificaCodigo(novo->cod, head)){
        printf("Codigo ja existente.\n");
        scanf("%s", novo->cod);
    }
    printf("Entre com o Apelido \n");
    scanf("%s", novo->apelido);
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

void cadastrarRecurso(Base *head){
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
}

 int main(){
    Base *head = NULL;
    head = cadastrarBase(head);
    printf("%s",head->apelido);
    imprimeBases(head);
    //cadastrarRecurso(head);
    return 0;
 }

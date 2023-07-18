#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

// Tipo que define o produto
typedef struct produto {
    char *nome;
    int codigo;
    float valor;
    int *data_de_validade;
} Produto;

// Tipo que define a lista
typedef struct lista {
    Produto *produto;
    struct lista *prox;
} Lista;

/* Cria um novo produto */
struct produto* CriaProduto(char* nome, int codigo, float valor, int* data_de_validade) {
    struct produto* novo_produto = (struct produto*)malloc(sizeof(struct produto));
    strcpy(novo_produto->nome, nome);
    novo_produto->codigo = codigo;
    novo_produto->valor = valor;
    memcpy(novo_produto->data, data_de_validade, sizeof(int) * 3);
    return novo_produto;
}

/* Cria uma nova lista */
struct lista* CriaLista() {
    struct lista* nova_lista = (struct lista*)malloc(sizeof(struct lista));
    nova_lista->p = NULL;
    nova_lista->prox = NULL;
    return nova_lista;
}

/* Insere um produto em uma lista */
void InsereListaProduto(struct lista* l, struct produto* p) {
    if (l->p == NULL) {
        l->p = p;
    } else {
        struct lista* nova_lista = CriaLista();
        nova_lista->p = p;
        nova_lista->prox = l->prox;
        l->prox = nova_lista;
    }
}

/* Retira um produto de uma determinada lista */
void RetiraListaProduto(struct lista** l, int id_produto) {
    struct lista* anterior = NULL;
    struct lista* atual = *l; // Correção nesta linha

    while (atual != NULL) {
        if (atual->p->codigo == id_produto) {
            if (anterior == NULL) {
                *l = atual->prox; // Correção nesta linha
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

/* Verifica se um produto está presente em uma determinada lista */
int VerificaListaProduto(struct lista* l, int id_produto) {
    struct lista* atual = l;

    while (atual != NULL) {
        if (atual->p->codigo == id_produto) {
            return 1; // Produto encontrado
        }
        atual = atual->prox;
    }
    return 0; // Produto não encontrado
}

/* Verifica se existe um produto vencido em uma determinada lista */
int VerificaListaValidade(struct lista* l, int* data_atual) {
    int vencidos = 0;
    struct lista* atual = l;

    while (atual != NULL) {
        if (atual->p->data[0] < data_atual[0] ||
            (atual->p->data[0] == data_atual[0] && atual->p->data[1] < data_atual[1]) ||
            (atual->p->data[0] == data_atual[0] && atual->p->data[1] == data_atual[1] && atual->p->data[2] < data_atual[2])) {
            vencidos++;
        }
        atual = atual->prox;
    }
    return vencidos;
}

/* Imprime todos os produtos de uma lista */
void ImprimeListaProdutos(struct lista* l) {
    struct lista* atual = l;
    printf("Lista de Produtos:\n");
    while (atual != NULL) {
        printf("Nome: %s\n", atual->p->nome);
        printf("Código: %d\n", atual->p->codigo);
        printf("Valor: %.2f\n", atual->p->valor);
        printf("Data de validade: %d/%d/%d\n", atual->p->data[0], atual->p->data[1], atual->p->data[2]);
        printf("---------------------\n");
        atual = atual->prox;
    }
}

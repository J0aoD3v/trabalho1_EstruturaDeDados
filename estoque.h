#ifndef ESTOQUE_H_INCLUDED
#define ESTOQUE_H_INCLUDED
#include "estoque.c"

/* Cria um novo produto */
Produto* CriaProduto(char* nome, int codigo, float valor, int* data_de_validade);

Lista* CriaLista();

/* Insere um produto em uma lista */
Lista* InsereListaProduto(Lista* l, Produto* p);

/* Retira um produto de uma determinada lista */
Lista* RetiraListaProduto(Lista* l, int id_produto);

/* Verifica se um produto está presente em uma determinada lista */
int VerificaListaProduto(Lista* p, int id_produto);

/* Verifica se existe um produto vencido em uma determinada lista */
Lista* VerificaListaValidade(Lista* p);

/* Imprime todos os produtos de uma lista */
void ImprimeListaProdutos(Lista* p);

/* Ordena Lista pelo valor do produto */
Lista* OrdenaListaValor(Lista* p);

/* Ordena Lista pelo valor do produto */
Lista* OrdenaListaVencimento(Lista* p);

#endif // ESTOQUE_H_INCLUDED

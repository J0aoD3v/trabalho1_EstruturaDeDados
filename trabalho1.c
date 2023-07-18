#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

struct produto {
    char nome[20];
    int codigo;
    float valor;
    int data[3];
};

struct lista {
    struct produto *p;
    struct lista *prox;
};

int main() {
    FILE* entrada = fopen("D:\\ARQUIVOS\\Downloads\\TrabalhoFelix\\trabalho1\\entrada.txt", "r");
    FILE* saida = fopen("D:\\ARQUIVOS\\Downloads\\TrabalhoFelix\\trabalho1\\saida.txt", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir os arquivos de entrada ou saída.\n");
        return 1;
    }

    struct lista* estoque = CriaLista();

    char comando[20];
    while (fscanf(entrada, "%s", comando) != EOF) {
        if (strcmp(comando, "PRODUTO") == 0) {
            char nome[20];
            int codigo, dia, mes, ano;
            float valor;
            fscanf(entrada, "%s %d %f %d %d %d", nome, &codigo, &valor, &dia, &mes, &ano);
            struct produto* p = CriaProduto(nome, codigo, valor, (int[3]){dia, mes, ano});
            InsereListaProduto(estoque, p);
        } else if (strcmp(comando, "RETIRA") == 0) {
            int codigo_produto_retirar;
            fscanf(entrada, "%d", &codigo_produto_retirar);
            RetiraListaProduto(&estoque, codigo_produto_retirar);
        } else if (strcmp(comando, "IMPRIME_LISTA") == 0) {
            ImprimeListaProdutos(estoque);
        } else if (strcmp(comando, "ATUALIZA_PRECO") == 0) {
            int codigo_produto_atualizar;
            float novo_valor;
            fscanf(entrada, "%d %f", &codigo_produto_atualizar, &novo_valor);
            AtualizaPrecoProduto(estoque, codigo_produto_atualizar, novo_valor);
        } else if (strcmp(comando, "VERIFICA_VALIDADE") == 0) {
            int dia, mes, ano;
            fscanf(entrada, "%d %d %d", &dia, &mes, &ano);
            int vencidos = VerificaListaValidade(estoque, (int[3]){dia, mes, ano});
            fprintf(saida, "Existem %d produtos vencidos.\n", vencidos);
        } else if (strcmp(comando, "VERIFICA_LISTA") == 0) {
            int codigo_produto;
            fscanf(entrada, "%d", &codigo_produto);
            int encontrado = VerificaListaProduto(estoque, codigo_produto);
            if (encontrado) {
                fprintf(saida, "O produto de código %d está presente na lista.\n", codigo_produto);
            } else {
                fprintf(saida, "O produto de código %d não está presente na lista.\n", codigo_produto);
            }
        } else if (strcmp(comando, "ORDENA_LISTA_VALIDADE") == 0) {
            estoque = OrdenaListaValidade(estoque);
        } else if (strcmp(comando, "ORDENA_LISTA_VALOR") == 0) {
            estoque = OrdenaListaValor(estoque);
        }
    }

    // Fechar os arquivos
    fclose(entrada);
    fclose(saida);

    // Liberar memória alocada
    struct lista* atual = estoque;
    while (atual != NULL) {
        struct lista* prox = atual->prox;
        free(atual->p);
        free(atual);
        atual = prox;
    }

    return 0;
}

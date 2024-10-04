#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contato {
    char nome[50];
    char telefone[20];
    char email[50];
} Contato;

typedef struct No {
    Contato contato;
    struct No* proximo;
    struct No* anterior;
} No;

No* criarContato(char nome[], char telefone[], char email[]) {
    No* novoNo = (No*) malloc(sizeof(No));
    strcpy(novoNo->contato.nome, nome);
    strcpy(novoNo->contato.telefone, telefone);
    strcpy(novoNo->contato.email, email);
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;
    return novoNo;
}

No* inserirInicio(No* lista, char nome[], char telefone[], char email[]) {
    No* novoNo = criarContato(nome, telefone, email);
    novoNo->proximo = lista;
    if (lista != NULL) {
        lista->anterior = novoNo;
    }
    return novoNo;
}

No* removerPorNome(No* lista, char nome[]) {
    No* atual = lista;

    while (atual != NULL && strcmp(atual->contato.nome, nome) != 0) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Contato nao encontrado.\n");
        return lista;
    }

    if (atual == lista) {
        lista = atual->proximo;
        if (lista != NULL) {
            lista->anterior = NULL;
        }
    } else {
        if (atual->anterior != NULL) {
            atual->anterior->proximo = atual->proximo;
        }
        if (atual->proximo != NULL) {
            atual->proximo->anterior = atual->anterior;
        }
    }

    free(atual);
    printf("Contato removido com sucesso.\n");
    return lista;
}

void imprimirLista(No* lista) {
    if (lista == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    No* atual = lista;
    while (atual != NULL) {
        printf("Nome: %s\n", atual->contato.nome);
        printf("Telefone: %s\n", atual->contato.telefone);
        printf("Email: %s\n\n", atual->contato.email);
        atual = atual->proximo;
    }
}

void pesquisarContato(No* lista, char nome[]) {
    No* atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->contato.nome, nome) == 0) {
            printf("Contato encontrado:\n");
            printf("Nome: %s\n", atual->contato.nome);
            printf("Telefone: %s\n", atual->contato.telefone);
            printf("Email: %s\n\n", atual->contato.email);
            return;
        }
        atual = atual->proximo;
    }
    printf("Contato nao encontrado.\n");
}

void exibirMenu() {
    printf("\nSelecione uma operacao:\n");
    printf("1. Criar Agenda\n");
    printf("2. Inserir contato\n");
    printf("3. Remover contato\n");
    printf("4. Mostrar lista de contatos\n");
    printf("5. Pesquisar contato por nome\n");
    printf("X. Sair\n");
    printf("Opcao: ");
}

int main() {

    No* lista = NULL;
    char opcao;
    char nome[50], telefone[20], email[50];

    while (1) {
        exibirMenu();
        scanf(" %c", &opcao);

        if (opcao == 'X' || opcao == 'x') {
            printf("Fim do programa...\n");
            break;
        }

        switch (opcao) {
            case '1':
                printf("Digite o nome: ");
                scanf(" %49[^\n]", nome);
                printf("Digite o telefone: ");
                scanf(" %19[^\n]", telefone);
                printf("Digite o email: ");
                scanf(" %49[^\n]", email);
                lista = criarContato(nome, telefone, email);
                printf("Contato criado.\n");
                break;

            case '2':
                printf("Digite o nome: ");
                scanf(" %49[^\n]", nome);
                printf("Digite o telefone: ");
                scanf(" %19[^\n]", telefone);
                printf("Digite o email: ");
                scanf(" %49[^\n]", email);
                lista = inserirInicio(lista, nome, telefone, email);
                printf("Contato inserido no início.\n");
                break;

            case '3':
                printf("Digite o nome: ");
                scanf(" %49[^\n]", nome);
                lista = removerPorNome(lista, nome);
                break;

            case '4':
                imprimirLista(lista);
                break;

            case '5':
                printf("Digite o nome: ");
                scanf(" %49[^\n]", nome);
                pesquisarContato(lista, nome);
                break;

            default:
                printf("Opcao invalida.\n");
        }
    }

    return 0;
}

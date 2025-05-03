#include "Lista_Dupla.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void inicializarBiblioteca(Biblioteca* b) {
    b->primeiro = NULL;
    b->ultimo = NULL;
    b->totalLivros = 0;
}

int cadastrarLivro(Biblioteca* b, char* titulo, char* autor, int ano, char* isbn) {
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->livro.isbn, isbn) == 0) return 0; 
        atual = atual->proximo;
    }

    NoLivro* novo = (NoLivro*)malloc(sizeof(NoLivro));
    if (novo == NULL) return 0;
    strcpy(novo->livro.titulo, titulo);
    strcpy(novo->livro.autor, autor);
    novo->livro.ano = ano;
    strcpy(novo->livro.isbn, isbn);
    novo->livro.status = DISPONIVEL;
    novo->livro.usuario[0] = '\0';
    novo->livro.dataEmprestimo[0] = '\0';
    novo->proximo = NULL;
    novo->anterior = b->ultimo;
    if (b->ultimo) b->ultimo->proximo = novo;
    else b->primeiro = novo;
    b->ultimo = novo;
    b->totalLivros++;
    return 1;
}

void listarTodosLivros(Biblioteca* b) {
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        printf("%s - %s - %d - %s\n", 
               atual->livro.titulo, 
               atual->livro.autor, 
               atual->livro.ano, 
               atual->livro.isbn);
        printf("Status: %s\n\n", atual->livro.status == DISPONIVEL ? "Disponível" : "Emprestado");
        atual = atual->proximo;
    }
}

int emprestarLivro(Biblioteca* b, char* isbn, char* usuario, char* data) {
    NoLivro* atual = consultarLivroPorISBN(b, isbn);
    if (!atual || atual->livro.status == EMPRESTADO) return 0;

    atual->livro.status = EMPRESTADO;
    strcpy(atual->livro.usuario, usuario);
    strcpy(atual->livro.dataEmprestimo, data);
    return 1;
}

int devolverLivro(Biblioteca* b, char* isbn) {
    NoLivro* atual = consultarLivroPorISBN(b, isbn);
    if (!atual || atual->livro.status == DISPONIVEL) return 0;

    atual->livro.status = DISPONIVEL;
    atual->livro.usuario[0] = '\0';
    atual->livro.dataEmprestimo[0] = '\0';
    return 1;
}

NoLivro* consultarPorISBN(Biblioteca* b, char* isbn) {
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        if (strcmp(atual->livro.isbn, isbn) == 0) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void exibirFrente(Biblioteca* b) {
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
    printf("ISBN: %s | Título: %s\n", atual->livro.isbn, atual->livro.titulo);
        atual = atual->proximo;
    }
}

void exibirTras(Biblioteca* b) {
    NoLivro* atual = b->ultimo;
    while (atual != NULL) {
    printf("ISBN: %s | Título: %s\n", atual->livro.isbn, atual->livro.titulo);
        atual = atual->anterior;
    }
}

int removerInicio(Biblioteca* b) {
    if (!b->primeiro) return 0;
    NoLivro* temp = b->primeiro;

    b->primeiro = temp->proximo;
    if (b->primeiro) b->primeiro->anterior = NULL;
    else b->ultimo = NULL;

    free(temp);
    b->totalLivros--;
    return 1;
}

int removerFim(Biblioteca* b) {
    if (!b->ultimo) return 0;
    NoLivro* temp = b->ultimo;

    b->ultimo = temp->anterior;
    if (b->ultimo) b->ultimo->proximo = NULL;
    else b->primeiro = NULL;

    free(temp);
    b->totalLivros--;
    return 1;
}

int removerLivroPorISBN(Biblioteca* b, char* isbn) {
    NoLivro* atual = consultarLivroPorISBN(b, isbn);
    if (!atual) return 0;

    if (atual->anterior) atual->anterior->proximo = atual->proximo;
    else b->primeiro = atual->proximo;

    if (atual->proximo) atual->proximo->anterior = atual->anterior;
    else b->ultimo = atual->anterior;

    free(atual);
    b->totalLivros--;
    return 1;
}

void destruirBiblioteca(Biblioteca* b) {
    NoLivro* atual = b->primeiro;
    while (atual != NULL) {
        NoLivro* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    b->primeiro = NULL;
    b->ultimo = NULL;
    b->totalLivros = 0;
}

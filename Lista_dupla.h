#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H
#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_ISBN 14
#define MAX_USUARIO 100
#define MAX_DATA 11

typedef enum {
    DISPONIVEL,
    EMPRESTADO
} StatusLivro;

typedef struct {
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int ano;
    char isbn[MAX_ISBN];
    StatusLivro status;
    char usuario[MAX_USUARIO];
    char dataEmprestimo[MAX_DATA];
} Livro;

// Nó de lista duplamente encadeada
typedef struct NoLivro {
    Livro livro;
    struct NoLivro* proximo;
    struct NoLivro* anterior;
} NoLivro;

typedef struct {
    NoLivro* primeiro;
    NoLivro* ultimo;     // novo campo para facilitar inserção/remover no fim
    int totalLivros;
} Biblioteca;

// Protótipos
void inicializarBiblioteca(Biblioteca* b);
int cadastrarLivro(Biblioteca* b, char* titulo, char* autor, int ano, char* isbn);
void listarTodosLivros(Biblioteca* b);
int emprestarLivro(Biblioteca* b, char* isbn, char* usuario, char* data);
int devolverLivro(Biblioteca* b, char* isbn);
NoLivro* consultarLivroPorISBN(Biblioteca* b, char* isbn);
void exibirFrente(Biblioteca* b);
void exibirTras(Biblioteca* b);
int removerLivroPorISBN(Biblioteca* b, char* isbn);
int removerInicio(Biblioteca* b);
int removerFim(Biblioteca* b);
void destruirBiblioteca(Biblioteca* b);
#endif
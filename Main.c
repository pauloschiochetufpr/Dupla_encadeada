#include <stdio.h>
#include "Lista_Dupla.h"

int main() {
    Biblioteca b;
    inicializarBiblioteca(&b);
    
    printf("Cadastrando livros...\n");
    cadastrarLivro(&b, "Não Mais Humano", "Osamu Dazai", 1948, "1111");
    cadastrarLivro(&b, "Domain-Driven Design", "Eric Evans", 2003, "2222");
    cadastrarLivro(&b, "A metarmorfose", "Franz Kafka", 1915, "3333");
    
    printf("Emprestando o livro\n");
    emprestarLivro(&b, "3333", "Paulo", "01/05/2025");
    
    printf("Exibindo livros frente:\n");
    exibirFrente(&b);
    
    printf("Exibindo livros trás:\n");
    exibirTras(&b);
    
    printf("Removendo o livro\n");
    removerLivroPorISBN(&b, "2222");
    
    printf("Liberando a memória.\n");
    destruirBiblioteca(&b);
    
    return 0;
}

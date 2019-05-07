// O programa agregador funciona como filtro. Recebe pelo stdin entradas no formato do ficheiro de vendas, até end-of-file.
// Nessa altura produz para o stdout os dados agregados de cada artigo com vendas efectuadas, contendo o código do artigo,
// a quantidade total e o montante total de vendas do artigo respectivo (mantendo o formato do ficheiro de vendas).

// Para permitir explorar agregação concorrente, faça com que o servidor de vendas ponha a correr várias instâncias
// do programa agregador, dividindo o intervalo a agregar por estas, e fazendo com que os resultados das sub-agregações
// sejam por sua vez agregados.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../src/libs/readline/readline.h"

int main() {
    /* code */
    return EXIT_SUCCESS;
}

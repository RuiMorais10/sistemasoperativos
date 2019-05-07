// Este programa deve controlar stocks, receber pedidos do cliente de vendas, e registar as vendas efectuadas. 
// A quantidade em stock de cada artigo deverá ser mantida num único ficheiro STOCKS, para todos
// os artigos. Cada venda efectuada deverá ser registada, acrescentando uma entrada a um ficheiro
// VENDAS, contendo código, quantidade e montante total da venda.

// Necessario verificar se ficheiro artigos foi modificado?
// https://stackoverflow.com/questions/10324611/how-to-calculate-the-md5-hash-of-a-large-file-in-c
// ou primeira linha de artigos é alterada para um time? 

// O servidor de vendas deve ainda providenciar para correr o agregador a pedido, fazendo com que este
// receba o intervalo (para ser agregado) do ficheiro de vendas desde a última agregação, e fazendo com que
// o resultado da agregação seja escrito num ficheiro cujo nome reflecte o momento em que a agregação foi
// solicitada (e.g., 2019-03-29T14:23:56).

// Not strictly required, just in case
#include <sys/types.h>
#include <sys/stat.h>
// Normal Stuff
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

//DEBUG
#include <stdio.h>

#include "dynread.h"
int server();

int main() {
    server();
    return EXIT_SUCCESS;
}

int server() {
    char* buffer;
    int size;
    int stocks_file_descriptor = open("STOCKS", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    int vendas_file_descriptor = open("VENDAS", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    
    char* inputfifo = "/tmp/svinputfifo";
    mkfifo(inputfifo, 0666);

    while((buffer = readBuffer(&size))) {   //Cycle to parse input from stdin.
        
        free(buffer);
    }
    unlink(inputfifo);
    return EXIT_SUCCESS;
}
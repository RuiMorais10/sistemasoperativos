// Este programa deve controlar stocks, receber pedidos do cliente de vendas, e registar as vendas efectuadas. 
// A quantidade em stock de cada artigo deverá ser mantida num único ficheiro STOCKS, para todos
// os artigos. Cada venda efectuada deverá ser registada, acrescentando uma entrada a um ficheiro
// VENDAS, contendo código, quantidade e montante total da venda.

// O servidor de vendas deve ainda providenciar para correr o agregador a pedido, fazendo com que este
// receba o intervalo (para ser agregado) do ficheiro de vendas desde a última agregação, e fazendo com que
// o resultado da agregação seja escrito num ficheiro cujo nome reflecte o momento em que a agregação foi
// solicitada (e.g., 2019-03-29T14:23:56).

// Not strictly required, just in case
#include <sys/types.h>
#include <sys/stat.h>
// Normal Stuff
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h> // necessary to see when a file was last modified
#include <sys/types.h>

// DEBUG
#include <stdio.h>

// structs
#include "../../src/libs/structs/stock.h"
#include "../../src/libs/structs/artigo.h"

// libs
#include "../../src/libs/readline/readline.h"

// http://pubs.opengroup.org/onlinepubs/007908799/xsh/sysstat.h.html
/**
 * @brief Get the time the file was last modified
 * 
 * @param path      path to file
 * @return time_t   time when the file was last modified. counter starts at epoch time
 */
time_t getFileLastModified(char *path);

int main() {
    char* buffer;
    int size;
    int stocks_file_descriptor = open("STOCKS", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    int vendas_file_descriptor = open("VENDAS", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    
    char* inputfifo = "/tmp/svinputfifo";
    mkfifo(inputfifo, 0666);

	while((buffer = readline(&size))) {     //Cycle to parse input from stdin.
        
        free(buffer);
    }

    unlink(inputfifo); // close fiffo
    return EXIT_SUCCESS;
}

time_t getFileLastModified(char *path) {
    struct stat fileStat;
    stat(path, &fileStat);
    return fileStat.st_mtime;
}

// Este programa deverá permitir inserir novos artigos (especificando o nome e preço de venda), ou alterar
// atributos de um dado artigo (nome ou preço). Cada artigo tem um código numérico, atribuído na criação
// como o próximo de uma sequência (1, 2, 3, . . . ).

// Para o acesso a um artigo no ficheiro ARTIGOS poder ser feito usando o código como índice, as entradas devem ter um tamanho fixo.

// Sendo o nome de tamanho variável, este atributo no ficheiro de artigos deve conter apenas “referências” (e.g., posição)
// onde se encontram num ficheiro STRINGS, em separado, contendo os respectivos nomes.

// É aceitável que o ficheiro STRINGS contenha nomes obsoletos, desperdiçando algum espaço, de
// forma a que se possa apenas acrescentar conteúdo mesmo aquando da alteração de nomes.
// Este programa recebe todo o seu input pelo seu stdin, lendo linhas de texto com o formato do exemplo seguinte:

// $ ma
// i <nome> <preço> 		--> insere novo artigo, mostra o código
// n <código> <novo nome> 	--> altera nome do artigo
// p <código> <novo preço> 	--> altera preço do artigo
// ...
// <EOF>

// Solution:
// 	- Do not replace any string!
//	- Append new strings to the end of the file
//		- use |:| to indicate a valid product name
//		- when changing a name, switch |:| to |_| or something else, changing the pattern
//		- pattern is necessary to differentiate between valid/invalid names

// Para reduzir o desperdício de espaço, quando este superar os 20% do ficheiro, deverá ser
// feita a compactação para um novo ficheiro e ajustadas as posições no ficheiro de artigos.
// Esta operação deverá ser a última a acrescentar ao seu trabalho.

// Solution:
//  - When changing name add the distance between product (i) and (i+1) to a variable.
//	- Before the end of every cycle, calculate the size of "waste"
//		- off_t size = lseek(stringsFileDescriptor, 0, SEEK_END) - lseek(stringsFileDescriptor, 0, SEEK_SET);
//		- if waste > size * .2, then run compact
// grep -oP '(\|:\|).+[\W\S]' strings >> tmp; rm strings; mv tmp strings;
// https://gist.github.com/mplewis/5279108

// Not strictly required, just in case
#include <sys/types.h>
#include <sys/stat.h>
// Normal Stuff
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


#include "dynread.h"

// TODO REMOVE THIS BEFORE FINAL BUILD
#include <stdio.h>
// Debug only


typedef struct artigos {
	off_t offset;	// offset of the string in the file
	double price;	// price of the article
} Artigo;

void sigint_handler(int signal);

/**
 * @brief creates new Artigo
 * 
 * @param offset 	offset of string in file
 * @param price 	price of artigo
 * @return Artigo 	new Artigo
 */
Artigo newArtigo(off_t offset, double price);

/**
 * @brief compacts and remaps artigos.
 * 
 * @param artigosFileDescriptor 
 * @param stringsFileDescriptor 
 * @return int new stringsFileDescriptor
 */
int remapArtigos();

/**
 * @brief Compacts strings
 * 
 * @param  artigosFileDescriptor 
 * @param  stringsFileDescriptor 
 * @return int new stringsFileDescriptor
 */
int compactStrings();

/**
 * @brief 
 * 
 * @param productID 
 * @param productName 
 * @param productSize 
 * @param artigosFileDescriptor 
 * @param stringsFileDescriptor 
 */
void changeName(int productID, char* productName, int productSize);

/**
 * @brief 
 * 
 * @param productID 
 * @param newPrice 
 * @param artigosFileDescriptor 
 * @return int 
 */
void changePrice(int productID, int newPrice);

/**
 * @brief 
 * 
 * @param test 
 * @return int 
 */
int validPrice(char* test);

/**
 * @brief 
 * 
 * @param test 
 * @return int 
 */
int validCode(char* test);

/**
 * @brief 
 * 
 * @param productName 
 * @param wsize 
 * @param price 
 * @param artigosFileDescriptor 
 * @param stringsFileDescriptor 
 */
void insertVendas(char* productName, int wsize, double price);

int main() {
	char* buffer,* tmp;
	int size = 0;

	//  Vars required to create and/or change a product
	char *productName;
	double price = 0, productID = 0;
	size_t wsize = 0;
	
	while((buffer = readLine(&size))) {				//Cycle to parse input from stdin.
		signal(SIGINT, sigint_handler);

		if(buffer == NULL || size == 0) break;

		tmp = strtok(buffer, " ");
		if(strcmp(tmp, "i") == 0) {						// i <nome> <preço> --> insere novo artigo, mostra o código
			tmp = strtok(NULL, " ");					// i <nome>
			// TODO FALTA VALIDAR!
			productName = strdup(tmp);
			wsize = strlen(productName);
			
			tmp = strtok(NULL, " ");					// i <nome> <preço>

			if(validPrice(tmp)) {						// invalid price, free buffers
				free(productName);
				wsize = 0;
			} else {									// valid price, insert
				price = atof(tmp);
				
				insertVendas(productName, wsize, price);
			}
			free(productName);
		} else if(strcmp(tmp, "p") == 0) {				// p <código> <novo preço> --> altera preço do artigo
			tmp = strtok(NULL, " ");
			if(!validCode(tmp)) {
				productID = atoi(tmp);

				tmp = strtok(NULL, " ");
				if(!validPrice(tmp)) {
					price = atof(tmp);
					changePrice(productID, price);
				}
			}
		} else if(strcmp(tmp, "n") == 0) {				// n <código> <novo nome> --> altera nome do artigo
			tmp = strtok(NULL, " ");
			if(!validCode(tmp)) {
				productID = atoi(tmp);

				tmp = strtok(NULL, " ");
				productName = strdup(tmp);
				wsize = strlen(productName);

				changeName(productID, productName, wsize);

				free(productName);
			}
		} else if(strcmp(tmp, "s") == 0) {
			compactStrings();
		}

		free(buffer);								   // free buffer before allocating a new string onto it
	}

	return EXIT_FAILURE;
}

void sigint_handler(int signal) {
	_exit(EXIT_SUCCESS);
}

int validPrice(char* test) {
	int dotCount = 0;
	for(int i = 0; i < strlen(test); i++) {
		if(test[i] == '.') {
			dotCount += 1;
		} else if(test[i] < '0' || test[i] > '9' || (dotCount > 1)) {
			return 1;
		}
	}
	return 0;
}

int validCode(char* test) {
	for(int i = 0; i < strlen(test); i++)
		if(test[i] < '0' || test[i] > '9') return 1;
	return 0;
}

void changeName(int productID, char* productName, int productSize) {
	//  Open files "artigos" and "strings"
	//  If the files don't exist, create them.
	int artigosFileDescriptor = open("artigos", O_RDWR | O_CREAT, S_IRWXO );
	int stringsFileDescriptor = open("strings", O_RDWR | O_CREAT, S_IRWXO );

	off_t end = lseek(artigosFileDescriptor, 0, SEEK_END);
	off_t offset = lseek(artigosFileDescriptor, ((productID - 1) * sizeof(struct artigos)), SEEK_SET);

	off_t str_start = lseek(stringsFileDescriptor, 0, SEEK_SET);

	if(offset < end) {	// if( offset < end ) => artigo exists, check offset to invalidate the string
		Artigo fromFile;
		if(read(artigosFileDescriptor, &fromFile, sizeof(struct artigos))) {
			lseek(stringsFileDescriptor, fromFile.offset, SEEK_SET);
			if(write(stringsFileDescriptor, "|_", 2)) {
				lseek(stringsFileDescriptor, 0, SEEK_END);
				if(write(stringsFileDescriptor, "|:|", 3)) {
					if(write(stringsFileDescriptor, productName, productSize)) {
						if(write(stringsFileDescriptor, "\n", 1)) {
							off_t str_end = lseek(stringsFileDescriptor, 0, SEEK_END) - str_start;

							lseek(artigosFileDescriptor, ((productID - 1) * sizeof(struct artigos)), SEEK_SET);
							fromFile.offset = str_end;
							if(write(artigosFileDescriptor, &fromFile, sizeof(struct artigos))) { /*do nothing, output to stderr later*/ }
						}
					}
				}
			}
		}
	}

	close(artigosFileDescriptor);
	close(stringsFileDescriptor);
}

void changePrice(int productID, int newPrice) {
	//  Open file "artigos"
	//  If the file doesn't exist, create it.
	int artigosFileDescriptor = open("artigos", O_RDWR | O_CREAT, S_IRWXO );

	off_t end = lseek(artigosFileDescriptor, 0, SEEK_END);
	off_t offset = lseek(artigosFileDescriptor, ((productID-1) * sizeof(struct artigos)), SEEK_SET);
	if(offset < end) {	// if( offset < end ) => artigo exists  
		Artigo fromfile;
		if(read(artigosFileDescriptor, &fromfile, sizeof(struct artigos))) {
			lseek(artigosFileDescriptor, (productID * sizeof(struct artigos)), SEEK_SET);
			Artigo tofile = newArtigo(fromfile.offset, newPrice);
			if(write(artigosFileDescriptor, &tofile, sizeof(struct artigos))) { /*do nothing, output to stderr later*/ }
		}
	}

	close(artigosFileDescriptor);
}

/*
	off_t offsetsize = sizeof(struct artigos);
	off_t size = lseek(artigosFileDescriptor, 0, SEEK_END) - lseek(artigosFileDescriptor, 0, SEEK_SET);
	size = size / offsetsize;

	dynamic array with size positions,
	sort articles by position,
	remap the offset of each article by lseek(artigosFileDescriptor, position * offsetsize, SEEK_SET);
*/
/*
	https://regexr.com/4ckp7
	time grep -oP '(\|:\|).+[\W\S]' strings >> tmp; rm strings; mv tmp strings;
*/
/*
	Compacting be like:
	grep -oP '(\|:\|).+[\W\S]' strings >> tmp; rm strings; mv tmp strings;
*/

int remapArtigos(int artigosFileDescriptor, int stringsFileDescriptor) {
	stringsFileDescriptor = compactStrings(stringsFileDescriptor);
	return 1;
}

int compactStrings() {
	// close before compacting
	pid_t child;
	
	if((child = fork()) == -1) {
		perror("Error forking child");
		return EXIT_FAILURE;
	} else if(child == 0){
		//child dups stdout to tmp
		char *argv[] = {"grep", "-oP", "(\\|:\\|).+[\\W\\S]", "strings", NULL};
		int tmp_fd = open("tmpfileforstrings", O_RDWR | O_CREAT | O_EXCL, S_IRWXO );

		if(tmp_fd == -1) { //error, couldn't crçeate file
			// remove it in case it already exists
		} else {
			dup2(tmp_fd, STDOUT_FILENO); // open the stdout to the file descriptor
			
			if(execvp("grep", argv) < 0) // execvp -> grep -oP '(\|:\|).+[\W\S]' strings
				perror("err, execvp grep");
			else { // grep executed without errors
				//maybe use unlink/link later?
				char* arg_rm[] = {"rm", "strings", NULL}; 
				char* arg_mv[] = {"mv", "tmpfileforstrings", "strings", NULL};

				if(unlink("strings")) // execvp -> rm strings
					perror("err, unlink()");
				if(link("tmpfileforstrings", "strings")) // execvp -> mv fileforstrings strings
					perror("err, link()");
			}
			close(tmp_fd);
			_exit(EXIT_SUCCESS);
		}
	} else { // parent
		int status = 0;
		waitpid(child, &status, 0);
		
		if(status) perror("err, child");
	}
	return 1;
}

//
Artigo newArtigo(off_t off, double price) {
	return (Artigo) { .offset = off, .price = price };
}

//
void insertVendas(char* productName, int productsize, double price) {
	//  Open files "artigos" and "strings"
	//  If the files don't exist, create them.
	int artigosFileDescriptor = open("artigos", O_RDWR | O_CREAT, S_IRWXO );
	int stringsFileDescriptor = open("strings", O_RDWR | O_CREAT, S_IRWXO );

	off_t str_start = lseek(stringsFileDescriptor, 0, SEEK_END);
	lseek(artigosFileDescriptor, 0, SEEK_END);

	if(write(stringsFileDescriptor, "|:|", 3)) {
		if(write(stringsFileDescriptor, productName, productsize)) {
			if(write(stringsFileDescriptor, "\n", 1)) { // Write worked
				Artigo tofile = newArtigo(str_start, price);
				if(write(artigosFileDescriptor, &tofile, sizeof(struct artigos))) { /*do nothing*/ }
			}
		}
	}

	close(artigosFileDescriptor);
	close(stringsFileDescriptor);
}

#ifndef ARTIGO_H
#define ARTIGO_H
#include <sys/types.h>

typedef struct artigos {
	off_t offset;	// offset of the string in the file
	double price;	// price of the article
} Artigo;

#endif
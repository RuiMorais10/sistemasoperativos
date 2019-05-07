// No servidor de vendas, para evitar o acesso constante ao ficheiro ARTIGOS, e tendo em conta que vários
// artigos populares serão continuamente requisitados, mantenha em memória a informação de preços que
// foi lida deste ficheiro, tendo cuidado com a sua invalidação por uma alteração de preços. Ou seja, quando
// são efectuadas alterações a preços de artigos, tal deve comunicado ao servidor de vendas, para este poder
// usar os preços actualizados.
#include <stdint.h>

//Número de elementos a guardar em cache
#define CACHESIZE 128

// Talvez uma hashtable? 
// Fazer isto apenas após resto do programa
// Ideia: https://stackoverflow.com/questions/4327115/embedded-c-how-to-create-a-cache-for-expensive-external-reads 
struct CacheEntry {
    int value;
    int address;
};

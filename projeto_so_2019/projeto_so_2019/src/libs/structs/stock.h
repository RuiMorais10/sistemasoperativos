#ifndef STOCK_H
#define STOCK_H

typedef struct stocks {
    //off_t offset;
    long id;
    long stock;
    double price;
} Stock;

#endif
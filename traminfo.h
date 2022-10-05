#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
struct Tram{
    char    *tram_id;
    char    *location;
    int     passenger_count;
    struct  Tram* next;
};


struct Tram * createTram(char *id, char *loc, int count);
void insert(struct Tram **root, char *id, char * loc, int count, bool islocation);
void display(struct Tram  **root); 

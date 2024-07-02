#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define CAPACITY 10
#define BUFFER 1024

typedef struct Record {
    int id; 
    char* field1; 
    int field2; 
    double field3; 
} Record; 

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo); 
Record *read_records(FILE *filename, unsigned long *num_records); 
void free_records(Record *records, unsigned long num_records); 
int int_cmp(const void *first, const void *second); 
int double_cmp(const void *first, const void *second); 
int string_cmp(const void *first, const void *second); 
void sorting_master(void *base, size_t nitems, size_t size, size_t algo, int (*compar)(const void*, const void*)); 
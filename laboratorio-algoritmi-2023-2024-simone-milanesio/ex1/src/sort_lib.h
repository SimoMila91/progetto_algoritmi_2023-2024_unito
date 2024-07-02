#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void merge_sort(void *base, size_t nitems, size_t size, int (*compare)(const void*, const void*)); 
void merge(void *base, size_t left, size_t right, size_t size, int (*compare)(const void*, const void*)); 
void quick_sort_recursive(void *base, size_t low, size_t high, size_t size, int (*compare)(const void*, const void*)); 
void quick_sort(void *base, size_t nitems, size_t size, int (*compare)(const void*, const void*)); 
size_t partition(void *base, size_t low, size_t high, size_t size, int (*compare)(const void*, const void*)); 
void swap(void *a, void *b, size_t size); 

/**
 * @brief: Il 3 way Quicksort i tempi si riducono a circa [ 28 secondi ] per ordinare l'intero dataset di [ 20.000.000 di record ]. 
 *         Dividendo le partizioni in elementi minori, uguali e maggiori gestisce meglio la profondità della ricorsione,
 *         in particolare quando (come nel caso del nostro dataset) vi sono molti record che si ripetono. 
 */
void quick_sort_recursive_3way(void *base, int low, int high, size_t size, int (*compare)(const void*, const void*));
void partition_3way(void *base, int low, int high, int *lt, int *gt, size_t size, int (*compare)(const void*, const void*));
#include "sort_lib.h"

void merge_sort(void *base, size_t nitems, size_t size, int (*compare)(const void*, const void*)) {
    if (nitems > 1) {
        size_t mid = nitems / 2; 
        merge_sort(base, mid, size, compare); 
        merge_sort((char *)base + mid * size, nitems - mid, size, compare); 
        merge(base, mid, nitems - mid, size, compare); 
    }

}

void merge(void *base, size_t left_size, size_t right_size, size_t size, int (*compare)(const void*, const void*)) {
    size_t total_size = left_size + right_size; 
    void *temp = malloc(total_size * size); 
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n"); 
        exit(EXIT_FAILURE); 
    }

    size_t i = 0, j = 0, k = 0; 

    char *left = (char *)base; 
    char *right = (char *)base + left_size * size; 

    while (i < left_size && j < right_size) {
        if (compare(left + i * size, right + j * size) <= 0) {
            memcpy(temp + k * size, left + i * size, size); 
            i++; 
        } else {
            memcpy(temp + k * size, right + j * size, size); 
            j++; 
        }
        k++; 
    }

    while (i < left_size) {
        memcpy(temp + k * size, left + i * size, size); 
        i++; 
        k++; 
    }

    while (j < right_size) {
        memcpy(temp + k * size, right + j * size, size); 
        j++; 
        k++; 
    }

    /* now we can copy temp on base and free temp */
    
    memcpy(base, temp, total_size * size); 
    free(temp); 

}

void swap(void *a, void *b, size_t size) {
    char *temp = malloc(size); 
    if (temp == NULL) {
        fprintf(stderr, "Malloc error in swap\n"); 
        exit(EXIT_FAILURE); 
    }
   
    memcpy(temp, a, size); 
    memcpy(a, b, size);  
    memcpy(b, temp, size); 
    free(temp); 
}


size_t partition(void *base, size_t low, size_t high, size_t size, int (*compare)(const void*, const void*)) {
    
    char *base_char = (char *)base;
    void *pivot = base_char + (high - 1) * size;
    size_t i = low - 1;  

    for (size_t j = low; j < high; j++) {
        if (compare(base_char + j * size, pivot) < 0) {
            i++;
            swap(base_char + i * size, base_char + j * size, size); 
        }
    }

    swap(base_char + (i+1)* size, base_char + (high-1) * size, size); 

    return i + 1; 
}

void quick_sort_recursive(void *base, size_t low, size_t high, size_t size, int (*compare)(const void*, const void*)) {
    
    if (low < high) {

        int pivot = partition(base, low, high, size, compare); 
      
        if (pivot > 0) quick_sort_recursive(base, low, pivot, size, compare); 

        quick_sort_recursive(base, pivot + 1, high, size, compare); 
    }
}



/**
 * @brief l'idea era quella di evitare lo stack overflow dovuto all'eccessiva profondità della ricorsione
 * @attention con l'implementazione del quicksort iterativo ha impiegato 1400 secondi circa per ordinare 10.000.000 di record. FALLITO
 * 
 *

size_t random_partition(void *base, size_t low, size_t high, size_t size, int (*compare)(const void*, const void*)) {
    size_t random_pivot_index = low + rand() % (high - low);
    char *base_char = (char *)base;
    swap(base_char + random_pivot_index * size, base_char + (high - 1) * size, size);
    return partition(base, low, high, size, compare);
}

void quick_sort_iterative(void *base, size_t nitems, size_t size, int (*compare)(const void*, const void*)) {
    if (nitems < 2) return;

    char *base_char = (char *)base;
    size_t *stack = malloc(nitems * sizeof(size_t));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    size_t top = 0;
    stack[top++] = 0;
    stack[top++] = nitems;

    while (top > 0) {
        size_t high = stack[--top];
        size_t low = stack[--top];

        if (high - low < 2) continue;

        size_t pivot = random_partition(base_char, low, high, size, compare);

        if (pivot > low) {
            stack[top++] = low;
            stack[top++] = pivot;
        }
        if (pivot + 1 < high) {
            stack[top++] = pivot + 1;
            stack[top++] = high;
        }
    }

    free(stack);
}

*/


void partition_3way(void *base, int low, int high, int *lt, int *gt, size_t size, int (*compare)(const void*, const void*)) {

   char *btmp = (char *)base;
    char *pivot = btmp + high * size;
    *lt = low;
    *gt = high;
    int i = low;

    while (i <= *gt) {
        int cmp = compare(btmp + i * size, pivot);
        if (cmp < 0) {
            swap(btmp + i * size, btmp + (*lt) * size, size);
            (*lt)++;
            i++;
        } else if (cmp > 0) {
            swap(btmp + i * size, btmp + (*gt) * size, size);
            (*gt)--;
        } else {
            i++;
        }
    }
}

void quick_sort_recursive_3way(void *base, int low, int high, size_t size, int (*compare)(const void*, const void*)) {
    if (low >= high) return;

    int lt, gt;
    partition_3way(base, low, high, &lt, &gt, size, compare);

    quick_sort_recursive_3way(base, low, lt - 1, size, compare);
    quick_sort_recursive_3way(base, gt + 1, high, size, compare);
}



void quick_sort(void *base, size_t nitems, size_t size, int (*compare)(const void*, const void*)) {
    
    //quick_sort_recursive(base, 0, nitems, size, compare);
    
    //srand((unsigned int)time(NULL)); // Inizializzazione del generatore di numeri casuali
    //quick_sort_iterative(base, nitems, size, compare);

    if (nitems > 1) {
        quick_sort_recursive_3way(base, 0, nitems-1, size, compare);
    }
    
}







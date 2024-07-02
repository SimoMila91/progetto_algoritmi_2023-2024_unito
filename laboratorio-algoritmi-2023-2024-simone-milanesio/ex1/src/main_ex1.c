#include "main_ex1.h"
#include "sort_lib.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Missing parameters\n"); 
        exit(EXIT_FAILURE); 
    }

    const char *file_name = argv[1]; 
    const char *output_file = argv[2]; 
    size_t field = (size_t)atoi(argv[3]);
    size_t algo = (size_t)atoi(argv[4]); 
    
    if (algo > 2 || algo < 1) {
        fprintf(stderr, "The last parameter should be 1 (quicksort) or 2 (merge sort). Try again\n"); 
        exit(EXIT_FAILURE); 
    }

    if (field < 1 || field > 3) {
        fprintf(stderr, "Field parameter doesn't exists. Should be 1 (string), 2 (int) or 3 (floating). Try again\n"); 
        exit(EXIT_FAILURE); 
    }

    FILE *infile = fopen(file_name, "r"); 
    if (!infile) {
        fprintf(stderr, "Error try to open infile\n"); 
        exit(EXIT_FAILURE); 
    } 

    FILE *outfile = fopen(output_file, "w"); 
    if (!outfile) {
        fprintf(stderr, "Error try to open outfile\n"); 
        exit(EXIT_FAILURE); 
    }

    sort_records(infile, outfile, field, algo);
}

void sorting_master(void *base, size_t nitems, size_t size, size_t algo, int (*compar)(const void*, const void*)) {
    
    clock_t begin = clock();
    if (algo == 1) quick_sort(base, nitems, size, compar); 
    else if (algo == 2) merge_sort(base, nitems, size, compar); 
    clock_t end = clock(); 

    double total_time = (double)(end - begin) / CLOCKS_PER_SEC; 
    
    char string[10]; 

    if (algo == 1) strcpy(string, "quickSort"); 
    else strcpy(string, "mergeSort");   
    
    printf("Total time of %s with %ld record: %f\n", string, nitems, total_time); 
}


void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo) {
    unsigned long num_records = CAPACITY;
    Record *records = read_records(infile, &num_records);

    if (num_records == 0) {
        fprintf(stderr, "No records found\n");
        exit(EXIT_FAILURE);
    }

    fclose(infile);

    switch(field) {
        case 1:
            sorting_master(records, num_records, sizeof(Record), algo, string_cmp);
            break;
        case 2:
            sorting_master(records, num_records, sizeof(Record), algo, int_cmp);
            break;
        case 3:
            sorting_master(records, num_records, sizeof(Record), algo, double_cmp);
            break;
        default:
            fprintf(stderr, "Inserted field doesn't exist. Please choose between 1 to 3 and try again.\n");
            fclose(outfile);
            free_records(records, num_records);
            exit(EXIT_FAILURE);
    }

    for (unsigned long i = 0; i < num_records; i++) {
        fprintf(outfile, "%d, %s, %d, %f\n", records[i].id, records[i].field1, records[i].field2, records[i].field3);
    }

    fclose(outfile);
    free_records(records, num_records);
}


void free_records(Record *records, unsigned long num_records) {
    
    unsigned long i;  

    for (i = 0; i < num_records; i++) {
        free(records[i].field1); 
        records[i].field1 = NULL; 
    }

    free(records); 
}


int int_cmp(const void *first, const void *second) {
    
    Record *one = (Record*)first; 
    Record *two = (Record*)second; 

    return one->field2 - two->field2; 
}


int string_cmp(const void *first, const void *second) {
    
    Record *one = (Record*)first; 
    Record *two = (Record*)second;

    return strcmp(one->field1, two->field1);
}


int double_cmp(const void *first, const void *second) {
    
    Record *one = (Record*)first;  
    Record *two = (Record*)second;
    
    if (fabs(one->field3 - two->field3) <  1e-10) {
        return 0; 
    } else if (one->field3 < two->field3) {
        return -1; 
    } else return 1; 
}

Record *read_records(FILE *file, unsigned long *num_records) {
    char length[BUFFER];
    unsigned long capacity = *num_records;
    unsigned long i = 0;
    Record *records = malloc(capacity * sizeof(Record));

    if (records == NULL) {
        fprintf(stderr, "Error in malloc - line 113 - main\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(length, BUFFER, file) != NULL) {
        if (i == capacity) {
            capacity *= 2;
            records = realloc(records, capacity * sizeof(Record));
            if (records == NULL) {
                fprintf(stderr, "Error realloc in read_records\n");
                exit(EXIT_FAILURE);
            }
        }

        char *line = strdup(length);
        if (line == NULL) {
            fprintf(stderr, "Error strdup in read_records\n");
            exit(EXIT_FAILURE);
        }

        char *id = strtok(line, ",");
        char *field1 = strtok(NULL, ",");
        char *field2 = strtok(NULL, ",");
        char *field3 = strtok(NULL, ",");

        if (!id || !field1 || !field2 || !field3) {
            fprintf(stderr, "Error parsing fields in line %ld.\n", i + 1);
            free(line);
            exit(EXIT_FAILURE);
        }

        records[i].id = atoi(id);
        records[i].field1 = strdup(field1);
        if (records[i].field1 == NULL) {
            fprintf(stderr, "Error strdup field1\n");
            free(line);
            exit(EXIT_FAILURE);
        }
        records[i].field2 = atoi(field2);
        records[i].field3 = atof(field3);

        free(line);
        i++;
    }

    *num_records = i;
    records = realloc(records, i * sizeof(Record));
    if (records == NULL) {
        fprintf(stderr, "Error last realloc read_records\n");
        exit(EXIT_FAILURE);
    }

    return records;
}

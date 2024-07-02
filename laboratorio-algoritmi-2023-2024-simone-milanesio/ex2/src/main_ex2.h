#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

void find_min_words(char *dictionary[], int dic_len, FILE *txt);  
void print_output(char *words[], int min_distances[], const char *w);
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int edit_distance(const char *s1, const char *s2);
int edit_distance_dyn(const char *s1, const char *s2); 
int min(int dno_op, int dcanc, int dins); 
int edit_distance_dyn_memo(const char *s1, const char *s2, int len1, int len2, int **memo);
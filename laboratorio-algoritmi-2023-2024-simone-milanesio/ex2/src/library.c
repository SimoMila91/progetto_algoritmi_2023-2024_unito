#include "library.h"
 

int min(int dno_op, int dcanc, int dins) {
     
    int min = dno_op; 
    if (dcanc < min) min = dcanc; 
    if (dins < min) min = dins; 
    return min; 
}

int edit_distance(const char *s1, const char *s2) {

    if (strlen(s1) == 0) return strlen(s2); 
    if (strlen(s2) == 0) return strlen(s1); 

    int dno_op = __INT_MAX__; 
    if (*s1 == *s2) {
        dno_op = edit_distance(s1 + 1, s2 + 1);
    } 

    int dcanc = 1  + edit_distance(s1, s2 + 1); 
    int dins = 1  + edit_distance(s1 + 1, s2);

    return min(dno_op, dcanc, dins); 

}

int edit_distance_dyn(const char *s1, const char *s2) {

    int len1 = strlen(s1); 
    int len2 = strlen(s2); 

    int **memo = (int **)malloc((len1 + 1) * sizeof(int *)); 
    if (memo == NULL) return -1; 

    for (int i = 0; i <= len1; i++) {
        memo[i] = (int *)malloc((len2 +  1) * sizeof(int)); 
        if (memo[i] == NULL) return -1; 
        for (int j = 0; j <= len2; j++) {
            memo[i][j] = -1; 
        }
    }

    int res = edit_distance_dyn_memo(s1, s2, len1, len2, memo); 

    for (int i = 0; i <= len1; i++) {
        free(memo[i]); 
    }

    free(memo); 

    return res; 
}

int edit_distance_dyn_memo(const char *s1, const char *s2, int len1, int len2, int **memo) {

    if (memo[len1][len2] != -1) return memo[len1][len2]; 

    if (len1 == 0) return len2; 
    if (len2 == 0) return len1; 

    int dno_op;  
    if (*s1 == *s2) {
        dno_op = edit_distance_dyn_memo(s1 + 1, s2 + 1, len1 - 1, len2 -1, memo); 
    } else dno_op = __INT_MAX__;

    int dcanc = 1 + edit_distance_dyn_memo(s1, s2 + 1, len1, len2 - 1, memo); 
    int dins = 1 + edit_distance_dyn_memo(s1 + 1, s2, len1 - 1, len2, memo);

    memo[len1][len2] = min(dno_op, dcanc, dins); 

    return min(dno_op, dcanc, dins); 
}
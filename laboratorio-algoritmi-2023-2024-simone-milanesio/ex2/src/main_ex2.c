/**
 * @file main_ex2.c
 * @author Simone Milanesio 
 * @brief dyn_total_time = 31.538832 | edit_total_time = 104.322131
*/

#include "main_ex2.h"
#include "library.h"

#define WORDS_LEN 5
#define MAX_DIC_LEN 1000000
#define WORD_LEN 1000

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("One or more parameters are missing"); 
        exit(EXIT_FAILURE); 
    }

    const char *dic_file = argv[1]; 
    const char *txt_file = argv[2]; 

    FILE *dic = fopen(dic_file, "r"); 
    FILE *txt = fopen(txt_file, "r"); 

    if (dic == NULL ) {
        printf("Error opening one or more files, try again."); 
        exit(EXIT_FAILURE); 
    }

    char *dictionary[MAX_DIC_LEN];  
    char word[WORD_LEN];
    int dic_len = 0; 

    while (fgets(word, WORD_LEN, dic)!= NULL && dic_len < MAX_DIC_LEN) {
        int len = strlen(word); 
        if (len > 0 && word[len - 1] == '\n') {
            word[len -1] = '\0'; 
        }
        dictionary[dic_len] = strdup(word); 
        dic_len++; 
    }

    fclose(dic); 
    
    clock_t begin = clock(); 

    find_min_words(dictionary, dic_len, txt);

    clock_t end = clock();  

    fclose(txt); 

    double total_time = (double)(end - begin) / CLOCKS_PER_SEC; 
    printf("Total time: %f\n", total_time); 

    return 0;
}




void find_min_words(char *dictionary[], int dic_len, FILE *txt) {
    
    char w[WORD_LEN]; 
    
    while (fgets(w, WORD_LEN,txt) != NULL) {
 
        if (w[strlen(w) - 1] == '\n' ) {
            w[strlen(w) - 1] = '\0'; 
        }

        char *token = strtok(w, " "); 
        
        while (token != NULL) {
            token[0] = tolower(token[0]); 
            int len = strcspn(token, ",.?!:;");
            
            token[len] = '\0';  

            char *words[WORDS_LEN] = {NULL}; 
            int min_distances[WORDS_LEN] = {1000}; 
            

    
                for (int i = 0; i < dic_len; i++) {

                int distance = edit_distance_dyn(token, dictionary[i]);

                for (int k = 0; k < WORDS_LEN; k++) {
                    if (words[k] == NULL || distance < min_distances[k]) {

                        for (int j = WORDS_LEN-1; j > k; j--) {
                            min_distances[j] = min_distances[j - 1]; 
                            words[j] = words[j - 1]; 
                        }

                        words[k] = dictionary[i]; 
                        min_distances[k] = distance; 
                        break; 
                    }
                }
                
                /**
                 * @cond if the word exists => distance == 0 => break
                */

                //if (distance == 0) break; 
            }

            print_output(words, min_distances, token); 

            token = strtok(NULL, " "); 
        }
    }
    
}

void print_output(char *words[], int min_distances[], const char *w) {

    FILE *output; 

    int opened = access("./data/output.txt", F_OK);  

    if (opened == 0) {
        output = fopen("./data/output.txt", "a"); 
    } else {
        output = fopen("./data/output.txt", "w"); 
    }
    
    if (output == NULL) {
        printf("Error opening output file. Try again."); 
        exit(EXIT_FAILURE); 
    }

    if (opened == 0) {
        fprintf(output, "------------------------------------------------\n"); 
    }

    fprintf(output, "Word: %s\n", w); 

    for (int i = 0; i < WORDS_LEN; i++) {
        fprintf(output, "Suggestion: %s\t\t Min_distance: %d\n", words[i], min_distances[i]); 
        //if (min_distances[i] == 0) break; 
    }

    fclose(output); 
}
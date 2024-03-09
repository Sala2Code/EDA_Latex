#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/struct.h"
#include "../include/globalVar.h"
#include "../include/latex.h"

#include "../include/csv.h"


// Personal function to consider consecutive delimiters and set NULL for empty cases
char* xstrtok(char* line, const char* delims){
    static char *saveline = NULL;
    char *p;
    int n;

    if(line != NULL){
        saveline = line;
    }
    // see if we have reached the end of the line
    if(saveline == NULL || *saveline == '\0'){
        return NULL;
    }
    
    // return the number of characters that aren't delims
    n = strcspn(saveline, delims);
    p = saveline; // save start of this token 
    saveline += n; // bump past the delim

    if(*saveline != '\0'){ // trash the delim if necessary
        *saveline++ = '\0';
    }
    return p;
}


void read_csv(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("Error during the opening of the file. \n");
        exit(1);
    }


    char* line = (char*) malloc(MAX_SIZE_LINE * sizeof(char));
    char *token;
    fgets(line, MAX_SIZE_LINE, file); // read name of col
    // count the number of col
    token = strtok(line, sep);

    char* sep2 = (char*) malloc(3*sizeof(char*));
    sprintf(sep2, "%s\n", sep);

    while( token != NULL ) {
        n_col++;
        token = strtok(NULL, sep2);
    }
    free(sep2);

    if(NO_NAME){
        add_name_col(path); // generate name for each column : col-i
    }

    while(fgets(line, MAX_SIZE_LINE, file)){
        n_row++;
    }
    printf("Number of columns: %d\n", n_col);
    printf("Number of rows: %d\n", n_row);

    arr_NaN = (int*) calloc(n_col, sizeof(int));
    
    rewind(file);
    int i_col = 0;
    arr_isCat_col = (int*) malloc(n_col * sizeof(int));

    for(int i=0; i<n_col; i++) { // for each column
        char** arr_val_unique = (char**) malloc(n_row * sizeof(char*));
        int n_val_unique = 0;

        rewind(file);
        fgets(line, MAX_SIZE_LINE, file); // TODO : read name of col, set this as a parameter and create col_i if not present

        while (fgets(line, MAX_SIZE_LINE, file)) { // set sum_NaN and determine type of col
            i_col = 0;
            token = xstrtok(line, sep);

            while(token != NULL && i_col < n_col) {                
                if(i_col == i){
                    if(strtok(token, "\n") == NULL){ // Count NaN per column
                        arr_NaN[i]++;
                    }else{ // Count unique value{
                        int isUnique = 1;
                        for(int j=0; j<n_val_unique; j++){
                            if(strcmp(arr_val_unique[j], token) == 0){
                                isUnique = 0;
                                break;
                            }
                        }
                        if(isUnique){
                            arr_val_unique[n_val_unique] = strdup(token);
                            n_val_unique++;
                        }
                    }
                    break;
                }
                token = xstrtok(NULL, sep);
                i_col++;
            }
        } 
        arr_isCat_col[i] = (n_val_unique <= THRESHOLD_CAT) ? 1 : 0;

        n_cat_col += arr_isCat_col[i];
        n_cont_col += !arr_isCat_col[i];

        for(int j=0; j<n_val_unique; j++){
            free(arr_val_unique[j]);
        }
        free(arr_val_unique);
    }
    arr_cat_col = (cat_col*) malloc(n_cat_col * sizeof(cat_col));
    arr_cont_col = (cont_col*) malloc(n_cont_col * sizeof(cont_col));

    fclose(file);
    free(line);
}



const char* determine_type(char* token){
    if( atoi(token) != 0 || strcmp(token, "0") == 0){
        return "int"; 
    }
    if( atof(token) != 0 || strcmp(token, "0.0") == 0){
        return "float";
    }
    if(strcmp(token, "") == 0){
        return "NULL";
    }
    return "string";

}


void add_name_col(const char* path){
    FILE* file = fopen(path, "r");
    if (!file) {
        printf("Error during the opening of the file. \n");
        exit(1);
    }

    FILE* fpTemp = fopen("tempFile.csv", "w");
    if (fpTemp == NULL) {
        perror("Error opening temp file : operation needed to add column name");
        fclose(file);
        exit(1);
    }

    char line[MAX_SIZE_LINE] = "";
    for(int i=0; i<n_col; i++){
        char temp[MAX_SIZE_LINE];
        sprintf(temp, "col-%d%s", i, (i < n_col - 1) ? sep : "\n"); 
        if (strlen(line) + strlen(temp) < MAX_SIZE_LINE) {
            strcat(line, temp);
        } else {
            printf("Error: Exceeded maximum line size.\n");
            break; 
        }
    }

    fputs(line, fpTemp);
    char buffer[MAX_SIZE_LINE];
    while (fgets(buffer, MAX_SIZE_LINE, file) != NULL) {
        fputs(buffer, fpTemp);
    }

    fclose(file);
    fclose(fpTemp);

    char newPath[128];
        strncpy(newPath, path, strlen(path) - 4);
        newPath[strlen(path) - 4] = '\0';
        strcat(newPath, "_col_name.csv");
        rename("tempFile.csv", newPath);

    printf("Use the file %s to get EDA\n", newPath);
    exit(1);

}
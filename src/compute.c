#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/struct.h"
#include "../include/globalVar.h"
#include "../include/latex.h"
#include "../include/csv.h"

#include "../include/compute.h"


void compute_col(const char *path){
    FILE *file = fopen(path, "r"); // the file has already been opened
    char* line = (char*) malloc(MAX_SIZE_LINE * sizeof(char));
    char* token;

    char* sep2 = (char*) malloc(3*sizeof(char));
    sprintf(sep2, "%s\n", sep);

    fgets(line, MAX_SIZE_LINE, file);
    token = strtok(line, sep2); // in name of col, there is no NULL (so no need to use xstrtok)
    for(int i_col=0;i_col<n_col;i_col++){
        char* name = strdup(latexify(token));
        if(arr_isCat_col[i_col]){
            arr_cat_col[index_cat_cont(i_col)].i_col = i_col;
            arr_cat_col[index_cat_cont(i_col)].name = name;
            arr_cat_col[index_cat_cont(i_col)].n_NaN = arr_NaN[i_col];

            arr_cat_col[index_cat_cont(i_col)].arr_val = (char**) malloc(n_row * sizeof(char*));
            arr_cat_col[index_cat_cont(i_col)].arr_val_unique = (char**) malloc(THRESHOLD_CAT * sizeof(char*));
            arr_cat_col[index_cat_cont(i_col)].arr_n_unique = (int*) malloc(THRESHOLD_CAT * sizeof(int));
            arr_cat_col[index_cat_cont(i_col)].n_unique = 0;
        }else{
            arr_cont_col[index_cat_cont(i_col)].i_col = i_col;
            arr_cont_col[index_cat_cont(i_col)].name = name;
            arr_cont_col[index_cat_cont(i_col)].n_NaN = arr_NaN[i_col];
            arr_cont_col[index_cat_cont(i_col)].min = 0;
            arr_cont_col[index_cat_cont(i_col)].max = 0; 
            arr_cont_col[index_cat_cont(i_col)].mean = 0;
            arr_cont_col[index_cat_cont(i_col)].median = 0;
            arr_cont_col[index_cat_cont(i_col)].variance = 0;
            arr_cont_col[index_cat_cont(i_col)].std = 0;
            arr_cont_col[index_cat_cont(i_col)].n_outliers = 0;
            arr_cont_col[index_cat_cont(i_col)].arr_val = (double*) malloc(n_row * sizeof(double));
        }
        if(strcmp(name, name_target) == 0){
            col_target = i_col;
            printf("Target column found, %i\n", col_target);
        }
        token = strtok(NULL, sep2);
    }
    if(col_target == -1){
        printf("Target column not found\n");
        exit(1);
    }


    fgets(line, MAX_SIZE_LINE, file); // read the second line (first line with data)
    token = strtok(line, sep2); 
    for(int i_col=0;i_col<n_col;i_col++){
        if(arr_isCat_col[i_col]){
            arr_cat_col[index_cat_cont(i_col)].type = determine_type(token);
        }else{
            arr_cont_col[index_cat_cont(i_col)].type = determine_type(token);

        }
        token = strtok(NULL, sep2);
    }
    int i_col = 0;
    for(int i=0; i<n_col; i++) { // for each column
        rewind(file);
        fgets(line, MAX_SIZE_LINE, file);
        if(arr_isCat_col[i]){
            arr_cat_col[index_cat_cont(i)].arr_val = (char**) malloc(n_row * sizeof(char*)); // cat (all)
        }else{
            arr_cont_col[index_cat_cont(i)].arr_val = (double*) malloc(n_row * sizeof(double)); // cont (all)
        }
        char** arr_value = (char**) malloc( (n_row-arr_NaN[i]) * sizeof(char*)); // cont (non null)

        int e = 0;
        int e_all = 0;
        int f_all = 0;
        while (fgets(line, MAX_SIZE_LINE, file)) { // set sum_NaN and determine type of col
            i_col = 0;
            int a = 0;
            token = xstrtok(line, sep);
            while(token != NULL && i_col < n_col) {                
                if(i_col == i){
                    if(arr_isCat_col[i]){ // categorical
                        arr_cat_col[index_cat_cont(i)].arr_val[f_all] = strdup(token);
                        f_all++;
                    }else{ // continuous    
                        if(token != NULL && token[0] != '\0'){ 
                            
                            if(sep_d){
                                char* p = token;
                                for(; *p; p++){
                                    if (*p == ','){
                                        *p = '.';
                                    }
                                }
                            }

                            arr_cont_col[index_cat_cont(i)].arr_val[e_all] = atof(token);

                            arr_value[e] = strdup(token);
                            e++;
                        } else {
                            arr_cont_col[index_cat_cont(i)].arr_val[e_all] = NAN; 
                        }
                        e_all++;
                    }
                    break;
                }
                token = xstrtok(NULL, sep);
                i_col++;
            }
            a++;
        }
        if(arr_isCat_col[i]){
            compute_cat_col(index_cat_cont(i), arr_cat_col[index_cat_cont(i)].arr_val);
        }else{
            compute_cont_col(index_cat_cont(i), arr_value);
        }

        free(arr_value);
    }

    fclose(file);
    free(line);
    free(sep2);


}


void compute_cat_col(int i, char** arr){
    // count occurences for each unique value and store them in arr_val_unique
    arr_cat_col[i].arr_n_unique  = (int*) malloc(THRESHOLD_CAT * sizeof(int));
    arr_cat_col[i].arr_val_unique = (char**) malloc(THRESHOLD_CAT * sizeof(char*));

    // count occurence in arr and set in arr_n_unique and arr_val_unique
    int n_unique = 0;
    for(int j=0; j<n_row; j++){
        int k = 0;
        for(; k<n_unique; k++){
            if(strcmp(arr[j],arr_cat_col[i].arr_val_unique[k]) == 0){
                arr_cat_col[i].arr_n_unique[k]++;
                break;
            }
        }
        if(k == n_unique){
            arr_cat_col[i].arr_val_unique[n_unique] = arr[j];
            arr_cat_col[i].arr_n_unique[n_unique] = 1;
            n_unique++;
        }
    }
    arr_cat_col[i].n_unique = n_unique;
}

int compare(const void *a, const void *b) {
    // Convert void* pointers to double* and dereference them to get the double values
    double val_a = *(const double*)a;
    double val_b = *(const double*)b;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

void compute_cont_col(int i, char** arr){ 
    int len = n_row - arr_cont_col[i].n_NaN;

    double* dbl_arr = (double*) malloc(len * sizeof(double));
    
    // mean
    double sum = 0;
    for(int j=0; j<len; j++){
        dbl_arr[j] = atof(arr[j]);
        sum += dbl_arr[j];
    }
    arr_cont_col[i].mean = sum / len;

    // sort array
    qsort(dbl_arr, len, sizeof(char*), compare);

    // median
    arr_cont_col[i].median = len % 2 == 0 ? (dbl_arr[len/2 - 1] + dbl_arr[len/2]) / 2 : dbl_arr[len/2];


    // variance
    sum = 0;
    for(int j=0; j<len; j++){
        sum += pow((dbl_arr[j] - arr_cont_col[i].mean), 2);
    }
    arr_cont_col[i].variance = sum / len;

    //std
    arr_cont_col[i].std = sqrt(arr_cont_col[i].variance);

    //min & max (arr is sorted)
    arr_cont_col[i].min = dbl_arr[0];
    arr_cont_col[i].max = dbl_arr[len - 1];

    //n_outliers
    int mid = len / 2;
    double Q1 = len % 2 == 0 ? (dbl_arr[mid/2 - 1] + dbl_arr[mid/2]) / 2 : dbl_arr[mid/2];
    double Q3 = len % 2 == 0 ? (dbl_arr[mid + mid/2 - 1] + dbl_arr[mid + mid/2]) / 2 : dbl_arr[mid + mid/2];
    double IQR = Q3 - Q1;

    // Count outliers
    arr_cont_col[i].n_outliers = 0;
    for(int j=0; j<len; j++){
        if(dbl_arr[j] < Q1 - 1.5 * IQR || dbl_arr[j] > Q3 + 1.5 * IQR){
            arr_cont_col[i].n_outliers++;
        }
    }

    free(dbl_arr);
}
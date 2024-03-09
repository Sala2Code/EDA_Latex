#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/struct.h"

#include "../include/globalVar.h"

char* sep = strdup(";");
int sep_d = 0;
int NO_NAME = 0;


int col_target = -1;
char* name_target = strdup("target");

int n_col = 0;
int n_row = 0; // First line is the name of the columns, so it doesn't count

int n_cat_col = 0;
int n_cont_col = 0;

int* arr_NaN = NULL;
int* arr_isCat_col = NULL;


cont_col* arr_cont_col = NULL;
cat_col* arr_cat_col = NULL;



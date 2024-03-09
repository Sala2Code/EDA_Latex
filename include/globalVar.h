#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include "struct.h"

// threshold to unique value to be considered as a column categorical
#define MAX_SIZE_LINE 1024
#define THRESHOLD_CAT 10 // above of 12 different value, the column is considered as continuous

extern char* sep;
extern int sep_d;
extern int NO_NAME;


extern int col_target;
extern char* name_target;

extern int n_col;
extern int n_row;
extern int n_cat_col;
extern int n_cont_col;

extern int* arr_isCat_col;
extern int* arr_NaN;

extern cont_col* arr_cont_col;
extern cat_col* arr_cat_col;


#endif
#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>

struct cont_col{
    int i_col;
    char* name;
    const char* type;
    int n_NaN;

    double* arr_val;

    double min;
    double max;
    double mean;
    double median;
    double variance;
    double std;

    int n_outliers;

};

struct cat_col{
    int i_col;
    char* name;
    const char* type;
    int n_NaN;

    int n_unique;
    char** arr_val;
    char** arr_val_unique;
    int* arr_n_unique;
};

#endif
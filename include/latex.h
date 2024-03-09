#ifndef LATEX_H
#define LATEX_H

void write_latex();
void create_pdf();
void put_latex_content(FILE* file);

char* latexify(char* str);

int index_cat_cont(int i);
char* join_strings(char** arr_val_unique, int num);
char* replace_underscore(char* str);

#endif

#ifndef CSV_H
#define CSV_H


char* xstrtok(char* line, const char* delims);
void read_csv(const char *path);
const char* determine_type(char* token);
void add_name_col(const char* path);


#endif
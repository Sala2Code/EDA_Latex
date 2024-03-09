#include <stdio.h>
#include <stdlib.h>

#include "../include/struct.h"
#include "../include/globalVar.h"
#include "../include/csv.h"
#include "../include/command.h"
#include "../include/latex.h"
#include "../include/compute.h"


/*
Example of commands : 
main.exe tests/df_gpt.csv -d ","
main.exe tests/obesity.csv -s "," -t NObeysdad
main.exe tests/london.csv -c 1 ; main.exe tests/london_col_name.csv -t col-40

If you get : Unable to read an entire line---bufsize=200000. Please increase buf_size in texmf.cnf. 
Set in (generally) C:\texlive\2022\texmf.cnf, to the end : buf_size = 500000 (or greater if your data is bigger)
*/


int main( int argc, char *argv[]) {
    readCommand(argc, argv);

    const char *path = argv[1];
    // TODO : print message running
    read_csv(path);
    printf("Read csv is done\n");

    compute_col(path);
    printf("Compute columns is done\n");

    write_latex();
    create_pdf();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/globalVar.h"

#include "../include/command.h"

void readCommand(int argc, char *argv[]){
    if (argc == 1) {
        printf("Error: No file path provided.\n");
        help(argc, argv);
        exit(1);
    }
    // if (argc >2) {
    //     int level = atoi(argv[2]);
    //     if (level < 0 || level > 3) {
    //         printf("Error: Invalid level.\n");
    //         help(argc, argv);
    //         exit(1);
    //     }
    // }
    if (argc == 2 && (strcmp(argv[1], "-h") * strcmp(argv[1], "--help")) == 0 ) {
        help(argc, argv);
        exit(0);
    }

    if(argc > 2){
        for(int i=2; i<argc; i+=2){
            if(strcmp(argv[i], "-s") == 0){
                sep = strdup(argv[i+1]);
            }
            else if(strcmp(argv[i], "-t") == 0){
                name_target = strdup(argv[i+1]);
            }
            else if(strcmp(argv[i], "-d") == 0){
                sep_d = atoi(argv[i+1]);
            }
            else if(strcmp(argv[i], "-c") == 0){
                NO_NAME = atoi(argv[i+1]);
            }
            else{
                printf("Error: Invalid option.\n");
                help(argc, argv);
                exit(1);
            }
        }


    }
}


void help(int argc, char *argv[]){
    printf("Usage: <path/file.csv> [level]\n");
    printf("Options:\n");
    printf("  -h, --help\t Display this help message.\n");
    printf("  <path/file.csv>\tPath to the CSV file. \n");
    printf("  -s <separator> \tSeparator of the CSV file. Default \";\" \n");
    printf("  -t <target>\tName of the target column. Default \"target\"\n");
    printf("  -d <bool> \tSeparator of the decimal, 0 for \".\" and 1 for \",\". Default 0\n");
    printf("  -c <bool> \tIf the first line of the CSV file doensn't have column name. Default 0\n");

    // printf("  [level]\t(Facultative) Set a number to specify the size of the dataset (number of columns)\n");
    // printf("\t\t0: Small\n\t\t1: Normal\n\t\t2: Big\n\t\t3: Huge\n");
}

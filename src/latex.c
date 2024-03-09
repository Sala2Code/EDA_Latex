#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/struct.h"
#include "../include/globalVar.h"

#include "../include/latex.h"


void write_latex() {
    FILE *file = fopen("EDA.tex", "w");
    if (file != NULL) {
        put_latex_content(file);
        fclose(file);
    }else {
        printf("Failed to open file .tex\n");
        exit(1);
    }
}

void create_pdf() {
    int result = system("pdflatex EDA.tex");
    if (result == 0) {
        printf("PDF generated successfully.\n");
    }else {
        printf("Failed to generate PDF.\n");
    }
}

void put_latex_content(FILE* file){

    fprintf(file,
        "\\documentclass{article}\n"
        "\n"
        "\\usepackage{booktabs}\n"
        "\\usepackage{graphicx}\n"
        "\\usepackage{amsmath}\n"
        "\\usepackage{float}\n"
        "\n"
        "\\usepackage[table]{xcolor}\n"
        "\\usepackage{array}\n"
        "\\usepackage{booktabs}\n"
        "\\usepackage[utf8]{inputenc}\n"
        "\n"
        "\\usepackage[abspath]{currfile}"
        "\\usepackage{xstring}"
        "\\usepackage{pgf-pie}\n"
        "\\usepackage{pgfplots}\n"
        "\\pgfplotsset{compat=1.17}\n"
        "\n"
        "\\definecolor{contColor}{rgb}{0.67, 0.9, 0.93}\n"
        "\\definecolor{catColor}{rgb}{0.98, 0.68, 0.82}\n"
        "\n"
        "\\title{Exploratory Data Analysis Report}\n"
        "\\author{Sala2Code}\n"
        "\\date{\\today}\n"
        "\n"

        "\\newcommand{\\parsedata}[2]{\n"
        "    \\addplot+[hist={data=x}] table[row sep=\\\\,y index=0] {\n"
        "        #1 \\\\\n"
        "    };\n"
        "    \\addlegendentry{#2}\n"
        "}\n"
        "\\newcounter{index}\n"
        "\\newcommand{\\customhist}[5]{\n"
        "    \\begin{tikzpicture}\n"
        "    \\begin{axis}[\n"
        "        title={#5},\n"
        "        width=\\textwidth,\n"
        "        ybar interval,\n"
        "        xmin=#2,\n"
        "        xmax=#3,\n"
        "        ymin=0,\n"
        "        xlabel={Value},\n"
        "        ylabel={Frequency},\n"
        "        legend style={text width=6cm,align=center,at={(0.5,-0.20)},anchor=north,legend columns=1},\n"
        "    ]\n"
        "    \\setcounter{index}{0}\n"
        "    \\foreach \\data in {#1}{\n"
        "        \\stepcounter{index}\n"
        "        \\foreach \\name [count=\\xi] in {#4}{\n"
        "            \\ifnum\\xi=\\value{index}\n"
        "                \\edef\\temp{\\noexpand\\parsedata{\\data}{\\name}}\n"
        "                \\temp\n"
        "            \\fi\n"
        "        }\n"
        "    }\n"
        "    \\end{axis}\n"
        "    \\end{tikzpicture}\n"
        "}\n"
        "\\newcommand{\\makePieChart}[2]{\n"
        "\\begin{center}\n"
        "   \\begin{tikzpicture}\n"
        "   \\node[below=33mm ] {\\textbf{#2}};\n"
        "   \\pie[text=legend, rotate=90]{#1};\n"
        "   \\end{tikzpicture}\n"
        "\\end{center}\n"
        "}\n"

        "\\begin{document}\n"
        "\n"
        "\\maketitle\n"
        "\n"
        "\\section{Dataset Overview}\n"
        "\\subsection{General Information}"
    );

    fprintf(file,
        "\\begin{itemize}\n"
        "    \\item Size: \\textit{%d} rows / \\textit{%d} columns\n"
        "    \\item Target column: \\textit{%s}\n"
        "\\end{itemize}\n",
        n_row, n_col, name_target
    );



    fprintf(file,
        "\\begin{table}[!htb]\n"
        "    \\centering\n"
        "    \\caption{Dataset Columns Overview}\n"
        "    \\vspace{2mm}\n"
        "    \\begin{tabular}{llccc}\n"
        "        \\toprule\n"
        "        Column Name & Data Type \\footnotemark  & NULL \\\\\n"
        "        \\midrule\n"
    );

    for(int i = 0; i < n_col; i++){
        fprintf(file, 
            "\\cellcolor{%s} %s & %s & %d \\\\\n",
            (arr_isCat_col[i]) ? "catColor" : "contColor",
            (arr_isCat_col[i]) ? arr_cat_col[index_cat_cont(i)].name : arr_cont_col[index_cat_cont(i)].name,
            (arr_isCat_col[i]) ? arr_cat_col[index_cat_cont(i)].type : arr_cont_col[index_cat_cont(i)].type,
            arr_NaN[i]
        );
    }
    printf("Writting continuous columns...\n");

    fprintf(file,
        "        \\bottomrule\n"
        "    \\end{tabular}\n"
        "    \\vspace{2mm}\n"
        "    \\\\\n"
        "    \\textit{Note:} \\textcolor{contColor}{Blue} represents continuous variables, \\textcolor{catColor}{Red} represents categorical variables.\n"
        "\\end{table}\n"
        "\\footnotetext{Consider the first value in each column. Therefore, it is not precise.}\n"
        "\n"

    // * Continuous Columns

        "\\subsection{Continuous Columns}\n"
        "\\begin{table}[!htb]\n"
        "    \\centering\n"
        "    \\begin{tabular}{lccccccc}\n"
        "        \\toprule\n"
        "        Column Name & Mean & Median & Min & Max & Variance & Std & Outliers \\\\\n"
        "        \\midrule\n"
    );
    for(int i = 0; i <n_cont_col; i++){
        fprintf(file, 
            "%s & %.3g & %.3g & %.3g & %.3g & %.3g & %.3g & %i \\\\\n",
            arr_cont_col[i].name,
            arr_cont_col[i].mean,
            arr_cont_col[i].median,
            arr_cont_col[i].min,
            arr_cont_col[i].max,
            arr_cont_col[i].variance,
            arr_cont_col[i].std,
            arr_cont_col[i].n_outliers
        );
    }
    fprintf(file,
        "        \\addlinespace\n"
        "        \\bottomrule\n"
        "    \\end{tabular}\n"
        "    \\caption{Data types and null value counts for each column.}\n"
        "\\end{table}\n"
        );



    char* name_class = arr_isCat_col[col_target] ? join_strings(arr_cat_col[index_cat_cont(col_target)].arr_val_unique, arr_cat_col[index_cat_cont(col_target)].n_unique) : (char*)"";

    for(int i = 0; i < n_cont_col; i++) {
        fprintf(file, "\\customhist{\n");

        if(arr_isCat_col[col_target]){ // distribution according to target
        
            for(int j=0;j<arr_cat_col[index_cat_cont(col_target)].n_unique;j++){ // for each class
                for(int k = 0; k < n_row; k++) {
                    if(!isnan(arr_cont_col[i].arr_val[k]) && strcmp(arr_cat_col[index_cat_cont(col_target)].arr_val[k], arr_cat_col[index_cat_cont(col_target)].arr_val_unique[j]) == 0){
                        fprintf(file, "%.3g \\\\", arr_cont_col[i].arr_val[k]);
                    }
                }
                fprintf(file, ",");
            }
            fprintf(file,
                "}{%.3g}{%.3g}{%s}{%s}\\\\ \n",
                arr_cont_col[i].min,
                arr_cont_col[i].max,
                name_class,
                arr_cont_col[i].name
            );


        }else{ // regression, so distribution of data
        

            for(int j = 0; j < n_row; j++) {
                if(!isnan(arr_cont_col[i].arr_val[j])){
                    fprintf(file, "%.3g \\\\", arr_cont_col[i].arr_val[j]);
                }
            }

            fprintf(file, 
                "}{%.3g}{%.3g}{%s}{%s}\\\\ \n",
                arr_cont_col[i].min,
                arr_cont_col[i].max,
                ".",
                arr_cont_col[i].name
            );
        }
    }

    // * Categorical Columns
    printf("Writting categorical columns...\n");
    fprintf(file,"\\subsection{Categorical Columns}\n");
    for(int i=0; i<n_cat_col; i++){
        fprintf(file, "\\makePieChart{");
        for(int j=0; j<arr_cat_col[i].n_unique; j++){
            fprintf(file, "%.3g/%s,", (double)100*arr_cat_col[i].arr_n_unique[j]/n_row, replace_underscore(arr_cat_col[i].arr_val_unique[j]));
        }
        fprintf(file, "%.3g/NaN", (double)100*arr_cat_col[i].n_NaN/n_row);
        fprintf(file, "}{%s}\n", replace_underscore(arr_cat_col[i].name));
    }
    
    fprintf(file, "\\end{document}");

}

char* latexify(char* str) {
    int underscore_count = 0;
    for (char* p = str; *p; p++) {
        if (*p == '_') underscore_count++;
    }
    char* new_str = (char*)malloc(strlen(str) + underscore_count + 1);
    if (!new_str) {
        return NULL;
    }

    char* new_p = new_str;
    for (char* p = str; *p; p++) {
        if (*p == '_') {
            *new_p++ = '\\';
            *new_p = '_';
        } else {
            *new_p = *p;
        }
        new_p++; 
    }
    *new_p = '\0';

    for (char* p = new_str; *p; p++) {
        if (*p == '\n') *p = ' ';
    }

    return new_str;
}


int index_cat_cont(int i){
    int index = 0;
    for(int j=0;j<i;j++){
        if(arr_isCat_col[j]==arr_isCat_col[i]){
            index++;
        }
    }
    return index;
}

char* join_strings(char** arr_val_unique, int num) {
    if (num == 0) return NULL;
    
    int total_length = 0;
    for (int i = 0; i < num; ++i) {
        total_length += strlen(arr_val_unique[i]);
    }
    

    
    total_length += (num - 1);
    total_length += 1;

    char* result = (char*)malloc(total_length * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';
    int offset = 0;
    

    for (int i = 0; i < num; ++i) {
        int space_remaining = total_length - offset;
        if (i < num - 1) {
            offset += snprintf(result + offset, space_remaining, "%s,", arr_val_unique[i]);
        } else {
            snprintf(result + offset, space_remaining, "%s", arr_val_unique[i]);
        }
    }
    return replace_underscore(result);
}

// in latex, the class name should not contain underscore (either \_) (error : Missing number, treated as zero)
char* replace_underscore(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '_') {
            str[i] = '-';
        }
    }
    return str;
}

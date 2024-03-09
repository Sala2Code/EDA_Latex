# EDA_Latex

## Overview
EDA_Latex is designed to perform Exploratory Data Analysis (EDA) on datasets, extracting valuable insights and generating comprehensive PDF reports. These reports highlight key findings and visualizations, such as variable distributions. For datasets with a categorical target variable, additional analyses are provided to deepen the understanding of the data.

## Getting Started
### Installation
Ensure you are in the project's directory before proceeding with the following commands. LaTex should be installed.

### Usage
To learn about the available commands and their details, execute:
- `main.exe -h` or `main.exe --help`

To run the program, use the following syntax:
```plaintext
Usage: main.exe <path/to/your/file.csv> [options]
```
#### Options:
- `-h, --help`          Display the help message and exit.
- `<path/file.csv>`     Specify the path to the CSV file you wish to analyze.
- `-s <separator>`      Define the separator used in the CSV file. The default is `";"`.
- `-t <target>`         Specify the name of the target column. The default is `"target"`.
- `-d <bool>`           Set the decimal separator: `0` for `"."` and `1` for `","`. The default is `0`.
- `-c <bool>`           Indicate if the first line in the CSV does not contain column names. The default is `0`.

### Examples
Execute the program with specific datasets to generate PDF reports:
- For the GPT dataset: `main.exe tests/df_gpt.csv -d ","`
- For the Obesity dataset from Kaggle: `main.exe tests/obesity.csv -s "," -t NObeysdad`
  [Kaggle Playground Series S4E2](https://www.kaggle.com/competitions/playground-series-s4e2/data)
- For the London dataset from Kaggle, first run: `main.exe tests/london.csv -c 1` 
  Then, to analyze the dataset with column names added: `main.exe tests/london_col_name.csv -t col-40`
  [Kaggle Playground Series S4E3](https://www.kaggle.com/competitions/playground-series-s4e3/data)

## Troubleshooting
### Common Errors
- The target column must not contain NaN values.
- Ensure there are no NaN values in the first data row of the dataset.
- If encountering an error related to reading an entire line due to `bufsize` limitations, increase `buf_size` in `texmf.cnf`. This file is typically located at `C:\texlive\2022\texmf.cnf`. Append the following configuration: `buf_size = 500000`. Adjust the size accordingly if your dataset is larger.
- If you have more than 10 classes > globalVar.h increase the number of THRESHOLD_CAT
- 

## Gallery
Explore generated reports and visualizations in the gallery section to see examples of insights EDA_Latex can provide.

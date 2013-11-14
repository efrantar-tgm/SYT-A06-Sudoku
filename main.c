#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solve9x9.h"
#include "solvex.h"

#define DEBUG

#define READ_FILE                   0
#define MANUAL_INPUT                1

#define NUMBER_OF_SUDOKU_TYPES      2
#define SUDOKU_9X9                  0
#define SUDOKU_X                    1

const char* SUDOKU_TYPES[NUMBER_OF_SUDOKU_TYPES]={
  "Sudoku 9x9",
  "Sudoku X"
};

const char* PRETTY = "pretty";
const char* CSV = "csv";

sudoku* input();
void output(sudoku*, const char*, FILE*);

int main(int argc, char** argv){
  sudoku* s = input();
  output(s, PRETTY, stdout);
  if(s->type == SUDOKU_9X9)
    s = solve9x9(s);
  if(s->type == SUDOKU_X)
    s = solvex(s);
  if(s) 
    output(s, PRETTY, stdout);
  else
    printf("NO SUDOKU SOLUTION\n");
  return EXIT_SUCCESS;
}

/**
 * Read the sudoku by file or by stdin input.
 * \return the sudoku
 */
sudoku* input(){
  sudoku* s = malloc(sizeof(sudoku));
  int i, j, choice;
  FILE* in;
  char filename[256];

  for(i = 0; i < NUMBER_OF_SUDOKU_TYPES; i++)
    printf("%d: %s\n", i, SUDOKU_TYPES[i]);
  // read the type of sudoku
  while(scanf("%d", &(s->type)) != 1 || !(0 <= s->type && s->type < NUMBER_OF_SUDOKU_TYPES));

  // read the type of input
  printf("%d: input by file\n", READ_FILE);
  printf("%d: manual input\n", MANUAL_INPUT);

  while(scanf("%d", &choice) != 1 || !(choice == READ_FILE || choice == MANUAL_INPUT));
  
  in = stdin;

  if(choice == READ_FILE){
    printf("Enter filename: ");
    scanf("%s", filename);
    in = fopen(filename, "r");
    puts("");
    if(in == NULL){
      printf("No such file!");
      exit(1);
    }
  }
  
  for(i = 0; i < 9; i++)
    for(j = 0; j < 9; j++)
      fscanf(in, "%d%*c", &(s->grid[i][j]));
  return s;
}

/**
 * modified original from: https://github.com/AntonFagerberg/Sudoku-C/blob/master/sudoku.c
 * Prints a given sudoku.
 * \param s the sudoku to print
 */
void output(sudoku* s, const char* style, FILE* out) 
{
  int i, j;
  if(!strcmp(style, PRETTY)){
    for (i = 0; i < 81; i++) {
		  if ((i % 9) == 0 &&  i != 0) // end of line
        fprintf(out, "|\n");
      if ((i % 27) == 0) // end of 3 cell block
          fprintf(out, "+-------+-------+-------+\n");
      if ((i % 3) == 0) // end of cell
        fprintf(out, "| ");
      
      fprintf(out, "%d ", (*s).grid[i / 9][i % 9]);
    }
    fprintf(out, "|\n+-------+-------+-------+\n"); // final line
  }else if(!strcmp(style, CSV)){
    for(i = 0; i < 9; i++)
      for(j = 0; j < 9; j++)
        printf("%d%c", s->grid[i][j], ",\n"[j == 8]);
  }
}

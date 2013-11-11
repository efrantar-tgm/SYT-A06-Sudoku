#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

#define READ_FILE 0
#define MANUAL_INPUT 1

#define NUMBER_OF_SUDOKU_TYPES 2

const char* SUDOKU_TYPES[NUMBER_OF_SUDOKU_TYPES]={
  "Sudoku 9x9",
  "X-Sudoku"
};

typedef struct{
  int grid[9][9];
  int type;
} sudoku;

sudoku* input();
void output(sudoku*);

int main(int argc, char** argv){
  sudoku* s = input();
  output(s);

  return EXIT_SUCCESS;
}

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
 * Prints a given sudoku.
 * \param s the sudoku to print
 */
void output(sudoku* s) 
{
  int i, j;
  for(i = 0;i < 9;i++)
    for(j = 0;j < 9;j++)
      printf("%d%c", (*s).grid[i][j], ",\n"[j == 8]);
}

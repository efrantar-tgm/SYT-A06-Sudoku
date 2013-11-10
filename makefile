DEPS = sudoku.h
OBJ = sudoku_main.o sudokuSolvers.o

%.o : %.c $(DEPS)
	gcc -c -o $@ $< -I.

compile: $(OBJ)
	gcc -o sudoku $^ -I.

run:
	./sudoku

clean:
	rm *.o sudoku


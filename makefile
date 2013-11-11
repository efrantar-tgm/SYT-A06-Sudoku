DEPS = sudoku.h
OBJ = sudoku_main.o normal_sudoku_solver.o

%.o : %.c $(DEPS)
	gcc -c -o $@ $< -I.

compile: $(OBJ)
	gcc -o sudoku $^ -I.

run:
	./sudoku

clean:
	rm *.o sudoku


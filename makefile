DEPS = x.h
OBJ = y.o z.o

%.o : %.c $(DEPS)
	gcc -c -o $@ $< -I

compile: $(OBJ)
	gcc -o Sudoku $^ -I

run:
	./Sudoku

clean:
	rm *.o Sudoku


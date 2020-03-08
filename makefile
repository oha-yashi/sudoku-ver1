MAKE_O = gcc -c $<

solveSudoku: main.o setting.o calc.o menu.o
	gcc -lncurses -o $@ $^

main.o: main.c
	$(MAKE_O)

setting.o: setting.c setting.h
	$(MAKE_O)

calc.o: calc.c calc.h
	$(MAKE_O)

menu.o: menu.c menu.h calc.h setting.h
	$(MAKE_O)

clean: 
	rm *.o

do: 
	./solveSudoku
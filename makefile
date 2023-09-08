matcalc: mymat.o mainmat.o
	gcc -ansi -Wall -g mymat.o mainmat.o -o matcalc
mymat.o: mymat.c mymat.h
	gcc -c -ansi -Wall mymat.c -o mymat.o
mainmat.o: mainmat.c mymat.h
	gcc -c -ansi -Wall mainmat.c -o mainmat.o


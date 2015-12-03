# To run, enter
# make all

all: sleepingta

sleepingta: main.o student.o ta.o hangout.o help_student.o
	gcc -pthread -o sleepingta main.o student.o ta.o hangout.o help_student.o

main.o: main.c ta.h
	gcc -pthread -c main.c

student.o: student.c ta.h
	gcc -pthread -c student.c

ta.o: ta.c ta.h
	gcc -pthread -c ta.c

hangout.o: hangout.c
	gcc -c hangout.c

help_student.o: help_student.c
	gcc -c help_student.c

clean:
	rm -rf *.o sleepingta

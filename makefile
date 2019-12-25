all: sem.c writer.c
	gcc -o control sem.c
	gcc -o write writer.c

CFLAGS=-Wall  -std=c11 -pedantic -ggdb


build: main.c 
	gcc $(CFLAGS) -o target/output main.c chunk.c memory.c debug.c value.c vm.c
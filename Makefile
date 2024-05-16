build: 
	gcc chunk.c -Wall memory.c value.c vm.c debug.c compiler.c scanner.c main.c -o target/main 

run: 
	target/main

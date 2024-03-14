build: 
	gcc chunk.c -Wall memory.c value.c vm.c debug.c main.c -o target/main 

run: 
	target/main
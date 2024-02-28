build: 
	gcc chunk.c -Wall memory.c main.c -o target/main 

run: 
	target/main
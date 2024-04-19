compile:
	#@gcc -g -fsanitize=address -o build/target $(shell find . -type f -name "*.c")
	@gcc -g -o build/target $(shell find . -type f -name "*.c")

run:
	@./build/target

all: compile run

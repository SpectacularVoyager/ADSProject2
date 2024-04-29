compile:
	@gcc -g -o build/target $(shell find . -type f -name "*.c")

run:
	@rlwrap ./build/target

all: compile run

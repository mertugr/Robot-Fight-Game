all: compile run

compile:
	@g++ -std=c++11 main.cpp robot.cpp grid.cpp -o test

run:
	@./test


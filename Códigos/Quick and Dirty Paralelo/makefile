CPP    = -std=c++11
DEBUG  = $(CPP) -g
LFLAGS = -lm -O3

UTILIDADES 	= Utilidades.cpp Utilidades.hpp

SOLVER		= Solver.cpp Solver.hpp

all: compile compile_main run clean

all_saida: compile compile_main run_saida clean

all_paralelo: compile compile_main run_paralelo clean clean_paralelo

test: compile compile_test run clean

test_saida: compile compile_test run_saida clean

compile:
	g++ $(CPP) -c $(UTILIDADES)
	g++ $(CPP) -c $(SOLVER)

debug:
	g++ $(DEBUG) -c $(UTILIDADES)
	g++ $(DEBUG) -c $(SOLVER)

compile_main:
	g++ $(CPP) main.cpp *.o -o main $(LFLAGS)

debug_main:
	g++ $(DEBUG) main.cpp *.o -o main $(LFLAGS)

run:
	./main

run_saida:
	./main > saida

run_paralelo:
	python testManager.py

connect:
	ssh myuser@server

send:
	mkdir codigo
	mkdir ./codigo/results
	cp ./*.cpp ./codigo
	cp ./*.hpp ./codigo
	cp ./makefile ./codigo
	cp ./index.txt ./codigo
	scp -r ./codigo/ myuser@server:/diretorio/
	rm -rf codigo

valgrind: debug debug_main
	valgrind ./main > log.txt 2>&1

valgrind_screen: debug debug_main
	valgrind ./main

clean:
	rm *.o *.gch main

clean_paralelo:
	rm *.pyc

wipe:
	rm -rf results
	mkdir results
	mkdir results/instancias
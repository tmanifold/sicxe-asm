
# SIC/XE Assembler makefile

CXX = g++
STD = c++14
DEPS = instruction.o tokenizer.o hashmap.o optab.o assembler.o main.o

sic-asm : $(DEPS)
	$(CXX) -std=$(STD) $^ -o $@

instruction.o : instruction.cpp
	$(CXX) -std=$(STD) -c $^ -o $@

tokenizer.o : tokenizer.cpp
	$(CXX) -std=$(STD) -c $^ -o $@

hashmap.o : hashmap.cpp
	$(CXX) -std=$(STD) -c $^ -o $@

optab.o : optab.cpp
	$(CXX) -std=$(STD) -c $^ -o $@

assembler.o : assembler.cpp
	$(CXX) -std=$(STD) -c $^ -o $@

main.o : main.cpp
	$(CXX) -std=$(STD) -c $^ -o $@

tesla: instruction.cpp tokenizer.cpp hashmap.cpp optab.cpp assembler.cpp main.cpp
	$(CXX) -std=c++11 $^ -o sic-asm

test:
	./sic-asm test.sic

clean:
	rm sic-asm *.o

remake:
	make clean && make

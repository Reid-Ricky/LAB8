final: CheatersDriver.o HashTable.o
	g++ -o plagiarismCatcher CheatersDriver.o HashTable.o 
CheatersDriver.o: CheatersDriver.cpp HashTable.h
	g++ -c CheatersDriver.cpp
HashTable.o: HashTable.h
	g++ -c HashTable.cpp

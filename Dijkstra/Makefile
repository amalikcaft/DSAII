dijkstra.exe: main.o graph.o heap.o hash.o
	g++ -o dijkstra.exe main.o graph.o heap.o hash.o

main.o: main.cpp
	g++ -c main.cpp

graph.o: graph.cpp graph.h heap.h
	g++ -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o mainDebug.exe main.cpp graph.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups

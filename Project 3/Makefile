EXEC = dijkstra
CC = g++ -O4	# Notice -O4
CFLAGS = -c -Wall

$(EXEC) :main.o util.o heap.o graph.o
	$(CC) -o $(EXEC) main.o util.o heap.o graph.o

main.o	:main.cpp main.h util.h heap.h graph.h 
	$(CC) $(CFLAGS) main.cpp

graph.o	:graph.h graph.cpp
	$(CC) $(CFLAGS) graph.cpp

util.o	:util.h util.cpp
	$(CC) $(CFLAGS) util.cpp

heap.o	:heap.h heap.cpp
	$(CC) $(CFLAGS) heap.cpp

clean :
	rm *.o

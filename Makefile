CC = g++
CFLAGS = -g -fmax-errors=5 -std=c++11
LDFLAGS = -std=c++11
 
# SRC = $(wildcard *.cc)
MAIN = main.cpp
SRC = graph.cpp vertex.cpp view.cpp edge.cpp floydWarshall.cpp shortestPath.cpp
OBJS =  $(SRC:.cpp=.o) $(MAIN:.cc=.o)
HEADER = $(SRC:.cpp=.hpp)
AOUT = SkiResort
 
all : $(AOUT) 

$(AOUT) : $(OBJS) $(HEADER)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)
.cpp.o :
	$(CC) $(CFLAGS) -c $<
clean :
	@rm *.o
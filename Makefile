CXX=g++
CXXFLAGS=-Wall -Wextra -Werror

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

hello_world: hello_world.o
	$(CXX) $^ -o $@

.PHONY: run clean

run: hello_world
	./$<

clean:
	rm -f *.o *~ *.core 


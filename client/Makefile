client: main.o
	g++ -o $@ $^

main.o: main.cpp

%.o: %.cpp
	g++ -c $^

clean:
	rm -f *.o *.out client

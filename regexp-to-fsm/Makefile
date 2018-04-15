program: main.o statemachine.o node.o edge.o
	g++ -g main.o statemachine.o node.o edge.o -o program

statemachine.o: statemachine.cpp statemachine.h edge.h
	g++ -std=c++11 -Wall -Wdeprecated -pedantic -g -c statemachine.cpp -o statemachine.o

main.o: main.cpp statemachine.h
	g++ -std=c++11 -Wall -Wdeprecated -pedantic -g -c main.cpp -o main.o
	
edge.o: edge.cpp edge.h node.h
	g++ -std=c++11 -Wall -Wdeprecated -pedantic -g -c edge.cpp -o edge.o
	
node.o: node.cpp node.h
	g++ -std=c++11 -Wall -Wdeprecated -pedantic -g -c node.cpp -o node.o
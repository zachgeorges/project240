all: main static-analysis

main: main.o Ingredient.o Meat.o Sauce.o Soda.o Tacos.o Order.o GenericAPI.o 
	g++ -lpthread main.o Ingredient.o Meat.o Sauce.o Soda.o Tacos.o Order.o GenericAPI.o  -o main

main.o: main.cpp Ingredient.h Meat.h Sauce.h Soda.h Tacos.h Order.h GenericAPI.h LoadUpdate.h 
	g++ -Wall -c main.cpp 

Ingredient.o: Ingredient.cpp Ingredient.h
	g++ -Wall -c Ingredient.cpp

Meat.o: Meat.cpp Meat.h
	g++ -Wall -c Meat.cpp

Sauce.o: Sauce.cpp Sauce.h
	g++ -Wall -c Sauce.cpp

Soda.o: Soda.cpp Soda.h
	g++ -Wall -c Soda.cpp

Tacos.o: Tacos.cpp Tacos.h
	g++ -Wall -c Tacos.cpp

Order.o: Order.cpp Order.h
	g++ -Wall -c Order.cpp


static-analysis:
	cppcheck *.cpp

clean:
	rm -f *.o main
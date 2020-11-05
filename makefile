all: *.o
	g++ *.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
*.o: *.cpp
	g++ -c *.cpp

clean:
	rm *.o

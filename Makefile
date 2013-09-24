game:
	g++ -o warofthenets src/main.cpp src/engine/game.cpp src/engine/gametime.cpp -W -Wall -pedantic -lSDL2  -I./src/engine

dist-clean:
	rm warofthenets


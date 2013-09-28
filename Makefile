game:
	g++ -o warofthenets src/main.cpp src/engine/game.cpp src/engine/window.cpp src/engine/render.cpp src/engine/image.cpp -lSDL2  -I./src/engine

dist-clean:
	rm warofthenets


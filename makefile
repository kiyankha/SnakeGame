all:
	g++ -I src/include -I src/my_classes/  -L src/lib src/my_classes/*.cpp -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
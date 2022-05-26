all:
	g++ src/main.cpp -O3 -o main -I/usr/include/allegro5 -L/usr/lib -lallegro -lallegro_primitives -lallegro_ttf -lallegro_font

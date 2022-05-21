all:
	g++ main.cpp -o main -I/usr/include/allegro5 -L/usr/lib -lallegro -lallegro_primitives -lallegro_ttf -lallegro_font

#all:
#	mpiCC src/main.cpp -I/usr/include/allegro5 -L/usr/lib -lallegro -lallegro_primitives
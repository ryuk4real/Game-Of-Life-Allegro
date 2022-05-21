#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <random>
#include <time.h>
#include <string>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define COLS 100
#define ROWS 100
#define GENERATIONS 500000

#define MILLISECONDS_TO_WAIT_FOR_EACH_GENERATION 0

#define BLACK 	al_map_rgb(0,		  0,		0)
#define WHITE 	al_map_rgb(255,		255,	  255)
#define RED     al_map_rgb(255,       0,        0)

#define DISPLAY_HEIGHT 700
#define DISPLAY_WIDTH 700
#define SQUARE_HEIGHT DISPLAY_HEIGHT / COLS

#define GENERATION_COUNTER_FONT_SIZE 36
#define GENERATION_TEXT_COLOR RED




int *currentGeneration = new int[COLS * ROWS];
int *newGeneration = new int[COLS * ROWS];




void initializeFirstGenerationWithGlider();
void initializeRandomFirstGeneration();

void swapLastGeneration();
void generateNextGeneration();
void transictionCell(int i, int j);

int m(int i, int j);

void drawCell(int i, int j, ALLEGRO_COLOR cellColor);


int main(int args, char **argv)
{

    // ALLEGRO -------------------------------------------------------
    // Initialize allegro

    ALLEGRO_DISPLAY *display = nullptr;

	if (!al_init())
	{
		fprintf(stderr, "Failed to initialize allegro.\n");
		return 1;
	}

	// Create the display
	display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	if (!display)
	{
		fprintf(stderr, "Failed to create display.\n");
		return 1;
	}



    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_FONT *fontUbuntuB = al_load_font("fonts/Ubuntu-B.ttf", GENERATION_COUNTER_FONT_SIZE, 1);
    
	al_clear_to_color(WHITE);
	al_flip_display();

    // ---------------------------------------------------------------





    // GAME LOOP -----------------------------------------------------

    srand(time(nullptr));
    initializeRandomFirstGeneration();
    //initializeFirstGenerationWithGlider();

    for (int i = 0; i < GENERATIONS; ++i)
    {
        generateNextGeneration();
        swapLastGeneration();


        std::string generation = std::to_string(i);
        al_draw_text(fontUbuntuB, GENERATION_TEXT_COLOR, 10, 10, ALLEGRO_ALIGN_LEFT, generation.c_str());


        std::this_thread::sleep_for(std::chrono::milliseconds(MILLISECONDS_TO_WAIT_FOR_EACH_GENERATION));
        al_flip_display();
        al_clear_to_color(WHITE);
    }

    // ---------------------------------------------------------------








    // DESTROY -------------------------------------------------------
    al_destroy_display(display);

    delete [] currentGeneration;
    delete [] newGeneration;
    //----------------------------------------------------------------
}





void initializeFirstGenerationWithGlider()
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            currentGeneration[m(i,j)] = 0;
            newGeneration[m(i,j)] = 0;
        }
    }
    
    //inserisco un glider
    int i = ROWS / 2;
    int j = COLS / 2;

    currentGeneration[m(0,0)] = 1;

    currentGeneration[m(i, j - 1)] = 1;
    currentGeneration[m(i + 1, j)] = 1;
    currentGeneration[m(i, j + 1)] = 1;
    currentGeneration[m(i - 1, j + 1)] = 1;
    currentGeneration[m(i + 1, j + 1)] = 1;
}

void initializeRandomFirstGeneration()
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            currentGeneration[m(i,j)] = rand()%2;
            newGeneration[m(i,j)] = 0;
        }
    }
}

void swapLastGeneration()
{
    int *currentGenerationCopy = currentGeneration;
    currentGeneration = newGeneration;
    newGeneration = currentGenerationCopy;
}

void generateNextGeneration()
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {

            transictionCell(i,j);

        }
    }
}

void transictionCell(int i, int j)
{

    int neighbours = 0;

    for (int r = -1; r <= 1; ++r)
    {
        for (int c = -1; c <= 1; ++c)
        {

            if ((r != 0 || c != 0))
            {
                if (currentGeneration[m((i + r + ROWS) % ROWS, ((j + c + COLS) % COLS))] == 1)
                {
                    ++neighbours;
                }           
            }
        }
        
        if (currentGeneration[m(i,j)] == 1)
        {
            if (neighbours == 2 || neighbours == 3)
            {
                newGeneration[m(i,j)] = 1;
                drawCell(i,j, BLACK);
            }
            else newGeneration[m(i,j)] = 0;
        }
        else
        {
            if (neighbours == 3)
            {
                newGeneration[m(i,j)] = 1;
                drawCell(i,j, BLACK);
            }
            else newGeneration[m(i,j)] = 0;
        }
    }
}

int m(int i, int j)
{
    return ((i * COLS) + j);
}

void drawCell(int i, int j, ALLEGRO_COLOR cellColor)
{
   al_draw_filled_rectangle(i * SQUARE_HEIGHT,
                            j * SQUARE_HEIGHT,
                            i * SQUARE_HEIGHT + SQUARE_HEIGHT,
                            j * SQUARE_HEIGHT + SQUARE_HEIGHT,
                            cellColor);
}

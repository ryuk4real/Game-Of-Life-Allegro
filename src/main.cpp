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

#include "headers/Settings.hpp"

#define BLACK 	al_map_rgb(0,		  0,		0)
#define WHITE 	al_map_rgb(255,		255,	  255)
#define RED     al_map_rgb(255,       0,        0)

Settings settings;

const int columns = settings.getMatrixSize();
int rows = columns;

int squareHeight = settings.getDisplaySize() / columns;

int genetationTypefaceTextSize = settings.getGenerationTextTypefaceSize();
#define TEXT_COLOR settings.getGenerationTextColor()

int waitTime = settings.getMillisecodsToWaitForEachGeneration();

int *currentGeneration = new int[columns * rows];
int *newGeneration = new int[columns * rows];


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
	display = al_create_display(settings.getDisplaySize(), settings.getDisplaySize());
    
	if (!display)
	{
		fprintf(stderr, "Failed to create display.\n");
		return 1;
    }

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    
    ALLEGRO_FONT *fontUbuntuB = al_load_font("fonts/Ubuntu-B.ttf",
                                             36,
                                             1);
    
	al_clear_to_color(WHITE);
	al_flip_display();

    // ---------------------------------------------------------------



    // GAME LOOP -----------------------------------------------------

    srand(time(nullptr));
    initializeRandomFirstGeneration();
    //initializeFirstGenerationWithGlider();

    for (int i = 0; i < settings.getNumberOfGenerations(); ++i)
    {
        generateNextGeneration();
        swapLastGeneration();


        std::string generation = std::to_string(i);
        al_draw_text(fontUbuntuB, TEXT_COLOR, 10, 10, ALLEGRO_ALIGN_LEFT, generation.c_str());


        std::this_thread::sleep_for(std::chrono::milliseconds(settings.getMillisecodsToWaitForEachGeneration()));
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
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            currentGeneration[m(i,j)] = 0;
            newGeneration[m(i,j)] = 0;
        }
    }
    
    //inserisco un glider
    int i = rows / 2;
    int j = columns / 2;

    currentGeneration[m(0,0)] = 1;

    currentGeneration[m(i, j - 1)] = 1;
    currentGeneration[m(i + 1, j)] = 1;
    currentGeneration[m(i, j + 1)] = 1;
    currentGeneration[m(i - 1, j + 1)] = 1;
    currentGeneration[m(i + 1, j + 1)] = 1;
}

void initializeRandomFirstGeneration()
{
    for (int i = 0; i < rows
; ++i)
    {
        for (int j = 0; j < columns; ++j)
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
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
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
                if (currentGeneration[m((i + r + rows) % rows, ((j + c + columns) % columns))] == 1)
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
    return ((i * columns) + j);
}

void drawCell(int i, int j, ALLEGRO_COLOR cellColor)
{
   al_draw_filled_rectangle(i * squareHeight,
                            j * squareHeight,
                            i * squareHeight + squareHeight,
                            j * squareHeight + squareHeight,
                            cellColor);
}

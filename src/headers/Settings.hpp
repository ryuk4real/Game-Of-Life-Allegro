#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <allegro5/allegro5.h>
#include <fstream> //ifstream
#include <iostream> //cout
#include <assert.h>

#include "json.hpp"
using json = nlohmann::json;


using namespace std;

class Settings
{
    private:

        bool areSettingsDefault;

        int numberOfGenerations;
        ALLEGRO_COLOR generationTextColor;
        int generationTypefaceSize;

        int displaySize;
        int matrixSize;

        ALLEGRO_COLOR aliveCellColor;
        ALLEGRO_COLOR deadCellColor;

        int millisecondsToWaitForEachGeneration;
    


    public:



        Settings();




        // Setters --------------------------------------------------------------------------------------------------------
        void setAreSettingsDefault(bool _areSettingdsDEfault) {areSettingsDefault = areSettingsDefault;}

        void setNumberOfGenerations(int _numberOfGeneration) {numberOfGenerations = _numberOfGeneration;}
        void setGenerationTextColor(ALLEGRO_COLOR _generationTextColor) {generationTextColor = _generationTextColor;}
        void setGenerationTypeaceSize(int _typefaceSize) {generationTypefaceSize = _typefaceSize;}
        
        void setDisplaySize(int _displaySize) {displaySize = _displaySize;}
        void setMatrixSize(int _matrixSize) {matrixSize = _matrixSize;}

        void setAliveCellColor(ALLEGRO_COLOR _aliveCellColor) {aliveCellColor = _aliveCellColor;}
        void setDeadCellColor(ALLEGRO_COLOR _deadCellColor) {deadCellColor = _deadCellColor;}

        void setMillisecondsToWaitForEachGeneration(int _millisecondsToWaitForEachGeneration) {millisecondsToWaitForEachGeneration = _millisecondsToWaitForEachGeneration;}
        // -----------------------------------------------------------------------------------------------------------------




        // Getters -------------------------------------------------------------------------------------
        int getNumberOfGenerations() const {return numberOfGenerations;}
        ALLEGRO_COLOR getGenerationTextColor() const {return generationTextColor;}
        int getGenerationTextTypefaceSize() const {return generationTypefaceSize;}

        int getDisplaySize() const {return displaySize;}
        int getMatrixSize() const {return matrixSize;}

        ALLEGRO_COLOR getAliveCellColor() const {return aliveCellColor;}
        ALLEGRO_COLOR getDeadCellColor() const {return deadCellColor;}
        int getMillisecodsToWaitForEachGeneration() const {return millisecondsToWaitForEachGeneration;}
        // ----------------------------------------------------------------------------------------------

};

Settings::Settings()
{

    // Read json setings file ----------------------------------------------------------------------------
    ifstream settings("src/settings/settings.json");
    json jsonSettings;
    settings >> jsonSettings;
    //----------------------------------------------------------------------------------------------------


    numberOfGenerations = jsonSettings["Settings"]["numberOfGenerations"];

    //TODO: Generation text color

    generationTypefaceSize = jsonSettings["Settings"]["generationTypefaceSize"];

    displaySize = jsonSettings["Settings"]["displaySize"];

    matrixSize = jsonSettings["Settings"]["matrixSize"];

    //TODO: dead/alive cell color

    millisecondsToWaitForEachGeneration = jsonSettings["Settings"]["millisecondsToWaitForEachGeneration"];

}


#endif
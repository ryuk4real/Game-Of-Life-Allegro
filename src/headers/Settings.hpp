#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <allegro5/allegro5.h>
#include <fstream> //ifstream
#include <iostream> //cout
#include <assert.h>

#include "json.hpp"
using json = nlohmann::json;


using namespace std;

struct rgb{int r; int g; int b;};

class Settings
{

    private:

        bool areSettingsDefault;

        int numberOfGenerations;
        rgb generationTextColor;
        int generationTypefaceSize;

        int displaySize;
        int matrixSize;

        rgb aliveCellColor;
        rgb deadCellColor;

        int millisecondsToWaitForEachGeneration;
    


    public:



        Settings();




        // Setters --------------------------------------------------------------------------------------------------------
        void setAreSettingsDefault(bool &_areSettingdsDEfault) {areSettingsDefault = areSettingsDefault;}

        void setNumberOfGenerations(int &_numberOfGeneration) {numberOfGenerations = _numberOfGeneration;}
        void setGenerationTextColor(rgb &_generationTextColor) {generationTextColor = _generationTextColor;}
        void setGenerationTypeaceSize(int &_typefaceSize) {generationTypefaceSize = _typefaceSize;}
        
        void setDisplaySize(int &_displaySize) {displaySize = _displaySize;}
        void setMatrixSize(int &_matrixSize) {matrixSize = _matrixSize;}

        void setAliveCellColor(rgb &_aliveCellColor) {aliveCellColor = _aliveCellColor;}
        void setDeadCellColor(rgb &_deadCellColor) {deadCellColor = _deadCellColor;}

        void setMillisecondsToWaitForEachGeneration(int &_millisecondsToWaitForEachGeneration) {millisecondsToWaitForEachGeneration = _millisecondsToWaitForEachGeneration;}
        // -----------------------------------------------------------------------------------------------------------------




        // Getters -------------------------------------------------------------------------------------
        int getNumberOfGenerations() const {return numberOfGenerations;}
        rgb getGenerationTextColor() const {return generationTextColor;}
        int getGenerationTextTypefaceSize() const {return generationTypefaceSize;}

        int getDisplaySize() const {return displaySize;}
        int getMatrixSize() const {return matrixSize;}

        rgb getAliveCellColor() const {return aliveCellColor;}
        rgb getDeadCellColor() const {return deadCellColor;}
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

    generationTextColor.r = jsonSettings["Settings"]["generationTextColor"][0];
    generationTextColor.g = jsonSettings["Settings"]["generationTextColor"][1];
    generationTextColor.b = jsonSettings["Settings"]["generationTextColor"][2];

    generationTypefaceSize = jsonSettings["Settings"]["generationTypefaceSize"];

    displaySize = jsonSettings["Settings"]["displaySize"];

    matrixSize = jsonSettings["Settings"]["matrixSize"];

    aliveCellColor.r = jsonSettings["Settings"]["aliveCellColor"][0];
    aliveCellColor.g = jsonSettings["Settings"]["aliveCellColor"][1];
    aliveCellColor.b = jsonSettings["Settings"]["aliveCellColor"][2];

    deadCellColor.r = jsonSettings["Settings"]["deadCellColor"][0];
    deadCellColor.g = jsonSettings["Settings"]["deadCellColor"][1];
    deadCellColor.b = jsonSettings["Settings"]["deadCellColor"][2];

    generationTypefaceSize = jsonSettings["Settings"]["generationTypefaceSize"];

    millisecondsToWaitForEachGeneration = jsonSettings["Settings"]["millisecondsToWaitForEachGeneration"];

}


#endif
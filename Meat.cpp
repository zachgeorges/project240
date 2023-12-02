#include "Meat.h"

using namespace std;
using namespace crow;

Meat::Meat(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}


json::wvalue Meat::convertToJson() 
{
    json::wvalue writeJson = Ingredient::convertToJson();

    writeJson["meatType"] = meatType;
    writeJson["isPork"] = isPork;

    return writeJson;
}

// Update from JSON
void Meat::updateFromJson(json::rvalue readValueJson) 
{
    // Update the base Ingredient part
    Ingredient::updateFromJson(readValueJson); 

    // Update Meat-specific details
    meatType = readValueJson["meatType"].s();
    isPork = readValueJson["isPork"].b();
}
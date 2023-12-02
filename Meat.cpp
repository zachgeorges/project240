// Meat.cpp
#include "Meat.h"

using namespace std;
using namespace crow;

Meat::Meat(json::rvalue readValueJson) : Ingredient(readValueJson)  
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Meat::convertToJson() 
{
    json::wvalue writeJson = Ingredient::convertToJson();
    // Add Meat-specific properties
    // writeJson["type"] = meatType;
    writeJson["isPork"] = isPork;
    return writeJson;
}

// Update from JSON
void Meat::updateFromJson(json::rvalue readValueJson) 
{
    Ingredient::updateFromJson(readValueJson);
    // Update Meat-specific properties
    // meatType = readValueJson["type"].s();
    isPork = readValueJson["isPork"].b();
}
// Sauce.cpp
#include "Sauce.h"

using namespace std;
using namespace crow;

Sauce::Sauce(json::rvalue readValueJson) : Ingredient(readValueJson)  
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Sauce::convertToJson() 
{
    json::wvalue writeJson = Ingredient::convertToJson();
    // Add Sauce-specific properties
    // writeJson["type"] = sauceType;
    writeJson["isSpicy"] = isSpicy;
    return writeJson;
}

// Update from JSON
void Sauce::updateFromJson(json::rvalue readValueJson) 
{
    Ingredient::updateFromJson(readValueJson);
    // Update Sauce-specific properties
    // sauceType = readValueJson["type"].s();
    isSpicy = readValueJson["isSpicy"].b();
}
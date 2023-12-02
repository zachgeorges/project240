#include "Sauce.h"

using namespace std;
using namespace crow;

Sauce::Sauce(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Sauce::convertToJson() 
{
    // Convert the base Ingredient part
    json::wvalue writeJson = Ingredient::convertToJson();

    // Add Sauce-specific details
    writeJson["sauceType"] = sauceType;
    writeJson["isSpicy"] = isSpicy;

    return writeJson;
}

// Update from JSON
void Sauce::updateFromJson(json::rvalue readValueJson) 
{
    // Update the base Ingredient part
    Ingredient::updateFromJson(readValueJson); 

    // Update Sauce-specific details
    sauceType = readValueJson["sauceType"].s();
    isSpicy = readValueJson["isSpicy"].b();
}
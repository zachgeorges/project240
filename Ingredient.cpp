// Ingredient.cpp
#include "Ingredient.h"

using namespace crow;

Ingredient::Ingredient(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Ingredient::convertToJson() 
{
    json::wvalue writeJson;
    writeJson["id"] = id;
    writeJson["name"] = name;
    writeJson["calories"] = calories;
    writeJson["quantity"] = quantity;
    return writeJson;
}

// Update from JSON
void Ingredient::updateFromJson(json::rvalue readValueJson) 
{
    id = readValueJson["id"].s();
    name = readValueJson["name"].s();
    calories = readValueJson["calories"].i();
    quantity = readValueJson["quantity"].i();
}
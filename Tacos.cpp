#include "Tacos.h"

using namespace std;
using namespace crow;

extern map<std::string, Ingredient> ingredientsMap;
extern map<std::string, Meat> meatsMap;
extern map<std::string, Sauce> saucesMap;

Tacos::Tacos(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Tacos::convertToJson() 
{
    json::wvalue writeJson;
    writeJson["id"] = id;

    // Convert ingredients to JSON
    int index = 0;
    for (Ingredient ingredient : ingredients) 
    {
        writeJson["ingredients"][index] = ingredient.convertToJson();
        index++;
    }

    // Convert meats to JSON
    index = 0;
    for (Meat meat : meats) 
    {
        writeJson["meats"][index] = meat.convertToJson();
        index++;
    }

    // Convert sauces to JSON
    index = 0;
    for (Sauce sauce : sauces) 
    {
        writeJson["sauces"][index] = sauce.convertToJson();
        index++;
    }

    return writeJson;
}

// Update from JSON
void Tacos::updateFromJson(json::rvalue readValueJson) 
{
    id = readValueJson["id"].s();

    // Setting ingredients
    for (json::rvalue ingredientReadValueJson : readValueJson["ingredients"])
    {
        ingredients.push_back(ingredientsMap.at(ingredientReadValueJson["id"].s()));
    }

    // Setting meats
    for (json::rvalue meatReadValueJson : readValueJson["meats"])
    {
        meats.push_back(meatsMap.at(meatReadValueJson["id"].s()));
    }

    // Setting sauces
    for (json::rvalue sauceReadValueJson : readValueJson["sauces"])
    {
        sauces.push_back(saucesMap.at(sauceReadValueJson["id"].s()));
    }
}
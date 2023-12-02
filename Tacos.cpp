#include "Tacos.h"

using namespace std;
using namespace crow;

extern map<std::string, Ingredient> ingredientsMap;

Tacos::Tacos(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Tacos::convertToJson() 
{
    json::wvalue writeJson;
    writeJson["id"] = id;
    writeJson["cost"] = cost;

    // Convert ingredients to json (Save only the names)
    int index = 0;
    for (Ingredient ingredient : ingredients) 
    {
        writeJson["ingredients"][index]["name"] = ingredient.getName();
        // Add other ingredient properties if needed
        // writeJson["ingredients"][index]["calories"] = ingredient.getCalories();
        // writeJson["ingredients"][index]["quantity"] = ingredient.getQuantity();
    }

    return writeJson;
}

// Update from JSON
void Tacos::updateFromJson(json::rvalue readValueJson) 
{
    id = readValueJson["id"].s();
    cost = readValueJson["cost"].d();

    // Setting ingredients
    for (json::rvalue ingredientReadValueJson : readValueJson["ingredients"])
    {
        ingredients.push_back(ingredientsMap.at(ingredientReadValueJson["name"].s()));
        // Add other ingredient properties if needed
        // ingredients.back().setCalories(ingredientReadValueJson["calories"].i());
        // ingredients.back().setQuantity(ingredientReadValueJson["quantity"].i());
    }
}
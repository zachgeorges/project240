#ifndef TACOS_H
#define TACOS_H

#include <crow.h>
#include <string>
#include <vector>
#include "Ingredient.h"
#include "Meat.h"
#include "Sauce.h"

class Tacos
{
public:
    // Constructors
    Tacos() {}
    Tacos(crow::json::rvalue readValueJson);

    // Getters
    std::string getId() const { return id; }
    std::vector<Ingredient> getIngredients() const { return ingredients; }
    std::vector<Meat> getMeats() const { return meats; }
    std::vector<Sauce> getSauces() const { return sauces; }

    // Setters
    void setId(std::string idParam) { id = idParam; }
    void setIngredients(const std::vector<Ingredient>& ingredientsParam) { ingredients = ingredientsParam; }
    void setMeats(const std::vector<Meat>& meatsParam) { meats = meatsParam; }
    void setSauces(const std::vector<Sauce>& saucesParam) { sauces = saucesParam; }

    // Convert to JSON.
    crow::json::wvalue convertToJson();

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string id;
    std::vector<Ingredient> ingredients;
    std::vector<Meat> meats;
    std::vector<Sauce> sauces;
};

#endif // TACOS_H
#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <crow.h>
#include <string>

class Ingredient
{
public:
    // Constructors
    Ingredient() {}
    Ingredient(crow::json::rvalue readValueJson);

    // Getters
    std::string getId() const { return id; }
    std::string getName() const { return name; }
    int getCalories() const { return calories; }
    int getQuantity() const { return quantity; }

    // Setters
    void setId(std::string idParam) { id = idParam; }
    void setName(std::string nameParam) { name = nameParam; }
    void setCalories(int caloriesParam) { calories = caloriesParam; }
    void setQuantity(int quantityParam) { quantity = quantityParam; }

    // Convert to JSON.
    virtual crow::json::wvalue convertToJson();

    // Update from JSON.
    virtual void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string id;
    std::string name;
    int calories;
    int quantity;
};

#endif // INGREDIENT_H
#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include <crow.h>

/**
 * @brief Represents an ingredient.
 * 
 * The Ingredient class is a base class for other specific ingredient classes,
 * such as Meat and Sauce. It includes common properties like calories, name, quantity, and id.
 */
class Ingredient 
{
public:
    // Constructor
    Ingredient() {}
    Ingredient(crow::json::rvalue readValueJson);

    // Id get/set
    std::string getId() const { return id; }
    void setId(std::string ingredientId) { id = ingredientId; }

    // Name get/set
    std::string getName() const { return name; }
    void setName(std::string ingredientName) { name = ingredientName; }

    // Calories get/set
    int getCalories() const { return calories; }
    void setCalories(int ingredientCalories) { calories = ingredientCalories; }

    // Quantity get/set 
    int getQuantity() const { return quantity; }
    void setQuantity(int ingredientQuantity) { quantity = ingredientQuantity; }

    // Convert to JSON
    crow::json::wvalue convertToJson();

    // Update from JSON
    void updateFromJson(crow::json::rvalue readValueJson);
    
private:
    std::string id;
    std::string name;
    int calories;
    int quantity;
};

#endif // INGREDIENT_H
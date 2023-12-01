#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

/**
 * @brief Represents an ingredient.
 * 
 * The Ingredient class is a template for other specific ingredient classes,
 * such as Meat and Sauce. It includes common properties like calories.
 */
template <typename T>
class Ingredient 
{
public:
    Ingredient() : calories(0) {}
    Ingredient(std::string name, int calories) : name(name), calories(calories) {}

    std::string getName() const { return name; }
    void setName(std::string ingredientName) { name = ingredientName; }

    int getCalories() const { return calories; }
    void setCalories(int ingredientCalories) { calories = ingredientCalories; }

    // Additional properties and methods can be added based on specific ingredient types.

private:
    std::string name;
    int calories;
};

#endif // INGREDIENT_H
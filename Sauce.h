#ifndef SAUCE_H
#define SAUCE_H

#include "Ingredient.h"

/**
 * @brief Represents a type of sauce ingredient.
 * 
 * The Sauce class is derived from the Ingredient template
 * and includes specific properties for a sauce ingredient.
 */
class Sauce : public Ingredient<Sauce>
{
public:
    Sauce() : Ingredient<Sauce>() {}
    Sauce(std::string name, int calories, bool isSpicy)
        : Ingredient<Sauce>(name, calories), spicy(isSpicy) {}

    bool getIsSpicy() const { return spicy; }
    void setIsSpicy(bool isSpicy) { spicy = isSpicy; }

private:
    bool spicy;
};

#endif // SAUCE_H
#ifndef MEAT_H
#define MEAT_H

#include "Ingredient.h"

/**
 * @brief Represents a type of meat ingredient.
 * 
 * The Meat class is derived from the Ingredient template
 * and includes specific properties for a meat ingredient.
 */
class Meat : public Ingredient<Meat>
{
public:
    Meat() : Ingredient<Meat>() {}
    Meat(std::string name, int calories, std::string meatType)
        : Ingredient<Meat>(name, calories), meatType(meatType) {}

    std::string getMeatType() const { return meatType; }
    void setMeatType(std::string type) { meatType = type; }

private:
    std::string meatType;
};

#endif // MEAT_H
#ifndef SAUCE_H
#define SAUCE_H

#include <string>
#include <crow.h>
#include "Ingredient.h"

/**
 * @brief Represents a type of sauce ingredient.
 * 
 * The Sauce class is derived from the Ingredient class
 * and includes specific properties for a sauce ingredient.
 */
class Sauce : public Ingredient
{
public:
    // Constructor
    Sauce() {}
    Sauce(crow::json::rvalue readValueJson);

    // Type get/set
    //std::string getType() const { return sauceType; }
    //void setType(std::string type) { sauceType = type; }

    // IsSpicy get/set
    bool getIsSpicy() const { return isSpicy; }
    void setIsSpicy(bool spicyParam) { isSpicy = spicyParam; }

    // Convert to JSON
    crow::json::wvalue convertToJson();

    // Update from JSON
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string sauceType;
    bool isSpicy;
};

#endif // SAUCE_H
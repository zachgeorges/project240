#ifndef MEAT_H
#define MEAT_H

#include <crow.h>
#include <string>
#include "Ingredient.h"

/**
 * @brief Represents a type of meat ingredient.
 * 
 * The Meat class is derived from the Ingredient class
 * and includes specific properties for a meat ingredient.
 */
class Meat : public Ingredient
{
public:
    // Constructor
    Meat() {}
    Meat(crow::json::rvalue readValueJson);

    // Type get/set
    //std::string getType() const { return meatType; }
    //void setType(std::string type) { meatType = type; }

    // IsPork get/set
    bool getIsPork() const { return isPork; }
    void setIsPork(bool porkParam) { isPork = porkParam; }

    // Convert to JSON
    crow::json::wvalue convertToJson();

    // Update from JSON
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string meatType;
    bool isPork;
};

#endif // MEAT_H


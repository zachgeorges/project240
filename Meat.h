#ifndef MEAT_H
#define MEAT_H

#include <crow.h>
#include <string>
#include "Ingredient.h"

class Meat : public Ingredient
{
public:
    // Constructor
    Meat() {}
    Meat(crow::json::rvalue readValueJson);

    // Getters
    std::string getMeatType() const { return meatType; }
    bool getIsPork() const { return isPork; }

    // Setters
    void setMeatType(std::string meatTypeParam) { meatType = meatTypeParam; }
    void setIsPork(bool porkParam) { isPork = porkParam; }

    // Convert to JSON.
    crow::json::wvalue convertToJson() override;

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson) override;

private:
    std::string meatType;
    bool isPork;
};

#endif // MEAT_H
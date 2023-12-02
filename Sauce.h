#ifndef SAUCE_H
#define SAUCE_H

#include <crow.h>
#include <string>
#include "Ingredient.h"

class Sauce : public Ingredient
{
public:
    // Constructor
    Sauce() {}
    Sauce(crow::json::rvalue readValueJson);

    // Getters
    std::string getSauceType() const { return sauceType; }
    bool getIsSpicy() const { return isSpicy; }

    // Setters
    void setSauceType(std::string sauceTypeParam) { sauceType = sauceTypeParam; }
    void setIsSpicy(bool spicyParam) { isSpicy = spicyParam; }

    // Convert to JSON.
    crow::json::wvalue convertToJson() override;

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson) override;

private:
    std::string sauceType;
    bool isSpicy;
};

#endif // SAUCE_H
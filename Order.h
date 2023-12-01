#ifndef ORDER_H
#define ORDER_H

#include <crow.h>
#include <string>
#include <vector>
#include "Tacos.h"

class Order
{
public:
    // Constructors
    Order() {}
    Order(crow::json::rvalue readValueJson);

    // id get/set
    std::string getId() const { return id; }
    void setId(std::string idParam) { id = idParam; }

    // tacos get/set
    std::vector<Tacos> getTacos() const { return tacos; }
    void setTacos(std::vector<Tacos>& tacosParam) { tacos = tacosParam; }

    // cost get/set
    float getCost() const { return cost; }
    void setCost(float costParam) { cost = costParam; }

    // Convert to JSON.
    virtual crow::json::wvalue convertToJson();

    // Update from JSON.
    virtual void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string id;
    std::vector<Tacos> tacos;
    float cost;
};

#endif // ORDER_H
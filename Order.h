#ifndef ORDER_H
#define ORDER_H

#include <crow.h>
#include <string>
#include <vector>
#include "Tacos.h"
#include "Soda.h"

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
    void setTacos(const std::vector<Tacos>& tacosParam) { tacos = tacosParam; }

    // sodas get/set
    std::vector<Soda> getSodas() const { return sodas; }
    void setSodas(const std::vector<Soda>& sodasParam) { sodas = sodasParam; }

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
    std::vector<Soda> sodas;
    float cost;
};

#endif // ORDER_H
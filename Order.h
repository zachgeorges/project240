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

    // Getters
    std::string getId() const { return id; }
    std::vector<Tacos> getTacos() const { return tacos; }
    std::vector<Soda> getSodas() const { return sodas; }
    float getCost() const { return cost; }

    // Setters
    void setId(std::string idParam) { id = idParam; }
    void setTacos(const std::vector<Tacos>& tacosParam) { tacos = tacosParam; }
    void setSodas(const std::vector<Soda>& sodasParam) { sodas = sodasParam; }
    void setCost(float costParam) { cost = costParam; }

    // Convert to JSON.
    crow::json::wvalue convertToJson();

    // Update from JSON.
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string id;
    std::vector<Tacos> tacos;
    std::vector<Soda> sodas;
    float cost;
};

#endif // ORDER_H
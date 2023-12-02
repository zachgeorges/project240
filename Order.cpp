#include "Order.h"

using namespace std;
using namespace crow;

extern map<std::string, Tacos> tacosMap;
extern map<std::string, Soda> sodasMap;

Order::Order(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Order::convertToJson() 
{
    json::wvalue writeJson;
    writeJson["id"] = id;
    writeJson["cost"] = cost;

    // Convert tacos to json (Save only the ids)
    int tacoIndex = 0;
    for (Tacos taco : tacos) 
    {
        writeJson["tacos"][tacoIndex]["id"] = taco.getId();
        // Add other taco properties if needed
        // writeJson["tacos"][tacoIndex]["cost"] = taco.getCost();
    }

    // Convert sodas to json (Save only the ids)
    int sodaIndex = 0;
    for (Soda soda : sodas) 
    {
        writeJson["sodas"][sodaIndex]["id"] = soda.getId();
        // Add other soda properties if needed
        // writeJson["sodas"][sodaIndex]["cost"] = soda.getCost();
    }

    return writeJson;
}

// Update from JSON
void Order::updateFromJson(json::rvalue readValueJson) 
{
    id = readValueJson["id"].s();
    cost = readValueJson["cost"].d();

    // Setting tacos
    for (json::rvalue tacoReadValueJson : readValueJson["tacos"])
    {
        tacos.push_back(tacosMap.at(tacoReadValueJson["id"].s()));
        // Add other taco properties if needed
        // tacos.back().setCost(tacoReadValueJson["cost"].d());
    }

    // Setting sodas
    for (json::rvalue sodaReadValueJson : readValueJson["sodas"])
    {
        sodas.push_back(sodasMap.at(sodaReadValueJson["id"].s()));
        // Add other soda properties if needed
        // sodas.back().setCost(sodaReadValueJson["cost"].d());
    }
}
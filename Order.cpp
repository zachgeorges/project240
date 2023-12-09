#include "Order.h"

using namespace std;
using namespace crow;

extern map<std::string, Soda> sodasMap;
extern map<std::string, Tacos> tacosMap;

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

    // Convert tacos to JSON
    int index = 0;
    for (Tacos taco : tacos) 
    {
        writeJson["tacos"][index]["id"] = taco.getId();
        index++;
    }

    // Convert sodas to JSON
    index = 0;
    for (Soda soda : sodas) 
    {
        writeJson["sodas"][index]["id"] = soda.getId(); 
        index++;
    }

    return writeJson;
}

// Update from JSON
void Order::updateFromJson(json::rvalue readValueJson) 
{
    id = readValueJson["id"].s();
    cost = readValueJson["cost"].d();

    // Setting tacos
    for (json::rvalue tacosReadValueJson : readValueJson["tacos"])
    {
        tacos.push_back(tacosMap.at(tacosReadValueJson["id"].s()));
    }

    // Setting sodas
    for (json::rvalue sodaReadValueJson : readValueJson["sodas"])
    {
        sodas.push_back(sodasMap.at(sodaReadValueJson["id"].s()));
    }
}
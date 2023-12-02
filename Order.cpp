#include "Order.h"

using namespace std;
using namespace crow;

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
        writeJson["tacos"][index]["id"] = taco.convertToJson();
        index++;
    }

    // Convert sodas to JSON
    index = 0;
    for (Soda soda : sodas) 
    {
        writeJson["sodas"][index]["id"] = soda.convertToJson();
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
    for (json::rvalue tacoReadValueJson : readValueJson["tacos"])
    {
        Tacos taco(tacoReadValueJson);
        tacos.push_back(taco);
    }

    // Setting sodas
    for (json::rvalue sodaReadValueJson : readValueJson["sodas"])
    {
        Soda soda(sodaReadValueJson);
        sodas.push_back(soda);
    }
}
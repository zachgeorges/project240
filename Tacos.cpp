#include "Tacos.h"

using namespace std;
using namespace crow;

extern map<std::string, Meat> meatsMap;
extern map<std::string, Sauce> saucesMap;

Tacos::Tacos(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Tacos::convertToJson() 
{
    json::wvalue writeJson;
    writeJson["id"] = id;

    // Convert meats to JSON
    int index = 0;
    for (Meat meat : meats) 
    {
        writeJson["meats"][index][id] = meat.convertToJson();
        index++;
    }

    // Convert sauces to JSON
    index = 0;
    for (Sauce sauce : sauces) 
    {
        writeJson["sauces"][index][id] = sauce.convertToJson();
        index++;
    }

    return writeJson;
}

// Update from JSON
void Tacos::updateFromJson(json::rvalue readValueJson) 
{
    id = readValueJson["id"].s();

    // Setting meats
    for (json::rvalue meatReadValueJson : readValueJson["meats"])
    {
        meats.push_back(meatsMap.at(meatReadValueJson["id"].s()));
    }

    // Setting sauces
    for (json::rvalue sauceReadValueJson : readValueJson["sauces"])
    {
        sauces.push_back(saucesMap.at(sauceReadValueJson["id"].s()));
    }
}
#include "Soda.h"

using namespace std;
using namespace crow;

Soda::Soda(json::rvalue readValueJson)  
{
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Soda::convertToJson() 
{
    json::wvalue writeJson;
    writeJson["id"] = id;
    writeJson["size"] = size;
    writeJson["type"] = type;
    writeJson["isZeroCalorie"] = isZero;
    return writeJson;
}

// Update from JSON
void Soda::updateFromJson(json::rvalue readValueJson) 
{
    id = readValueJson["id"].s();
    size = readValueJson["size"].s();
    type = readValueJson["type"].s();
    isZero = readValueJson["isZeroCalorie"].b();
}
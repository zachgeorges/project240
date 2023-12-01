#include <crow.h>
#include <map>
#include <string>
#include "MeatFunctions.h"

using namespace std;
using namespace crow;

std::map<std::string, Meat> meatsMap;

json::wvalue convertMeatToJson(Meat meat) 
{
    json::wvalue writeValueJson;
    writeValueJson["name"] = meat.getName();
    writeValueJson["calories"] = meat.getCalories();
    writeValueJson["meatType"] = meat.getMeatType();
    return writeValueJson;
}

response searchMeats(string searchString) 
{
    vector<Meat> found;
    for (pair<string, Meat> meatPair : meatsMap) 
    {
        if (meatPair.second.getName().find(searchString) != string::npos) 
        {
            found.push_back(meatPair.second);
        }
    }

    json::wvalue jsonWriteValue;
    int index = 0;
    for (Meat meat : found)
    {
        jsonWriteValue[index] = convertMeatToJson(meat);
        index++;
    }

    return response(jsonWriteValue.dump());
}

struct
{
    bool operator()(pair<string, Meat>& a, pair<string, Meat>& b) 
    { 
        return a.second.getName() < b.second.getName(); 
    } 
} comparatorMeat;

response sortMeats(string sortString) 
{
    vector<pair<string, Meat>> meatsToSort;
    for (pair<string, Meat> meatPair : meatsMap) 
    {
        meatsToSort.push_back(meatPair);
    }

    if (sortString == "name")
    {
        sort(meatsToSort.begin(), meatsToSort.end(), comparatorMeat); 
    }

    json::wvalue jsonWriteValue;
    int index = 0;
    for (pair<string, Meat> meatPair : meatsToSort)
    {
        jsonWriteValue[index] = convertMeatToJson(meatPair.second);
        index++;
    }

    return response(jsonWriteValue.dump());
}

response createMeat(request req) 
{
    json::rvalue readValueJson = json::load(req.body);

    if (!readValueJson) 
        return response(400, "Invalid JSON");
    
    Meat meat{readValueJson["name"].s(), readValueJson["calories"].i(), readValueJson["meatType"].s()};
    meatsMap[meat.getName()] = meat;

    return response(201, convertMeatToJson(meat).dump());
}

response readMeat(string name) 
{
    try 
    {
        Meat meat = meatsMap.at(name);
        return response(convertMeatToJson(meat).dump());
    } 
    catch (out_of_range& exception) 
    {
        return response(404, "Meat Not Found");
    }
}

response readAllMeats(request req) 
{
    if (req.url_params.get("search"))
    {
        return searchMeats(req.url_params.get("search"));
    }

    if (req.url_params.get("sort"))
    {
        return sortMeats(req.url_params.get("sort"));
    }

    json::wvalue jsonWriteValue;
    int index = 0;
    for (pair<string, Meat> keyValuePair : meatsMap)
    {
        jsonWriteValue[index] = convertMeatToJson(keyValuePair.second);
        index++;
    }

    return response(jsonWriteValue.dump());
}

void updateMeat(request req, response& res, string name) 
{
    try 
    {
        Meat meat = meatsMap.at(name);
        json::rvalue readValueJson = json::load(req.body);

        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        meat.setCalories(readValueJson["calories"].i());
        meat.setMeatType(readValueJson["meatType"].s());
        meatsMap[name] = meat;

        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(convertMeatToJson(meat).dump());
        res.end();
    } 
    catch (out_of_range& exception) 
    {
        res.code = 404;
        res.end("Meat Not Found");
    }
}

response deleteMeat(string name) 
{
    try 
    {
        Meat meat = meatsMap.at(name);
        meatsMap.erase(name);
        return response(204);
    } 
    catch (out_of_range& exception) 
    {
        return response(404, "Meat not found");
    }
}

void saveMeatsToFile(map<string, Meat> data, string filename)  
{
    ofstream file(filename);

    if (file.is_open()) 
    {
        json::wvalue jsonWriteValue;
        int index = 0;
        for (pair<string, Meat> keyValuePair : data)
        {
            jsonWriteValue[index] = convertMeatToJson(keyValuePair.second);
            index++;
        }

        file << jsonWriteValue.dump();
        file.close();
    }
}

map<string, Meat> loadMeatsFromFile(string filename) 
{
    map<string, Meat> data;
    
    ifstream file(filename);

    if (file.is_open()) 
    {      
        ostringstream stringStreamJson;
        stringStreamJson << file.rdbuf();
        json::rvalue jsonReadValue = json::load(stringStreamJson.str());
        file.close();

        for (json::rvalue item : jsonReadValue) 
        {
            Meat meat{item["name"].s(), item["calories"].i(), item["meatType"].s()};
            data[meat.getName()] = meat;
        }
    }
    
    return data;
}
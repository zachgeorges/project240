#include <crow.h>
#include <map>
#include <string>
#include "SauceFunctions.h"

using namespace std;
using namespace crow;

std::map<std::string, Sauce> saucesMap;

json::wvalue convertSauceToJson(Sauce sauce) 
{
    json::wvalue writeValueJson;
    writeValueJson["name"] = sauce.getName();
    writeValueJson["calories"] = sauce.getCalories();
    writeValueJson["isSpicy"] = sauce.getIsSpicy();
    return writeValueJson;
}

response searchSauces(string searchString) 
{
    vector<Sauce> found;
    for (pair<string, Sauce> saucePair : saucesMap) 
    {
        if (saucePair.second.getName().find(searchString) != string::npos) 
        {
            found.push_back(saucePair.second);
        }
    }

    json::wvalue jsonWriteValue;
    int index = 0;
    for (Sauce sauce : found)
    {
        jsonWriteValue[index] = convertSauceToJson(sauce);
        index++;
    }

    return response(jsonWriteValue.dump());
}

struct
{
    bool operator()(pair<string, Sauce>& a, pair<string, Sauce>& b) 
    { 
        return a.second.getName() < b.second.getName(); 
    } 
} comparatorSauce;

response sortSauces(string sortString) 
{
    vector<pair<string, Sauce>> saucesToSort;
    for (pair<string, Sauce> saucePair : saucesMap) 
    {
        saucesToSort.push_back(saucePair);
    }

    if (sortString == "name")
    {
        sort(saucesToSort.begin(), saucesToSort.end(), comparatorSauce); 
    }

    json::wvalue jsonWriteValue;
    int index = 0;
    for (pair<string, Sauce> saucePair : saucesToSort)
    {
        jsonWriteValue[index] = convertSauceToJson(saucePair.second);
        index++;
    }

    return response(jsonWriteValue.dump());
}

response filterSauces(bool isSpicy) 
{
    vector<Sauce> found;
    for (pair<string, Sauce> saucePair : saucesMap) 
    {
        if (saucePair.second.getIsSpicy() == isSpicy) 
        {
            found.push_back(saucePair.second);
        }
    }

    json::wvalue jsonWriteValue;
    int index = 0;
    for (Sauce sauce : found)
    {
        jsonWriteValue[index] = convertSauceToJson(sauce);
        index++;
    }

    return response(jsonWriteValue.dump());
}

response createSauce(request req) 
{
    json::rvalue readValueJson = json::load(req.body);

    if (!readValueJson) 
        return response(400, "Invalid JSON");
    
    Sauce sauce{readValueJson["name"].s(), readValueJson["calories"].i(), readValueJson["isSpicy"].b()};
    saucesMap[sauce.getName()] = sauce;

    return response(201, convertSauceToJson(sauce).dump());
}

response readSauce(string name) 
{
    try 
    {
        Sauce sauce = saucesMap.at(name);
        return response(convertSauceToJson(sauce).dump());
    } 
    catch (out_of_range& exception) 
    {
        return response(404, "Sauce Not Found");
    }
}

response readAllSauces(request req) 
{
    if (req.url_params.get("search"))
    {
        return searchSauces(req.url_params.get("search"));
    }

    if (req.url_params.get("sort"))
    {
        return sortSauces(req.url_params.get("sort"));
    }

    if (req.url_params.get("isspicy"))
    {
        bool isSpicy = (string(req.url_params.get("isspicy")) == "TRUE" || string(req.url_params.get("isspicy")) == "true");
        return filterSauces(isSpicy);
    }

    json::wvalue jsonWriteValue;
    int index = 0;
    for (pair<string, Sauce> keyValuePair : saucesMap)
    {
        jsonWriteValue[index] = convertSauceToJson(keyValuePair.second);
        index++;
    }

    return response(jsonWriteValue.dump());
}

void updateSauce(request req, response& res, string name) 
{
    try 
    {
        Sauce sauce = saucesMap.at(name);
        json::rvalue readValueJson = json::load(req.body);

        if (!readValueJson) 
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        sauce.setCalories(readValueJson["calories"].i());
        sauce.setIsSpicy(readValueJson["isSpicy"].b());
        saucesMap[name] = sauce;

        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(convertSauceToJson(sauce).dump());
        res.end();
    } 
    catch (out_of_range& exception) 
    {
        res.code = 404;
        res.end("Sauce Not Found");
    }
}

response deleteSauce(string name) 
{
    try 
    {
        Sauce sauce = saucesMap.at(name);
        saucesMap.erase(name);
        return response(204);
    } 
    catch (out_of_range& exception) 
    {
        return response(404, "Sauce not found");
    }
}

void saveSaucesToFile(map<string, Sauce> data, string filename)  
{
    ofstream file(filename);

    if (file.is_open()) 
    {
        json::wvalue jsonWriteValue;
        int index = 0;
        for (pair<string, Sauce> keyValuePair : data)
        {
            jsonWriteValue[index] = convertSauceToJson(keyValuePair.second);
            index++;
        }

        file << jsonWriteValue.dump();
        file.close();
    }
}

map<string, Sauce> loadSaucesFromFile(string filename) 
{
    map<string, Sauce> data;
    
    ifstream file(filename);

    if (file.is_open()) 
    {      
        ostringstream stringStreamJson;
        stringStreamJson << file.rdbuf();
        json::rvalue jsonReadValue = json::load(stringStreamJson.str());
        file.close();

        for (json::rvalue item : jsonReadValue) 
        {
            Sauce sauce{item["name"].s(), item["calories"].i(), item["isSpicy"].b()};
            data[sauce.getName()] = sauce;
        }
    }
    
    return data;
}
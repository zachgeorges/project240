#include <crow.h>
#include <map>
#include <string>
#include "SodaFunctions.h"

using namespace std;
using namespace crow;

extern map<string, Soda> sodasMap;

json::wvalue convertSodaToJson(Soda soda)
{
    json::wvalue writeValueJson;
    writeValueJson["size"] = soda.getSize();
    writeValueJson["type"] = soda.getType();
    writeValueJson["isZero"] = soda.getIsZeroCalorie();
    return writeValueJson;
}

// Function to handle the GET request that includes the search parameter for searching sodas
response searchSodas(string searchString)
{
    vector<Soda> found;
    // For each string/Soda pair in the sodas map.
    for (pair<string, Soda> sodaPair : sodasMap)
    {
        // If the search string is found in the Soda as a substring then add it to the found vector.
        if (sodaPair.second.getSize().find(searchString) != string::npos)
        {
            found.push_back(sodaPair.second);
        }
    }

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;

    // For each soda in the vector, convert the soda to JSON and add to the write value.
    int index = 0;
    for (Soda soda : found)
    {
        jsonWriteValue[index] = convertSodaToJson(soda);
        index++;
    }

    return response(jsonWriteValue.dump());
}

// Comparator to sort pairs according to the second value soda.
struct
{
    bool operator()(pair<string, Soda>& a, pair<string, Soda>& b)
    {
        return a.second.getSize() < b.second.getSize();
    }
} comparatorSoda;

// Function to handle the GET request that includes the sort parameter for sorting sodas
response sortSodas(string sortString)
{
    // Vector to store the soda pairs.
    vector<pair<string, Soda>> sodasToSort;

    // For each string/Soda pair in the sodas map.
    for (pair<string, Soda> sodaPair : sodasMap)
    {
        sodasToSort.push_back(sodaPair);
    }

    if (sortString == "size")
    {
        // Sort using the comparator function
        sort(sodasToSort.begin(), sodasToSort.end(), comparatorSoda);
    }

    // Create a new JSON write value use to write to the file.
    json::wvalue jsonWriteValue;

    // For each soda in the vector, convert the soda to JSON and add to the write value.
    int index = 0;
    for (pair<string, Soda> sodaPair : sodasToSort)
    {
        jsonWriteValue[index] = convertSodaToJson(sodaPair.second);
        index++;
    }

    return response(jsonWriteValue.dump());
}

// Function to handle the GET request that filters sodas.
response filterSodas(bool isZeroCalorie)
{
    vector<Soda> found;
    // For each string/Soda pair in the sodas map.
    for (pair<string, Soda> sodaPair : sodasMap)
    {
        // If the search string is found in the Soda as a substring then add it to the found vector.
        if (sodaPair.second.getIsZeroCalorie() == isZeroCalorie)
        {
            found.push_back(sodaPair.second);
        }
    }

    // Create a new JSON write value used to write to the file.
    json::wvalue jsonWriteValue;

    // For each soda in the vector, convert the soda to JSON and add to the write value.
    int index = 0;
    for (Soda soda : found)
    {
        jsonWriteValue[index] = convertSodaToJson(soda);
        index++;
    }

    return response(jsonWriteValue.dump());
}

response createSoda(request req)
{
    // Load the request body string into a JSON read value.
    json::rvalue readValueJson = json::load(req.body);

    // If there was a problem converting the body text to JSON, return an error.
    if (!readValueJson)
        return response(400, "Invalid JSON");

    // Create a new Soda.
    Soda soda{readValueJson["size"].s(), readValueJson["type"].s(), readValueJson["isZero"].b()};

    // Add the new Soda to the map.
    sodasMap[soda.getSize()] = soda;

    // Return the created Soda as a JSON string.
    return response(201, convertSodaToJson(soda).dump());
}

response readSoda(string size)
{
    try
    {
        // Get the Soda from the sodas map.
        Soda soda = sodasMap.at(size);

        // Return the Soda as a JSON string.
        return response(convertSodaToJson(soda).dump());
    }
    catch (out_of_range& exception)
    {
        // If the Soda was not found in the map return a 404 not found error.
        return response(404, "Soda Not Found");
    }
}

response readAllSodas(request req)
{
    // If there is a search parameter on the request, then search for sodas.
    if (req.url_params.get("search"))
    {
        return searchSodas(req.url_params.get("search"));
    }

    // If there is a sort parameter on the request, then sort the sodas.
    if (req.url_params.get("sort"))
    {
        return sortSodas(req.url_params.get("sort"));
    }

    // If there is an iszerocalorie parameter on the request, then filter for zero-calorie sodas.
    if (req.url_params.get("iszerocalorie"))
    {
        bool isZeroCalorie = false;
        if (string(req.url_params.get("iszerocalorie")) == "TRUE" || string(req.url_params.get("iszerocalorie")) == "true")
        {
            isZeroCalorie = true;
        }
        return filterSodas(isZeroCalorie);
    }

    // Create a new JSON write value used to write to the file.
    json::wvalue jsonWriteValue;

    // For each Soda in the map, convert the Soda to JSON and add to the write value.
    int index = 0;
    for (pair<string, Soda> keyValuePair : sodasMap)
    {
        // first: gives you access to the first item in the pair.
        // second: gives you access to the second item in the pair.
        jsonWriteValue[index] = convertSodaToJson(keyValuePair.second);
        index++;
    }

    return response(jsonWriteValue.dump());
}

void updateSoda(request req, response& res, string size)
{
    try
    {
        // Get the Soda from the sodas map.
        Soda soda = sodasMap.at(size);

        // Convert the request body to JSON.
        json::rvalue readValueJson = json::load(req.body);

        // If there was a problem converting the body text to JSON, return an error.
        if (!readValueJson)
        {
            res.code = 400;
            res.end("Invalid JSON");
            return;
        }

        // Update the Soda.
        soda.setType(readValueJson["type"].s());
        soda.setIsZeroCalorie(readValueJson["isZero"].b());
        sodasMap[size] = soda;

        // Return the updated Soda as a JSON string.
        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(convertSodaToJson(soda).dump());
        res.end();
    }
    catch (out_of_range& exception)
    {
        // If the Soda was not found in the map, return a 404 not found error.
        res.code = 404;
        res.end("Soda Not Found");
    }
}

response deleteSoda(string size)
{
    try
    {
        // Get the Soda from the sodas map.
        Soda soda = sodasMap.at(size);

        // Remove the Soda from the sodas map.
        sodasMap.erase(size);

        // Return a successful code 204 which means success but no content to return.
        return response(204);
    }
    catch (out_of_range& exception)
    {
        // If the Soda was not found in the map, return a 404 not found error.
        return response(404, "Soda not found");
    }
}

void saveToFile(map<string, Soda> data, string filename)
{
    // Open the file for writing.
    ofstream file(filename);

    if (file.is_open())
    {
        // Create a new JSON write value used to write to the file.
        json::wvalue jsonWriteValue;

        // For each object in the map, convert the object to JSON and add to the write value.
        int index = 0;
        for (pair<string, Soda> keyValuePair : data)
        {
            // first: gives you access to the first item in the pair.
            // second: gives you access to the second item in the pair.
            jsonWriteValue[index] = convertSodaToJson(keyValuePair.second);
            index++;
        }

        // Write the JSON to the file.
        file << jsonWriteValue.dump();
        file.close();
    }
}

map<string, Soda> loadFromFile(string filename)
{
    map<string, Soda> data;

    // Open the file for reading.
    ifstream file(filename);

    // If the file is open.
    if (file.is_open())
    {
        // Create a stream for reading in the file.
        ostringstream stringStreamJson;

        // Read the entire JSON string.
        stringStreamJson << file.rdbuf();

        // Load the string into a JSON read value object.
        json::rvalue jsonReadValue = json::load(stringStreamJson.str());

        // Close the file.
        file.close();

        // For each item in the JSON, convert it to an object,
        // and add it to the data map.
        for (json::rvalue item : jsonReadValue)
        {
            Soda soda{item["size"].s(), item["type"].s(), item["isZero"].b()};
            data[soda.getSize()] = soda;
        }
    }

    return data;
}
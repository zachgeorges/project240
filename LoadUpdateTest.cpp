#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "Soda.h"
#include "LoadUpdate.h"

using namespace std;
using namespace crow;

TEST_CASE("Saving to a file and loading from a file for Soda") 
{
    // Load a resources to read.
    map<string, Soda> sodasMap;
    sodasMap["1"] = Soda{json::load(R"({"id":"1","size":"Large","type":"Cola","isZeroCalorie":false})")};
    sodasMap["2"] = Soda{json::load(R"({"id":"2","size":"Medium","type":"Lemonade","isZeroCalorie":true})")};
    sodasMap["3"] = Soda{json::load(R"({"id":"3","size":"Small","type":"Orange","isZeroCalorie":false})")};

    // Perform the action
    saveToFile<Soda>(sodasMap, "LoadUpdateTest.json");
    map<string, Soda> sodasMapLoaded = loadFromFile<Soda>("LoadUpdateTest.json");

    // Check the results
    CHECK(sodasMap.size() == sodasMapLoaded.size());
    CHECK(sodasMap.at("1").getId() == sodasMapLoaded.at("1").getId());
    CHECK(sodasMap.at("1").getSize() == sodasMapLoaded.at("1").getSize());
    CHECK(sodasMap.at("1").getType() == sodasMapLoaded.at("1").getType());
    CHECK(sodasMap.at("1").getIsZeroCalorie() == sodasMapLoaded.at("1").getIsZeroCalorie());

    CHECK(sodasMap.at("2").getId() == sodasMapLoaded.at("2").getId());
    CHECK(sodasMap.at("2").getSize() == sodasMapLoaded.at("2").getSize());
    CHECK(sodasMap.at("2").getType() == sodasMapLoaded.at("2").getType());
    CHECK(sodasMap.at("2").getIsZeroCalorie() == sodasMapLoaded.at("2").getIsZeroCalorie());

    CHECK(sodasMap.at("3").getId() == sodasMapLoaded.at("3").getId());
    CHECK(sodasMap.at("3").getSize() == sodasMapLoaded.at("3").getSize());
    CHECK(sodasMap.at("3").getType() == sodasMapLoaded.at("3").getType());
    CHECK(sodasMap.at("3").getIsZeroCalorie() == sodasMapLoaded.at("3").getIsZeroCalorie());
}

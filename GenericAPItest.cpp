#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include "Soda.h"
#include "Meat.h"
#include "Sauce.h"
#include "Tacos.h"
#include "Order.h"
#include "GenericAPI.h"

using namespace std;
using namespace crow;

map<string, Soda> sodasMap;
map<std::string, Sauce> saucesMap;
map<std::string, Meat> meatsMap;
map<std::string, Tacos> tacosMap;
map<std::string, Order> ordersMap;

TEST_CASE("Creating a new Soda resource") 
{
    // Setup resource map to be empty before the test
    GenericAPI<Soda>::resourceMap.clear();

    request req;
    req.body = R"({"isZeroCalorie":false,"type":"Cola","id":"1","size":"Large"})"; 


    response res = GenericAPI<Soda>::createResource(req);

    // Check the results
    json::rvalue expectedJson = json::load(req.body);
    json::rvalue actualJson = json::load(res.body);

    CHECK(res.code == 201); // Check that the response code is 201 Created

    CHECK(req.body == res.body);

    CHECK(GenericAPI<Soda>::resourceMap.size() == 1); // Ensure the resource was added to the map
    CHECK(GenericAPI<Soda>::resourceMap.at("1").getId() == "1"); // Validate the resource content
    CHECK(GenericAPI<Soda>::resourceMap.at("1").getSize() == "Large"); // Validate the resource content
    CHECK(!GenericAPI<Soda>::resourceMap.at("1").getIsZeroCalorie()); // Validate the resource content
}

TEST_CASE("Reading a Soda resource") 
{
    // Load a resource to read.
    sodasMap["1"] = Soda{json::load(R"({"isZeroCalorie":false,"type":"Cola","id":"1","size":"Large"})")};


    GenericAPI<Soda>::resourceMap = sodasMap;
    response res = GenericAPI<Soda>::readResource("1");

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == sodasMap["1"].convertToJson().dump()); // Validate the reponse body
    CHECK(GenericAPI<Soda>::resourceMap.size() == 1); // Ensure that no resources were added or removed from the map
}

TEST_CASE("Reading all Soda resources") 
{
    // Load resources to read.
    sodasMap["1"] = Soda{json::load(R"({"isZeroCalorie":false,"type":"Cola","id":"1","size":"Large"})")};
    sodasMap["2"] = Soda{json::load(R"({"isZeroCalorie":true,"type":"Lemonade","id":"2","size":"Medium"})")};
    sodasMap["3"] = Soda{json::load(R"({"isZeroCalorie":false,"type":"Orange","id":"3","size":"Small"})")};


    GenericAPI<Soda>::resourceMap = sodasMap;
    response res = GenericAPI<Soda>::readAllResources();

    // Create the expected response body
    string expectedResponseBody = R"([{"isZeroCalorie":false,"type":"Cola","id":"1","size":"Large"},{"size":"Medium","id":"2","type":"Lemonade","isZeroCalorie":true},{"isZeroCalorie":false,"type":"Orange","id":"3","size":"Small"}])";

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == expectedResponseBody); // Validate the reponse body
    CHECK(GenericAPI<Soda>::resourceMap.size() == 3); // Ensure that no resources were added or removed from the map
}

TEST_CASE("Updating a Soda resource") 
{
    // Load resources to update.
    
    sodasMap["1"] = Soda{json::load(R"({"isZeroCalorie":false,"type":"Cola","id":"1","size":"Large"})")};
    sodasMap["2"] = Soda{json::load(R"({"isZeroCalorie":true,"type":"Lemonade","id":"2","size":"Medium"})")};
    sodasMap["3"] = Soda{json::load(R"({"isZeroCalorie":false,"type":"Orange","id":"3","size":"Small"})")};


    GenericAPI<Soda>::resourceMap = sodasMap;
    request req;
    req.body = R"({"isZeroCalorie":false,"type":"Fanta","id":"2","size":"Large"})"; 
    response res;


    GenericAPI<Soda>::updateResource(req, res, "2");

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Soda>::resourceMap.size() == 3); // Ensure no resource was added or removed from the map
    CHECK(GenericAPI<Soda>::resourceMap.at("2").getSize() == "Large"); // Validate the resource content
    CHECK(!GenericAPI<Soda>::resourceMap.at("2").getIsZeroCalorie()); // Validate the resource content
}

TEST_CASE("Updating a non-existing Soda resource") 
{
    // Setup resource map to be empty before the test
    GenericAPI<Soda>::resourceMap.clear();


    request req;
    req.body = R"({"id":"1","size":"Medium","type":"Root Beer","isZeroCalorie":false})"; 

    response res;


    GenericAPI<Soda>::updateResource(req, res, "1");

    // Check the results
    CHECK(res.code == 404); // Check that the response code is 404 Not Found
    CHECK(res.body == "Resource Not Found"); // Validate the reponse body
    CHECK(GenericAPI<Soda>::resourceMap.size() == 0); // Ensure no resource was added to the map
}

TEST_CASE("Deleting a Soda resource") 
{
    // Load resources to delete.
    sodasMap["1"] = Soda{json::load(R"({"isZeroCalorie":false,"type":"Cola","id":"1","size":"Large"})")};
    sodasMap["2"] = Soda{json::load(R"({"isZeroCalorie":true,"type":"Lemonade","id":"2","size":"Medium"})")};
    sodasMap["3"] = Soda{json::load(R"({"isZeroCalorie":false,"type":"Orange","id":"3","size":"Small"})")};

    GenericAPI<Soda>::resourceMap = sodasMap;
    response res = GenericAPI<Soda>::deleteResource("2");

    // Check the results
    CHECK(res.code == 204); // Check that the response code is 204 No Content
    CHECK(res.body == ""); // Validate the response body
    CHECK(GenericAPI<Soda>::resourceMap.size() == 2); // Ensure one resource was removed from the map
    CHECK(GenericAPI<Soda>::resourceMap.find("2") == GenericAPI<Soda>::resourceMap.end()); // Ensure the resource is removed
}

TEST_CASE("Creating a new Soda resource with invalid JSON") 
{
    // Setup resource map to be empty before the test
    GenericAPI<Soda>::resourceMap.clear();

    request req;
    // Invalid JSON with missing closing brace
    req.body = R"({"isZeroCalorie":false,"type":"Cola","id":"1","size":"Large")"; 

    response res = GenericAPI<Soda>::createResource(req);

    // Check the results
    CHECK(res.code == 400); // Check that the response code is 400 Bad Request
    CHECK(res.body == "Invalid JSON"); // Validate the response body
    CHECK(GenericAPI<Soda>::resourceMap.size() == 0); // Ensure no resource was added to the map
}
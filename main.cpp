#include <crow.h>
#include <map>
#include <csignal>
#include <string>
#include "Ingredient.h"
#include "Soda.h"
#include "Tacos.h"
#include "Meat.h"
#include "Sauce.h"
#include "Order.h"  
#include "GenericAPI.h"
#include "LoadUpdate.h"

using namespace std;
using namespace crow;

// Load resources from files.
map<std::string, Ingredient> ingredientsMap = loadFromFile<Ingredient>("ingredients.json");
map<std::string, Soda> sodasMap = loadFromFile<Soda>("sodas.json");
map<std::string, Tacos> tacosMap = loadFromFile<Tacos>("tacos.json");
map<std::string, Meat> meatsMap = loadFromFile<Meat>("meats.json");
map<std::string, Sauce> saucesMap = loadFromFile<Sauce>("sauces.json");
map<std::string, Order> ordersMap = loadFromFile<Order>("orders.json");

int main() 
{
    // Create GenericAPIs to use in the CROW_ROUTES
    GenericAPI<Ingredient>::resourceMap = ingredientsMap;
    GenericAPI<Soda>::resourceMap = sodasMap;
    GenericAPI<Tacos>::resourceMap = tacosMap;
    GenericAPI<Meat>::resourceMap = meatsMap;
    GenericAPI<Sauce>::resourceMap = saucesMap;
    GenericAPI<Order>::resourceMap = ordersMap;

    // Setup the simple web service.
    SimpleApp app;

    // Define resources:

    // Ingredients
    CROW_ROUTE(app, "/api/ingredients").methods("POST"_method)(GenericAPI<Ingredient>::createResource);
    CROW_ROUTE(app, "/api/ingredients").methods("GET"_method)(GenericAPI<Ingredient>::readAllResources);
    CROW_ROUTE(app, "/api/ingredients/<string>").methods("GET"_method)(GenericAPI<Ingredient>::readResource);
    CROW_ROUTE(app, "/api/ingredients/<string>").methods("PUT"_method)(GenericAPI<Ingredient>::updateResource);
    CROW_ROUTE(app, "/api/ingredients/<string>").methods("DELETE"_method)(GenericAPI<Ingredient>::deleteResource);

    // Sodas
    CROW_ROUTE(app, "/api/sodas").methods("POST"_method)(GenericAPI<Soda>::createResource);
    CROW_ROUTE(app, "/api/sodas").methods("GET"_method)(GenericAPI<Soda>::readAllResources);
    CROW_ROUTE(app, "/api/sodas/<string>").methods("GET"_method)(GenericAPI<Soda>::readResource);
    CROW_ROUTE(app, "/api/sodas/<string>").methods("PUT"_method)(GenericAPI<Soda>::updateResource);
    CROW_ROUTE(app, "/api/sodas/<string>").methods("DELETE"_method)(GenericAPI<Soda>::deleteResource);

    // Tacos
    CROW_ROUTE(app, "/api/tacos").methods("POST"_method)(GenericAPI<Tacos>::createResource);
    CROW_ROUTE(app, "/api/tacos").methods("GET"_method)(GenericAPI<Tacos>::readAllResources);
    CROW_ROUTE(app, "/api/tacos/<string>").methods("GET"_method)(GenericAPI<Tacos>::readResource);
    CROW_ROUTE(app, "/api/tacos/<string>").methods("PUT"_method)(GenericAPI<Tacos>::updateResource);
    CROW_ROUTE(app, "/api/tacos/<string>").methods("DELETE"_method)(GenericAPI<Tacos>::deleteResource);

    // Meats
    CROW_ROUTE(app, "/api/meats").methods("POST"_method)(GenericAPI<Meat>::createResource);
    CROW_ROUTE(app, "/api/meats").methods("GET"_method)(GenericAPI<Meat>::readAllResources);
    CROW_ROUTE(app, "/api/meats/<string>").methods("GET"_method)(GenericAPI<Meat>::readResource);
    CROW_ROUTE(app, "/api/meats/<string>").methods("PUT"_method)(GenericAPI<Meat>::updateResource);
    CROW_ROUTE(app, "/api/meats/<string>").methods("DELETE"_method)(GenericAPI<Meat>::deleteResource);

    // Sauces
    CROW_ROUTE(app, "/api/sauces").methods("POST"_method)(GenericAPI<Sauce>::createResource);
    CROW_ROUTE(app, "/api/sauces").methods("GET"_method)(GenericAPI<Sauce>::readAllResources);
    CROW_ROUTE(app, "/api/sauces/<string>").methods("GET"_method)(GenericAPI<Sauce>::readResource);
    CROW_ROUTE(app, "/api/sauces/<string>").methods("PUT"_method)(GenericAPI<Sauce>::updateResource);
    CROW_ROUTE(app, "/api/sauces/<string>").methods("DELETE"_method)(GenericAPI<Sauce>::deleteResource);

    // Orders
    CROW_ROUTE(app, "/api/orders").methods("POST"_method)(GenericAPI<Order>::createResource);
    CROW_ROUTE(app, "/api/orders").methods("GET"_method)(GenericAPI<Order>::readAllResources);
    CROW_ROUTE(app, "/api/orders/<string>").methods("GET"_method)(GenericAPI<Order>::readResource);
    CROW_ROUTE(app, "/api/orders/<string>").methods("PUT"_method)(GenericAPI<Order>::updateResource);
    CROW_ROUTE(app, "/api/orders/<string>").methods("DELETE"_method)(GenericAPI<Order>::deleteResource);


    // Run the web service app.
    app.port(18888).run();

    saveToFile<Ingredient>(GenericAPI<Ingredient>::resourceMap, "ingredients.json");
    saveToFile<Soda>(GenericAPI<Soda>::resourceMap, "sodas.json");
    saveToFile<Tacos>(GenericAPI<Tacos>::resourceMap, "tacos.json");
    saveToFile<Meat>(GenericAPI<Meat>::resourceMap, "meats.json");
    saveToFile<Sauce>(GenericAPI<Sauce>::resourceMap, "sauces.json");
    saveToFile<Order>(GenericAPI<Order>::resourceMap, "orders.json");
}
#include <crow.h>
#include <map>
#include <string>
#include "Soda.h"
#include "SodaFunctions.h"
#include "Meat.h"
#include "MeatFunctions.h"
#include "Sauce.h"
#include "SauceFunctions.h"

using namespace std;
using namespace crow;

map<string, Soda> sodasMap;
map<string, Meat> meatsMap;
map<string, Sauce> saucesMap;


int main()
{
    sodasMap = loadFromFile("sodas.json");

    SimpleApp app;

    CROW_ROUTE(app, "/api/sodas").methods(HTTPMethod::POST)(createSoda);
    CROW_ROUTE(app, "/api/sodas").methods(HTTPMethod::GET)(readAllSodas);
    CROW_ROUTE(app, "/api/sodas/<string>").methods(HTTPMethod::GET)(readSoda);
    CROW_ROUTE(app, "/api/sodas/<string>").methods(HTTPMethod::PUT)(updateSoda);
    CROW_ROUTE(app, "/api/sodas/<string>").methods(HTTPMethod::DELETE)(deleteSoda);

    return 0;
}


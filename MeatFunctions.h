#ifndef MEAT_FUNCTIONS_H
#define MEAT_FUNCTIONS_H

#include <crow.h>
#include <map>
#include <string>
#include "Meat.h"

// Functions used to handle POST, GET, PUT, and DELETE requests for the Meat resource.
crow::response createMeat(crow::request req);
crow::response readMeat(std::string name);
crow::response readAllMeats(crow::request req);
void updateMeat(crow::request req, crow::response& res, std::string name);
crow::response deleteMeat(std::string name);

void saveMeatsToFile(std::map<std::string, Meat> data, std::string filename);
std::map<std::string, Meat> loadMeatsFromFile(std::string filename);

#endif // MEAT_FUNCTIONS_H
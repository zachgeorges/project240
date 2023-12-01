#ifndef SAUCE_FUNCTIONS_H
#define SAUCE_FUNCTIONS_H

#include <crow.h>
#include <map>
#include <string>
#include "Sauce.h"

// Functions used to handle POST, GET, PUT, and DELETE requests for the Sauce resource.
crow::response createSauce(crow::request req);
crow::response readSauce(std::string name);
crow::response readAllSauces(crow::request req);
void updateSauce(crow::request req, crow::response& res, std::string name);
crow::response deleteSauce(std::string name);

void saveSaucesToFile(std::map<std::string, Sauce> data, std::string filename);
std::map<std::string, Sauce> loadSaucesFromFile(std::string filename);

#endif // SAUCE_FUNCTIONS_H
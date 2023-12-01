#ifndef SODA_FUNCTIONS_H
#define SODA_FUNCTIONS_H

#include <crow.h>
#include <map>
#include <string>
#include "Soda.h"


crow::response createSoda(crow::request req);
crow::response readSoda(std::string size);
crow::response readAllSodas(crow::request req);
void updateSoda(crow::request req, crow::response& res, std::string size);
crow::response deleteSoda(std::string size);

void saveToFile(std::map<std::string, Soda> data, std::string filename);
std::map<std::string, Soda> loadFromFile(std::string filename);

#endif
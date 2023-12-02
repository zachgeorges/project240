#ifndef LOADUPDATE_H
#define LOADUPDATE_H

#include <map>
#include <string>

template <typename T>
void saveToFile(std::map<std::string, T> data, std::string filename);

template <typename T>
std::map<std::string, T> loadFromFile(std::string filename);

#include "LoadUpdate.cpp"

#endif // LOADUPDATE_H
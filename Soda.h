#ifndef SODA_H
#define SODA_H

#include <string>
#include <crow.h>

/**
 * @brief Represents the soda information.
 * 
 * The Soda class holds information about a soda,
 * including its size, type, and whether it is zero-calorie.
 */
class Soda
{
public:
    // Constructor
    Soda() { }
    Soda(crow::json::rvalue readValueJson);
    
    // Size Get/Set
    std::string getSize() { return size; }
    void setSize(std::string sodaSize) { size = sodaSize; }

    // Type Get/Set
    std::string getType() { return type; }
    void setType(std::string sodaType) { type = sodaType; }

    // ZeroCalorie Get/Set
    bool getIsZeroCalorie() { return isZero; }
    void setIsZeroCalorie(bool isZeroCalorie) { isZero = isZeroCalorie; }

    // Convert to JSON
    crow::json::wvalue convertToJson();

    // Update from JSON
    void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string size;
    std::string type;
    bool isZero;
};

#endif // SODA_H

//Might need const keyword for getters 
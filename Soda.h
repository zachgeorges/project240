#ifndef SODA_H
#define SODA_H

#include <string>

/**
 * @brief Represents the soda information.
 * 
 * The Soda class holds information about a soda,
 * including its size, type, and whether it is zero-calorie.
 */
class Soda
{
public:
    Soda() { }
    Soda(std::string sodaSize, std::string sodaType, bool isZeroCalorie)
        : size(sodaSize), type(sodaType), isZero(isZeroCalorie) { }
    
    std::string getSize() { return size; }
    void setSize(std::string sodaSize) { size = sodaSize; }

    std::string getType() { return type; }
    void setType(std::string sodaType) { type = sodaType; }

    bool getIsZeroCalorie() { return isZero; }
    void setIsZeroCalorie(bool isZeroCalorie) { isZero = isZeroCalorie; }

private:
    std::string size;
    std::string type;
    bool isZero;
};

#endif // SODA_H
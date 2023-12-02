#ifndef TACOS_H
#define TACOS_H

#include <crow.h>
#include <string>
#include <vector>
#include <map>
#include "Ingredient.h"

class Tacos
{
public:
    // Constructors
    Tacos() {}
    Tacos(crow::json::rvalue readValueJson);

    // id get/set
    std::string getId() const { return id; }
    void setId(std::string idParam) { id = idParam; }

    // ingredients get/set
    std::vector<Ingredient> getIngredients() const { return ingredients; }
    void setIngredients(std::vector<Ingredient>& ingredientsParam) { ingredients = ingredientsParam; }

    // cost get/set
    float getCost() const { return cost; }
    void setCost(float costParam) { cost = costParam; }

    /* popularity get/set 
    std::string getPopularity(int level) const 
    {
        auto i = popularity.find(level); 
        if (i != popularity.end()) //check if popularity level in the map
        {
            return i->second;
        }
        return "unsure"; // if not return undefined popularity
    }
    void setPopularity(const std::map<int, std::string>& popularityParam) { popularity = popularityParam; }*/
    
    
    

    // Convert to JSON.
    virtual crow::json::wvalue convertToJson();

    // Update from JSON.
    virtual void updateFromJson(crow::json::rvalue readValueJson);

private:
    std::string id;
    std::vector<Ingredient> ingredients;
    float cost;
    std::map<int, std::string> popularity;
    // Initializer for a popularity map 
    void initializePopularityMap();


    /*void Album::initializePopularityMap() {
    popularity[1] = "not popular";
    popularity[2] = "somewhat popular";
    popularity[3] = "popular";
    popularity[4] = "very popular";
    popularity[5] = "most popular";
    
    This will be in the .cpp file*/
};

#endif // TACOS_H
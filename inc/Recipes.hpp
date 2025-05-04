#ifndef HEADER_RECIPE
#define HEADER_RECIPE
#include <string>
#include <vector>
#include <unordered_map>
namespace Resturant
{
class Recipes
{
private:
    size_t idCount_;
    struct Recipe
    {
        size_t id_;
        std::string name_;
        std::unordered_map<std::string, size_t> ingredients_;
    };
    std::unordered_map<size_t, Recipe> galacticCookBook_;
    std::unordered_map<std::string, size_t> recipeLookup_;
public:
    Recipes();
    ~Recipes() = default;

    bool DoWeHaveTheRecipe(std::string recipeName) const;
    std::unordered_map<std::string, size_t> GetIngredientList(std::string recipie);
    bool AddRecipe(std::string recipeName, std::unordered_map<std::string, int> ingredients);
    bool RemoveRecipe(std::string recipeName);
};
}
#endif
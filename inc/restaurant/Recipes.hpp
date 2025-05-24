#ifndef HEADER_RECIPE
#define HEADER_RECIPE
#include <string>
#include <vector>
#include <unordered_map>
namespace restaurant
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

            Recipe(const std::string &name, size_t id, const std::unordered_map<std::string, size_t> &ingredients) : id_(id), name_(name), ingredients_(ingredients)
            {
            }
        };
        std::unordered_map<size_t, Recipe> galacticCookBook_;
        std::unordered_map<std::string, size_t> recipeLookup_;

        const size_t GetId(const std::string &recipeName) const;

    public:
        Recipes();
        ~Recipes() = default;

        bool DoWeHaveTheRecipe(const std::string &recipeName) const;
        const bool GetIngredientList(std::string recipeName, std::unordered_map<std::string, size_t> &ingredientList);
        bool AddRecipe(const std::string &recipeName, const std::unordered_map<std::string, size_t> &ingredients);
        bool RemoveRecipe(const std::string &recipeName);
    };
}
#endif
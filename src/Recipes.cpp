#include "Recipes.hpp"
#include <iostream>

namespace Restaurant
{
    Recipes::Recipes() : idCount_(0)
    {
    }

    bool Recipes::AddRecipe(const std::string &name, const std::unordered_map<std::string, size_t> &ingredients)
    {
        if (DoWeHaveTheRecipe(name))
        {
            std::cerr << "We already have a recipe with same name" << std::endl;
            return false;
        }
        Recipe recipe = Recipe(name, ++idCount_, ingredients);
        galacticCookBook_[idCount_] = recipe;
        recipeLookup_[name] = idCount_;
        return true;
    }

    const size_t Recipes::GetId(const std::string &recipeName) const
    {
        if (recipeLookup_.count(recipeName) > 0)
            return recipeLookup_.at(recipeName);
        return 0;
    }

    bool Recipes::DoWeHaveTheRecipe(const std::string &recipeName) const
    {
        size_t id = GetId(recipeName);
        if (id > 0)
        {
            if (galacticCookBook_.count(id) > 0)
            {
                return true;
            }
        }
        std::cerr << "Recipe not present" << std::endl;
        return false;
    }

    bool Recipes::RemoveRecipe(const std::string &recipeName)
    {
        if (!DoWeHaveTheRecipe(recipeName))
        {
            std::cerr << "Recipe not present" << std::endl;
            return false;
        }
        auto id = recipeLookup_[recipeName];
        recipeLookup_.erase(recipeName);
        galacticCookBook_.erase(id);
        return true;
    }

    const bool Recipes::GetIngredientList(std::string recipeName, std::unordered_map<std::string, size_t> &ingredientList)
    {
        if (!DoWeHaveTheRecipe(recipeName))
        {
            std::cerr << "Recipe not present" << std::endl;
            return false;
        }

        auto id = recipeLookup_[recipeName];
        Recipe recipe = galacticCookBook_[id];
        ingredientList = recipe.ingredients_;

        return true;
    }
}
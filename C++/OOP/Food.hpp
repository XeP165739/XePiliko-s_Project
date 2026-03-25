#include <string>

#ifndef FOOD_HPP
#define FOOD_HPP

#include "Product.hpp"

class Food : public Product
{
    private:
    std::string ingredients;

    public:
    Food(std::string name, std::string productId, double price, double tax, std::string ingredients)
        : Product(name, productId, price, tax)
    {
        this->ingredients = ingredients;
    }

    std::string getIngredients(){
        return ingredients;
    }

    std::string toString() {
        return Product::toString() + " | " + ingredients;
    }
};

#endif

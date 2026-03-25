#include <string>

#ifndef ELECTRONICS_HPP
#define ELECTRONICS_HPP

#include "Product.hpp"

class Electronics: public Product
{
    private:
    std::string waranty;

    public:
    Electronics(std::string name, std::string productId, double price, double tax, std::string waranty)
        : Product(name, productId, price, tax)
    {
        this->waranty = waranty;
    }

    std::string getWaranty(){
        return waranty;
    }

    std::string toString() {
        return Product::toString() + " | " + waranty;
    }
};

#endif

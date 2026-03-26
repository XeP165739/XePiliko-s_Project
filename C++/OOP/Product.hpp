#pragma once

#include <string>

class Product
{
    protected:
    std::string name;
    std::string productId;
    double price;
    double tax;

    public:
    Product(std::string name, std::string productId, double price, double tax);
    virtual ~Product();

    std::string getName();
    std::string getProductId();
    double getPrice();
    double getTax();
    double getTotal();

    virtual std::string toString();
};

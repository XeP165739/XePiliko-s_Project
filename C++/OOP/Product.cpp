#include "Product.hpp"

Product::Product(std::string name, std::string productId, double price, double tax){
    this->name = name;
    this->productId = productId,
    this->price = price;
    this->tax = tax;
}

Product::~Product(){}

std::string Product::getName(){
    return name;
}

std::string Product::getProductId(){
    return productId;
}

double Product::getPrice(){
    return price;
}

double Product::getTax(){
    return tax;
}

double Product::getTotal(){
    return price * (1 + tax);
}

std::string Product::toString(){
    return name + " | " + productId + " | " + std::to_string(price) + " | " + std::to_string(tax);
}

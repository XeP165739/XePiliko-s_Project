#include "Product.hpp"
#include "Food.hpp"
#include "Electronics.hpp"

#include <iostream>
#include <string>
#include <vector>

#ifndef SHELF_HPP
#define SHELF_HPP

class Shelf
{
    private:
    std::vector<Product*> shelf;

    public:
    Shelf(){
        shelf.push_back(new Product("Toothbrush", "1-1234", 15.5, 0.12));
        shelf.push_back(new Product("Toothpaste", "1-1227", 59.99, 0.12));
        shelf.push_back(new Product("Notebook", "1-1475", 19.99, 0.12));
        shelf.push_back(new Product("Pencil", "1-1333", 2.45, 0.12));
        shelf.push_back(new Product("Scented Soap", "1-3327", 20.00, 0.12));
        shelf.push_back(new Food("Potato Chips", "2-3434", 20.12, 0.09, "Potato, Atificial Flavorings(Cheese)"));
        shelf.push_back(new Food("Candy Corn", "2-2112", 5.00, 0.09, "Glucose, Corn Startch"));
        shelf.push_back(new Food("Sour Patch", "2-6788", 6.45, 0.09, "Jelly, Sugar, Ascorbic Acid"));
        shelf.push_back(new Electronics("USB", "3-0934", 199.49, 0.20, "1 year"));
        shelf.push_back(new Electronics("Head Phones", "3-7866", 50.99, 0.20, "1 Month"));
    }

    std::vector<Product*> getShelf(){
        return shelf;
    }

    Product* getItem(std::string productId){
        for (Product* p : shelf) {
            if(p->getProductId().compare(productId) == 0) return p;
        }

        return nullptr;
    }

    void showShelf(){
        for (Product* p : shelf) {
            std::cout << p->toString() << std::endl;
        }
    }

    void clear(){
        for (Product* p : shelf) {
            delete p;
        }
    }
};

#endif

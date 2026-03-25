#include "Customer.hpp"

Customer::Customer(std::string name, std::string id, int age){
        this->name = name;
        this->id = id;
        this->age = age;
    }

std::string Customer::getName(){
        return name;
    }

std::string Customer::getId(){
        return id;
    }

int Customer::getAge(){
        return age;
    }

std::string Customer::toString(){
        return name + " | " + id + " | " + std::to_string(age);
    }
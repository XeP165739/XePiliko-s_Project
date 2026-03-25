#include <iostream>
#include <string>

class Customer 
{
private:
    std::string name;
    std::string id;
    int age;

public:
    Customer(std::string name, std::string id, int age);
    std::string getName();
    std::string getId();
    int getAge();
    std::string toString();
};
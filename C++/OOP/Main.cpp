#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "Shelf.hpp"
#include "Product.hpp"
#include "Electronics.hpp"
#include "Food.hpp"

Shelf shelf = Shelf();

int validInput(){
    std::string rawInput;
    int input = 0;

    std::getline(std::cin, rawInput);

    try {
        input = std::stoi(rawInput);
    } catch (...) {
        input = 0;
    }

    return input;
}

typedef struct Node {
    Product* product;
    int amount;

    struct Node* next;
    struct Node* prev;
} Node;

class Cart
{
    private:
    Node* head = nullptr;
    Node* tail = nullptr;

    public:
    ~Cart() { clear(); } // use basically for memory cashing andmaking sure that creating new instace of cart willhave its own memory

    void addItem(Product* product, int amount){
        Node* temp = head;

        while(temp != nullptr){
            if(temp->product == product) {
                temp->amount +=amount;
                return;
            }
            temp = temp->next;
        }

        Node* newNode = new(std::nothrow) Node; // much safer making of new object instead of malloc

        if (newNode == nullptr){
            std::cerr << "Cannot create new node" << std::endl;
            return;
        }

        newNode->product = product;
        newNode->amount = amount;
        newNode->next = nullptr;

        if(head == nullptr){
            newNode->prev = nullptr;
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        return;
    }

    void showCart(){
        Node* temp = head;

        while(temp != nullptr){
            std::cout << temp->product->getName() << " | " << std::to_string(temp->amount) << std::endl;
            temp = temp->next;
        }
    }

    void clear(){
        while(head != nullptr){
            Node* temp = head;

            head = head->next;
            delete temp;
        }

        tail = nullptr;
    }
};

class Customer {
    private:
    Cart cart;
    double balance;

    public:
    ~Customer() {
        balance = 0;
    };

    void addToCart(Product* product, double amount){
        if (product == nullptr){
            std::cerr << "Product not found | Customer:addToCart(productId, amount)" << std::endl;
            return;
        }

        cart.addItem(product, amount);
        double total = product->getTotal() * amount;
        addBalance(total);
    }

    void showCart(){
        cart.showCart();
    }

    void clearCart(){
        cart.clear();
    }

    void addBalance(double amount){
        this->balance += amount;
    }

    void setBalance(double amount){
        this->balance = 0;
    }

    double getBalance(){
        return balance;
    }
};

class Service
{
    private:
    Customer cus;

    public:
    Service(Customer cus){
        this->cus = cus;
    }

    Product* addItem(std::string productId, int amount){
        Product* p = shelf.getItem(productId);

        if(p == nullptr){
            std::cerr << "Product Id not found" << std::endl;
            return nullptr;
        }

        if(amount <= 0){
            std::cerr << "Amount invalid" << std::endl;
            return nullptr;
        }

        cus.addToCart(p, amount);
        return p;
    }

    double pay(double amount){
        if(cus.getBalance() > amount){
            std::cerr << "Amount insufficient" << std::endl;
            return -1;
        }

        double change = cus.getBalance() - change;
        cus.setBalance(0);

        return change;
    }

    double getBalance(){
        return cus.getBalance();
    }

    void showCart(){
        cus.showCart();
    }

    void clearCart(){
        cus.clearCart();
    }
};

void Buy(){
    Customer cus = Customer();
    Service cs = Service(cus);

    while(true)
    {
        std::cout << "---Main--- \n1: View Shelf \n2: Add Item \n3: View Cart \n4: Pay \n5: Exit \n> ";

        switch (validInput())
        {
        case 1: {
            shelf.showShelf();
            break;
        }

        case 2: {
            std::string id;
            int amount;

            std::cout << "Product Id > ";
            std::getline(std::cin, id);
            std::cout << "Amount > ";
            amount = validInput();

            if(cs.addItem(id, amount) == nullptr){
                std::cerr << "Cannot add to cart" << std::endl;
            }

            break;
        }

        case 3: {
            cs.showCart();
            break;
        }

        case 4: {
            int amount;

            std::cout << "Total Balance: " << std::to_string(cs.getBalance()) << std::endl;
            std::cout << "Amount > ";
            amount = validInput();

            if(cs.pay(amount) == -1){
                std::cerr << "Cannot Pay. Amount insufficient. Please try again" << std::endl;
            } else {
                cs.clearCart();
            }

            break;
        }

        case 5: {
            if(cs.getBalance() ==  0.0){
                return;
            } else {
                std::cerr << "Cannot exit without paying. Balance: " << std::to_string(cs.getBalance()) << std::endl;
            }

            break;
        }

        default:
            std::cerr << "Input Invalid" << std::endl;
        }
    }
}

void Open(){
    while(true)
    {
        std::cout << "---Main--- \n1: Buy \n2: Exit \n> ";
        switch (validInput())
        {
        case 1:
            Buy();
            // shelf.showShelf();
            break;

        case 2:
            return;

        default:
            std::cout << "Input Invalid" << std::endl;
        }
    }
}

int main(){
    Open();

    shelf.clear();
    return 0;
}

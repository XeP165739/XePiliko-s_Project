#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "Shelf.hpp"
#include "Customer.hpp"
#include "Product.hpp"
#include "Electronics.hpp"
#include "Food.hpp"

Shelf shelf = Shelf();

typedef struct Node {
    Product* product;
    int ammount;

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

    void addItem(Product* product, int ammount){
        Node* newNode = new(std::nothrow) Node; // much safer making of new object instead of malloc

        if (newNode == nullptr){
            std::cout << "Cannot create new node" << std::endl;
            return;
        }

        newNode->product = product;
        newNode->ammount = ammount;
        newNode->next = nullptr;

        if(head == nullptr){
            newNode->prev = nullptr;
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void showCart(){
        Node* temp = head;

        while(temp != nullptr){
            std::cout << temp->product->getName() << " | " << std::to_string(temp->ammount) << std::endl;
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

int main(){
    Cart cart;
    Cart cart2;

    cart.addItem(shelf.getItem("1-1234"), 2);
    cart.addItem(shelf.getItem("2-3434"), 5);
    cart.addItem(shelf.getItem("3-0934"), 2);

    cart.showCart();

    cart2.addItem(shelf.getItem("1-1234"), 2);
    cart2.addItem(shelf.getItem("2-3434"), 5);
    cart2.addItem(shelf.getItem("3-0934"), 2);

    cart.clear();

    cart2.showCart();
    shelf.clear();
    return 0;
}

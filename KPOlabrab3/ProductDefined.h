#include <iostream>
#include <string.h>
#include "product.h"

Product::Product() {
    this->name = new char[strlen("")];
    strcpy(this->name, "");
    
    this->code = new char[strlen("")];
    strcpy(this->code, "");
    
    this->quantity = 1;

    std::cout << this->code << " Product::Product()" << "\n";
}
Product::Product(char *name, char *code, int quantity=1) {
    this->name = new char[strlen(name)];
    strcpy(this->name, name);
    
    this->code = new char[strlen(code)];
    strcpy(this->code, code);
    
    this->quantity = quantity;

    std::cout << this->code << " Product::Product(char *name, char *code, int quantity=1)" << "\n";
}
Product::Product(const Product& pr) {
    this->name = new char[strlen(pr.name)];
    strcpy(this->name, pr.name);
    
    this->code = new char[strlen(pr.code)];
    strcpy(this->code, pr.code);
    
    this->quantity = pr.quantity;

    std::cout << this->code << " Product::Product(const Product& pr)" << "\n";
}
Product::~Product() {
    std::cout << this->code << " Product::~Product()" << "\n";
    
    delete this->name;
    delete this->code;
}

void Product::setName(char *name) {
    delete this->name;
    this->name = new char[strlen(name)];
    strcpy(this->name, name);
}
char *Product::getName() {
    return this->name;
}

void Product::setCode(char *code) {
    delete this->code;
    this->code = new char[strlen(code)];
    strcpy(this->code, code);
}
char *Product::getCode() {
    return this->code;
}
    
void Product::setQuantity(int qt) {
    this->quantity = qt;
}
int Product::getQuantity() {
    return this->quantity;
}
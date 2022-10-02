#include <iostream>
#include "ProductDefined.h"

using namespace std;

int main() {
    //указатель на объект
    Product *pr1 = new Product("Gear", "id_1", 10); //вызов конструктора с параметрами
        //Product * - тип указателя
        //pr1 - переменная
        //new Product() - вызывает конструктор
    Product *pr2 = new Product(); //вызов конструктора без параметрами

    cout << pr1->getName() << ' ' << pr1->getCode() << ' ' << pr1->getQuantity() << endl;
    cout << pr2->getName() << ' ' << pr2->getCode() << ' ' << pr2->getQuantity() << endl;

    pr2 = new Product(*pr1); //вызов конструктора копирования
    pr2->setCode("id_2");

    cout << pr1->getName() << ' ' << pr1->getCode() << ' ' << pr1->getQuantity() << endl;
    cout << pr2->getName() << ' ' << pr2->getCode() << ' ' << pr2->getQuantity() << endl;
    
    //pointer - указатель на метод Product::getQuantity
    int (Product::*pointer)();
    pointer = &Product::getQuantity;
    cout << (pr1->*pointer)() << endl;
    
    delete pr1; //вызов деструктора
    delete pr2; //вызов деструктора

    return 0;
}

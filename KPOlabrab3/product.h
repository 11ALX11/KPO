#ifndef PRODUCTH
#define PRODUCTN

//класс Изделие
class Product {

    private:
    
    //Имя
    char *name;
    //Код
    char *code;
    //Количество
    int quantity;

    public:

//Конструкторы
    //без параметров
    Product();
    //с параметрами
    Product(char *name, char *code, int quantity);
    //копирования
    Product(const Product&);

//Деконструктор
    ~Product();

//сеттеры и геттеры
    //для имени
    void setName(char *name);
    char *getName();

    //для кода
    void setCode(char *code);
    char *getCode();
        
    //для количества
    void setQuantity(int qt);
    int getQuantity();
};

#endif
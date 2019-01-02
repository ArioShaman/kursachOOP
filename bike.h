#include <string>
#include <iostream>

using namespace std;

class Bike:public virtual Transport{
    public:
        int rentPrice;//цена аренды за час в у.е.
        string kind;//тип транспортного средства;
        Bike(){
            cout << "Конструктор Auto без парметров";
        }
        Bike(int id, int createYear, string mark ,string color, string number, int mileage, int rentPrice):Transport(id, createYear, mark, color, number, mileage){
            this->rentPrice = rentPrice;
            this->kind = "Мотоцикл";
        }

        friend ostream &operator<<(ostream &output, const Bike &b){

            output << "ID: "<< b.id << "\n";
            output << "Дата создания: "<< b.createYear << "\n";
            output << "Модель: "<< b.mark << "\n";
            output << "Цвет: "<< b.color << "\n";
            output << "номер: "<< b.number << "\n";
            output << "Пробег: "<< b.mileage << "\n";
            output << "Тип транспорта: "<< b.kind << "\n";
            output << "Цена аренды: "<< b.rentPrice << "\n";
            output << "Арендован ли транспорт?: "<< b.isRent << "\n\n";
            return output;
        }     

    void print(){
        cout << this->id << "\n";
        cout << this->createYear << "\n";
        cout << this->mark << "\n";
        cout << this->color << "\n";
        cout << this->number << "\n";
        cout << this->mileage << "\n";

        cout << this->kind << "\n";
        cout << this->rentPrice << "\n";
        cout << "\n";    
    }        


};

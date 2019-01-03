#include <string>
#include <iostream>

using namespace std;

class Bike:public virtual Transport{
    public:
        int rentPrice;//цена аренды за час в у.е.
        string kind;//тип транспортного средства;
        Bike():Transport(){
            this->rentPrice = 0;
            this->kind = "Мотоцикл";
        }
        Bike(int id, int createYear, string mark ,string color, string number, int mileage, int rentPrice):Transport(id, createYear, mark, color, number, mileage){
            this->rentPrice = rentPrice;
            this->kind = "Мотоцикл";
        }


        void setBike(Bike &b){
            this->id = b.id;
            this->createYear = b.createYear; 
            this->mark = b.mark;
            this->color = b.color;
            this->number = b.number;
            this->mileage = b.mileage;
            this->rentPrice = b.rentPrice;
            this->isRent = b.isRent;   
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


};

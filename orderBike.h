#include <string>
#include <iostream>

using namespace std;

class OrderBike:public virtual Order{
    public:
        int startRent;
    OrderBike(int id, int id_transport, int startRent, int durationRent):Order(id,id_transport,durationRent){
        this->startRent = startRent;
    }

    friend ostream &operator<<(ostream &output, const OrderBike &o){
        output << "ID: "<< o.id << "\n";
        output << "bike ID: "<< o.id_transport << "\n";
        output << "Начало аренды(день): "<< o.startRent << "\n";        
        output << "Длительность аренды: "<< o.durationRent << "\n";
        output << "Длительность штрафа: "<< o.durationFine << "\n";
        output << "Заказ закрыт?: "<< o.isClose << "\n";
        cout << "\n";
    }


    void print(){
        cout << this->id << "\n";
        cout << this->startRent << "\n";        
        cout << this->id_transport << "\n";
        cout << this->durationRent << "\n";
        cout << this->durationFine << "\n";
        cout << this->isClose<< "\n";
        cout << "\n";
    }
};
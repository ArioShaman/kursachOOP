#include <string>
#include <iostream>

using namespace std;

class OrderBike:public virtual Order{
    public:

    OrderBike(int id, int id_transport, int durationRent):Order(id,id_transport,durationRent){

    }

    friend ostream &operator<<(ostream &output, const OrderBike &o){
        output << "ID: "<< o.id << "\n";
        output << "Auto ID: "<< o.id_transport << "\n";
        output << "Длительность аренды: "<< o.durationRent << "\n";
        output << "Длительность штрафа: "<< o.durationFine << "\n";
        output << "Заказ закрыт?: "<< o.isClose << "\n";
        cout << "\n";
    }


    void print(){
        cout << this->id << "\n";
        cout << this->id_transport << "\n";
        cout << this->durationRent << "\n";
        cout << this->durationFine << "\n";
        cout << this->isClose<< "\n";
        cout << "\n";
    }
};
#include <string>
#include <iostream>

using namespace std;

class OrderBike:public virtual Order{
    public:

    OrderBike(int id, int id_transport, int durationRent):Order(id,id_transport,durationRent){

    }

    void print(){
        cout << this->id << "\n";
        cout << this->id_transport << "\n";
        cout << this->durationRent << "\n";
        cout << this->durationFine << "\n";
        cout << this->isCose<< "\n";
        cout << "\n";
    }
};
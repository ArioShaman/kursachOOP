#include <string>
#include <iostream>

#include "transport.h"
#include "order.h"


#include "bike.h"
#include "auto.h"

#include "orderAuto.h"
#include "orderBike.h"

#include <fstream>
#include <stack> 


#include <ctime>
#include <cstdlib>

using namespace std;


//Чтение данных с файла
void readDataFromFile(stack <Auto> &autoStack, stack <Bike> &bikeStack){
    ifstream file("./database.txt");

    if(!file) {
        cout << "Cannot open input file.\n";
    }    


    string s;
    while (getline(file, s)) {
        int id; 
        int year;
        string mark;
        string color;
        string number;
        int mileage;        
        int rentPrice;
        string kind;        

        string delimiter = ",";
        size_t pos = 0;
        string token;
        int index = 0;

        while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);

            switch(index){
                case 0:
                    id = stoi(token);
                    break;
                case 1:
                    year = stoi(token);
                    break;
                case 2:
                    mark = token;
                    break;
                case 3:
                    color = token;
                    break;
                case 4:
                    number = token;
                    break;
                case 5:
                    mileage = stoi(token);
                    break;
                case 6:
                    rentPrice = stoi(token);
                    break;
                case 7:
                    kind = token;
                    break;                                                                                                                                            
                default:
                    break;
            }

            s.erase(0, pos + delimiter.length());
            index++;
        }
    
        if (kind == "auto"){
            Auto a(id, year, mark, color, number, mileage, rentPrice);   
            autoStack.push(a);
        }
        if(kind == "bike"){
            Bike b(id, year, mark, color, number, mileage, rentPrice);
            bikeStack.push(b);
        }
    } 
}

void rentAuto(int orderId, int curDay, stack <Auto> &autoStack, stack <OrderAuto> &autoOrders){
    if(autoStack.empty()){
        cout << "Стек пуст";
    }

    stack <Auto> notRentedAutoStack;
    stack <Auto> rentedAutoStack;

    bool isRent = false;

    while(!autoStack.empty()){

        //здесь производить заказ и проверку на то, арендован ли транспорт
        if(!autoStack.top().isRented()){//проверка на арендован ли автомобиль
        
            int isChanged = 1+rand()%(10-1);
            if(isChanged <= 5){
                autoStack.top().rent();
                isRent = true;
                int durationRent = 1+rand()%(8-1);
                OrderAuto oa(orderId, autoStack.top().id, curDay, durationRent);
                autoOrders.push(oa);
                cout << autoStack.top() << "\n";
                break;
            }

            notRentedAutoStack.push(autoStack.top());
            autoStack.pop();
        }else{
            rentedAutoStack.push(autoStack.top());
            autoStack.pop();
        }


    }

    //проверка на наличие средства для проката
    if(!isRent and autoStack.empty() and notRentedAutoStack.empty()){
        cout << "Автомобили на прокат закончились, поэтому клиент ушел до следующего раза\n";
    }


    while(!rentedAutoStack.empty()){
        autoStack.push(rentedAutoStack.top());
        rentedAutoStack.pop();
    }

    while(!notRentedAutoStack.empty()){
        autoStack.push(notRentedAutoStack.top());
        notRentedAutoStack.pop();
    }

}

void rentBike(int orderId, stack <Bike> &bikeStack, stack <OrderBike> &bikeOrders){
    if(bikeStack.empty()){
        cout << "Стек пуст";
    }

    stack <Bike> notRentedBikeStack;
    stack <Bike> rentedBikeStack;

    bool isRent = false;

    while(!bikeStack.empty()){

        //здесь производить заказ и проверку на то, арендован ли транспорт
        if(!bikeStack.top().isRented()){//проверка на арендован ли автомобиль
        
            int isChanged = 1+rand()%(10-1);
            if(isChanged <= 5){
                bikeStack.top().rent();
                isRent = true;
                int durationRent = 1+rand()%(8-1);
                OrderBike ob(orderId, bikeStack.top().id, durationRent);
                bikeOrders.push(ob);
                cout << bikeStack.top() << "\n";
                break;
            }

            notRentedBikeStack.push(bikeStack.top());
            bikeStack.pop();
        }else{
            rentedBikeStack.push(bikeStack.top());
            bikeStack.pop();
        }


    }

    //проверка на наличие средства для проката
    if(!isRent and bikeStack.empty() and notRentedBikeStack.empty()){
        cout << "Мотоциклы на прокат закончились, поэтому клиент ушел до следующего раза\n";
    }


    while(!rentedBikeStack.empty()){
        bikeStack.push(rentedBikeStack.top());
        rentedBikeStack.pop();
    }

    while(!notRentedBikeStack.empty()){
        bikeStack.push(notRentedBikeStack.top());
        notRentedBikeStack.pop();
    }
}



int main(){
    srand(time(NULL));

    stack <OrderAuto> autoOrders;// стек для учета текущих арендованных автомобилей
    stack <OrderBike> bikeOrders;// стек для учета текущих арендованных мотоциклов

    stack <OrderAuto> finishedAutoOrders;// стек для учета завершенных сделок по аренде автомобилей
    stack <OrderBike> finishedBikeOrders;// стек для учета завершенных сделок по аренде мотоциклов

    stack <Auto> autoStack;//стек для хранения данных об автомобилях
    stack <Bike> bikeStack;//стек для хранения данных о мотоциклах
    readDataFromFile(autoStack, bikeStack);
    
    
    int orderId = 0;


    for(int curDay = 1; curDay <= 20; curDay++){
        cout << "Текущий день:   "<< curDay << "\n";

        int countCustomers;
        countCustomers=1+rand()%(5-1);
        // cout<< countCustomers << "\n";
        for(int curCustomer = 1; curCustomer <= countCustomers; curCustomer++){
            orderId++;

            cout << "Customer:  " << orderId << "\n";
            int boolKindTransport = 0+rand()%(3-1);
            

            // rentAuto(orderId, curDay, autoStack, autoOrders);

            string curTransport;
            if(boolKindTransport == 1){
                curTransport = "auto";
                rentAuto(orderId, curDay, autoStack, autoOrders);

            }else{
                curTransport = "bike";
                rentBike(orderId, bikeStack, bikeOrders);
            }

        }
        //симуляция процесса возврата средства
        // while(!autoOrders.empty()){

        // }
    }


    return 0;
}
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

void rentAuto(stack <Auto> &autoStack){
    if(autoStack.empty()){
        cout << "Стек пуст";
    }

    stack <Auto> bufferAutoStack;
    while(!autoStack.empty()){
        int isChanged = 1+rand()%(10-1);
        if(isChanged <= 5){
            cout << autoStack.top();
            //здесь производить заказ и проверку на то, арендован ли транспорт
            break;
        }
        bufferAutoStack.push(autoStack.top());
        autoStack.pop();
    }

    while(!bufferAutoStack.empty()){
        autoStack.push(bufferAutoStack.top());
        bufferAutoStack.pop();
    }
}

void rentBike(stack <Bike> &bikeStack){
    if(bikeStack.empty()){
        cout << "Стек пуст";
    }

    stack <Bike> bufferBikeStack;
    while(!bikeStack.empty()){
        int isChanged = 1+rand()%(10-1);
        if(isChanged <= 5){
            cout << bikeStack.top();
            //здесь производить заказ и проверку на то, арендован ли транспорт
            break;
        }
        bufferBikeStack.push(bikeStack.top());
        bikeStack.pop();
    }

    while(!bufferBikeStack.empty()){
        bikeStack.push(bufferBikeStack.top());
        bufferBikeStack.pop();
    }
}



int main(){
    srand(time(NULL));
    // OrderAuto oa(1,1, 3, 10);
    // cout << oa;

    // OrderBike ob(1,2,6);
    // cout << ob;

    stack <Auto> autoStack;
    stack <Bike> bikeStack;
    readDataFromFile(autoStack, bikeStack);
    

    int orderId = 0;

    // for(int curDay = 1; curDay <= 3; curDay++){
    //     cout << "Текущий день:   "<< curDay << "\n";

    //     int countCustomers;
    //     countCustomers=1+rand()%(5-1);
    //     // cout<< countCustomers << "\n";
    //     for(int curCustomer = 1; curCustomer <= countCustomers; curCustomer++){
    //         cout << "Customer:  " << curCustomer << "\n";
    //         int boolKindTransport = 0+rand()%(3-1);
            
    //         string curTransport;
    //         if(boolKindTransport == 1){
    //             curTransport = "auto";
    //         }else{
    //             curTransport = "bike";
    //         }

    //     }
    // }


    return 0;
}
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


Auto getAutoById(stack <Auto> &autoStack, int id){
    stack <Auto> bufferedAutoStack;
    Auto a;
    while(!autoStack.empty()){
        if(autoStack.top().id == id){
            a.setAuto(autoStack.top());
        }
        else{
            bufferedAutoStack.push(autoStack.top());
            
        }
        autoStack.pop();

    }
    while(!bufferedAutoStack.empty()){
        autoStack.push(bufferedAutoStack.top());
        bufferedAutoStack.pop();
    }

    return a;
}

void rentAuto(int orderId, int curDay, stack <Auto> &autoStack, stack <OrderAuto> &autoOrders){
    if(autoStack.empty()){
        cout << "Стек пуст \n";
    }

    stack <Auto> bufferAutoStack;

    bool isRent = false;

    while(!autoStack.empty()){

        //здесь производить заказ и проверку на то, арендован ли транспорт
        if(!autoStack.top().isRented()){//проверка на арендован ли автомобиль
        
            int isChanged = 1+rand()%(10-1);
            if(isChanged <= 5){
                Auto a(getAutoById(autoStack, autoStack.top().id));
                a.rent();

                isRent = true;
                int durationRent = 1+rand()%(5-1);
                OrderAuto oa(orderId, a.id, curDay, durationRent);
                autoOrders.push(oa);

                autoStack.push(a);
                // cout << a << "\n";

                std::ofstream out("./otchet.txt", std::ios::app);
                if (out.is_open()){
                    out << "Арендован автомобиль:   " << a.mark << " , номер: " << a.number << "\n\n";
                }                
                out.close();

                break;
            }else{
                bufferAutoStack.push(autoStack.top());
                autoStack.pop();
            }
        }else{
            bufferAutoStack.push(autoStack.top());
            autoStack.pop();
        }
    }

    //проверка на наличие средства для проката
    if(!isRent and autoStack.empty()){
        std::ofstream out("./otchet.txt", std::ios::app);
        out << "Автомобили на прокат закончились, поэтому клиент ушел до следующего раза\n";
        out.close();
    }


    while(!bufferAutoStack.empty()){
        autoStack.push(bufferAutoStack.top());
        bufferAutoStack.pop();
    }

}

Bike getBikeById(stack <Bike> &bikeStack, int id){
    stack <Bike> bufferedBikeStack;
    Bike b;
    while(!bikeStack.empty()){
        if(bikeStack.top().id == id){
            b.setBike(bikeStack.top());
        }
        else{
            bufferedBikeStack.push(bikeStack.top());
            
        }
        bikeStack.pop();

    }
    while(!bufferedBikeStack.empty()){
        bikeStack.push(bufferedBikeStack.top());
        bufferedBikeStack.pop();
    }

    return b;
}

void rentBike(int orderId, int curDay, stack <Bike> &bikeStack, stack <OrderBike> &bikeOrders){
    if(bikeStack.empty()){
        cout << "Стек пуст \n";
    }

    stack <Bike> bufferBikeStack;

    bool isRent = false;

    while(!bikeStack.empty()){

        //здесь производить заказ и проверку на то, арендован ли транспорт
        if(!bikeStack.top().isRented()){//проверка на арендован ли мотоцикл
        
            int isChanged = 1+rand()%(10-1);
            if(isChanged <= 5){
                Bike b(getBikeById(bikeStack, bikeStack.top().id));
                b.rent();
                isRent = true;
                int durationRent = 1+rand()%(8-1);
                OrderBike ob(orderId, b.id, curDay, durationRent);
                
                bikeOrders.push(ob);

                std::ofstream out("./otchet.txt", std::ios::app);
  
                out << "Арендован мотоцикл:   " << b.mark << " , номер: " << b.number << "\n\n";
                                
                out.close();
                bikeStack.push(b);
                break;
            }
            bufferBikeStack.push(bikeStack.top());
            bikeStack.pop();
        }else{
            bufferBikeStack.push(bikeStack.top());
            bikeStack.pop();
        }


    }

    while(!bufferBikeStack.empty()){
        bikeStack.push(bufferBikeStack.top());
        bufferBikeStack.pop();
    }

}


int checkProfit(stack <OrderAuto> &finishedAutoOrders, stack <OrderBike> &finishedBikeOrders, stack <Auto> &autoStack, stack <Bike> &bikeStack){
    stack <OrderAuto> buferFinishedAutoOrders;
    stack <OrderBike> bufferFinishedBikeOrders;

    int autoProfit = 0;
    int bikeProfit = 0;



    while(!finishedAutoOrders.empty()){
        OrderAuto oa(finishedAutoOrders.top()) ;

        Auto a(getAutoById(autoStack, finishedAutoOrders.top().id_transport)); 

        int curProfit = a.rentPrice * oa.durationRent + a.rentPrice*2*oa.durationFine;

        autoProfit += curProfit;
        
        autoStack.push(a);
        buferFinishedAutoOrders.push(finishedAutoOrders.top());
        finishedAutoOrders.pop();
    }
    while(!buferFinishedAutoOrders.empty()){
        finishedAutoOrders.push(buferFinishedAutoOrders.top());
        buferFinishedAutoOrders.pop();
    }


    while(!finishedBikeOrders.empty()){
        OrderBike ob(finishedBikeOrders.top()) ;

        Bike b(getBikeById(bikeStack, finishedBikeOrders.top().id_transport)); 

        int curProfit = b.rentPrice * ob.durationRent + b.rentPrice*2*ob.durationFine;

        bikeProfit += curProfit;
        
        bikeStack.push(b);        
        bufferFinishedBikeOrders.push(finishedBikeOrders.top());
        finishedBikeOrders.pop();
    }

    while(!bufferFinishedBikeOrders.empty()){
        finishedBikeOrders.push(bufferFinishedBikeOrders.top());
        bufferFinishedBikeOrders.pop();
    }    
    return autoProfit + bikeProfit;
}
//Определить сколько раз были сданы в прокат транспортные средства в указанный период времени по каждому виду (автомобиль, мотоцикл).
void checkRentedTransport(int startDay, int finishDay, stack <OrderAuto> &autoOrders, stack <OrderAuto> &finishedAutoOrders, stack <OrderBike> &finishedBikeOrders){
    int bikeCount = 0;
    int autoCount = 0;

    stack <OrderAuto> bufferAutoOrders;
    stack <OrderAuto> buferFinishedAutoOrders;
    stack <OrderBike> bufferFinishedBikeOrders;

    //незакрытые сделки по аренде автомобилей
    while(!autoOrders.empty()){
        if((autoOrders.top().startRent >= startDay) and (autoOrders.top().startRent <= finishDay) ){
            autoCount++;
        }
        bufferAutoOrders.push(autoOrders.top());
        autoOrders.pop();
    }
    while(!bufferAutoOrders.empty()){
        autoOrders.push(bufferAutoOrders.top());
        bufferAutoOrders.pop();
    }

    //закрытые сделки по аренде автомобилей
    while(!finishedAutoOrders.empty()){
        if((finishedAutoOrders.top().startRent >= startDay) and (finishedAutoOrders.top().startRent <= finishDay) ){
            autoCount++;
        }        
        buferFinishedAutoOrders.push(finishedAutoOrders.top());
        finishedAutoOrders.pop();
    }
    while(!buferFinishedAutoOrders.empty()){
        finishedAutoOrders.push(buferFinishedAutoOrders.top());
        buferFinishedAutoOrders.pop();
    }

    //сделки по аренде мотоциклов
    while(!finishedBikeOrders.empty()){
        if((finishedBikeOrders.top().startRent >= startDay) and (finishedBikeOrders.top().startRent <= finishDay) ){
            bikeCount++;
        }    
        bufferFinishedBikeOrders.push(finishedBikeOrders.top());
        finishedBikeOrders.pop();
    }
    while(!bufferFinishedBikeOrders.empty()){
        finishedBikeOrders.push(bufferFinishedBikeOrders.top());
        bufferFinishedBikeOrders.pop();
    }

    std::ofstream out("./otchet.txt", std::ios::app);
    out << "Кол-во операций по аренде автомобилей: с " << startDay << " по " << finishDay << " число: " << autoCount << "\n";
    out << "Кол-во операций по аренде мотоциклов:  с " << startDay << " по " << finishDay << " число: " << bikeCount << "\n";
    out.close();
}

void checkMaxMileage(stack <Auto> &autoStack, stack <Bike> &bikeStack){
    stack <Auto> bufferAutoStack;
    stack <Bike> bufferBikeStack;

    int maxMileage = 0;
    string maxType = "auto";
    int maxIdTransport = 1; 

    while(!autoStack.empty()){
        if(autoStack.top().mileage > maxMileage){
            maxMileage = autoStack.top().mileage;
            maxIdTransport = autoStack.top().id;    
        }
        bufferAutoStack.push(autoStack.top());
        autoStack.pop();
    }
    while(!bufferAutoStack.empty()){
        autoStack.push(bufferAutoStack.top());
        bufferAutoStack.pop();
    }

    while(!bikeStack.empty()){

        if(bikeStack.top().mileage > maxMileage){
            maxType = "bike";
            maxMileage = bikeStack.top().mileage;
            maxIdTransport = bikeStack.top().id; 
        }
        bufferBikeStack.push(bikeStack.top());
        bikeStack.pop();
    }
    while(!bufferBikeStack.empty()){
        bikeStack.push(bufferBikeStack.top());
        bufferBikeStack.pop();
    }



    std::ofstream out("./otchet.txt", std::ios::app);
    
    out << "Транспорт с максимальным пробегом: \n";
        
    if(maxType == "auto"){
        Auto a(getAutoById(autoStack, maxIdTransport));
        out << a << "\n";
        autoStack.push(a);
    }else{
        Bike b(getBikeById(bikeStack, maxIdTransport));
        out << b << "\n";
        bikeStack.push(b);
    }
    out << "Пробег:  " << maxMileage << "\n";
    out.close(); 

}

int main(){
    srand(time(NULL));

    stack <OrderAuto> autoOrders;
    // стек для учета текущих арендованных автомобилей
    stack <OrderBike> bikeOrders;
    // стек для учета текущих арендованных мотоциклов

    stack <OrderAuto> bufferAutoOrders;
    // буферный стек для учета текущих арендованных автомобилей


    stack <OrderAuto> finishedAutoOrders;
    // стек для учета завершенных сделок по аренде автомобилей
    stack <OrderBike> finishedBikeOrders;
    // стек для учета завершенных сделок по аренде мотоциклов

    stack <Auto> autoStack;
    //стек для хранения данных об автомобилях
    stack <Bike> bikeStack;
    //стек для хранения данных о мотоциклах

    stack <Auto> bufferAutoStack;
    //буферный стек для хранения данных об автомобилях
    stack <Bike> bufferBikeStack;
    //буферный стек для хранения данных о мотоциклах    
    readDataFromFile(autoStack, bikeStack);
    
    
    int orderId = 0;


    



    for(int curDay = 1; curDay <= 30; curDay++){
        // cout << "Текущий день:   "<< curDay << "\n";
     
        std::ofstream out("./otchet.txt", std::ios::app);
        if (out.is_open()){
            out << "                           Текущий день:   " << curDay << "\n\n";
        }
        out.close(); 

        int countCustomers;
        countCustomers=1+rand()%(5-1);
        // countCustomers = 1;
        for(int curCustomer = 1; curCustomer <= countCustomers; curCustomer++){
            orderId++;

            // cout << "Customer:  " << orderId << "\n";
            
            std::ofstream out("./otchet.txt", std::ios::app);
            if (out.is_open()){
                out << "Id Покупателя:   " << orderId << "\n\n";
            }
            out.close(); 


            int boolKindTransport = 0+rand()%(3-1);
            

            

            string curTransport;

            if(boolKindTransport == 1){
                curTransport = "auto";
                rentAuto(orderId, curDay, autoStack, autoOrders);

            }else{
                curTransport = "bike";
                rentBike(orderId, curDay, bikeStack, bikeOrders);
            }

        }
        //симуляция процесса возврата автомобиля
        
        while(!autoOrders.empty()){
            OrderAuto oa(autoOrders.top());
            
            Auto a(getAutoById(autoStack, oa.id_transport));
            //проверка на то, истекла ли дата аренды  
            if(oa.isExpireRent(curDay)){
                // если истекла, то проверить вернул ли арендатель автомобиль
                bool inTime = 0+rand()%(3-1);
                if(!inTime){
                    // если не вернул то добавить штрафной час и идти дальше
                    oa.addFine(1);
                    
                    int mileage = 0+rand()%(300-1);

                    a.addMileage(mileage);

                    bufferAutoOrders.push(oa);
                }else{
                    //если вернул то разарендовать автомобиль и завершить заказ
                    a.unrent();

                    std::ofstream out("./otchet.txt", std::ios::app);
                    if (out.is_open()){
                        out << "Возвращен автомобиль :   " << a.mark << " , номер: " << a.number << "\n";
                        out << "Аренда длилась: " << oa.durationRent << " дней \n";
                        out << "Штрафное фремя: " << oa.durationFine << "\n";
                        out << "Пробег: " << a.mileage << " км\n\n";
                    }   
                    out.close();                    
                    
                    oa.close();
                    finishedAutoOrders.push(oa);
                }      
            
            }else{
                //если не истекла то пропустить
                bufferAutoOrders.push(oa);
            }
            autoStack.push(a);
            autoOrders.pop();


        }
        while(!bufferAutoOrders.empty()){
            autoOrders.push(bufferAutoOrders.top());
            bufferAutoOrders.pop();
        }
        

        //симуляция процесса возврата мотоцикла
        while(!bikeOrders.empty()){
            std::ofstream out("./otchet.txt", std::ios::app);

            OrderBike ob(bikeOrders.top());
            Bike b(getBikeById(bikeStack, ob.id_transport));


            int mileage = 0+rand()%(300-1);
            b.addMileage(mileage);                
            out << "Возвращен мотоцикл :   " << b.mark << " , номер: " << b.number << "\n";
            b.unrent();


            
            //рандом определяет сдан вовремя мотоцикл
            bool inTime = 0+rand()%(3-1);
            if(!inTime){
                //если не сдан, то определяется на рандоме проштрафленное время и помещается в завершенные заказы
                int fine = 1+rand()%(10-1);

                ob.addFine(fine);
            }
            out << "Аренда длилась: " << ob.durationRent << " часов \n";
            out << "Штрафное время: " << ob.durationFine << " часов \n";
            out << "Пробег: " << b.mileage << " км\n\n";

            //сдан/не сдан - поместить заказ в завершенные
            //предполагается, что арендатель возвратил мотоцикл после проштрафленного времени
            bikeStack.push(b);
            ob.close();
            finishedBikeOrders.push(ob);

            bikeOrders.pop();
            out.close(); 
        }

    }

    checkRentedTransport(1, 30, autoOrders, finishedAutoOrders, finishedBikeOrders);   
    
    std::ofstream out("./otchet.txt", std::ios::app);
    if (out.is_open()){
        out << "Месячная прибыль автосалона по завершенным сделкам:   " << checkProfit(finishedAutoOrders, finishedBikeOrders, autoStack, bikeStack) << " у.е.\n";
    }   
    out.close(); 

    return 0;


}
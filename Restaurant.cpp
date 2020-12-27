// ==========================================================================
//
//                   Restaurant.cpp
//
// ==========================================================================

#include <iostream>
#include <stdexcept>
#include <list>
#include <queue>
#include <deque>
#include "Time.h"
#include "Order.h"
#include "Driver.h"
#include "Restaurant.h"
using namespace std;

Restaurant::Restaurant() {

    deque<Order>cookQueue;
    cooking = cookQueue;

    deque<Order>departQueue;
    departure = departQueue;

    vector<Driver>driverQueue;
    driver = driverQueue;

    totalMinForOrders = 0;
    numOfOrdersComplete = 0;
}

void Restaurant::status() {
    //
    cout << "Orders waiting to cook:" << endl;

    if (!cooking.empty()) {

        for (int i = 0; i < cooking.size(); i++) {
            cout << '\t' << cooking[i].toString() << endl;
        }

    }

    cout << "Orders waiting to depart:" << endl;
    if (!departure.empty()) {

        for (int i = 0; i < departure.size(); i++) {
            cout << '\t' << departure[i].toString() << endl;
        }
    }

    cout << "Drivers: " << endl;
    if (!driver.empty()) {

        for (vector<Driver>::iterator itr = driver.begin(); itr != driver.end(); itr++) {
            cout << '\t' << itr->toString() << endl;
        }
    }

}

void Restaurant::summary() {

    cout << "Summary: " << endl;

    cout << "Number of Orders completed: " << numOfOrdersComplete << endl;

    if (totalMinForOrders == 0 || numOfOrdersComplete == 0) {
        cout << "Average time per order: 0" << endl;
    }
    else {
        cout << "Average time per order: " << ((double)(totalMinForOrders) / (double)(numOfOrdersComplete)) << endl;
    }

    for (int i = 0; i < driver.size(); i++) {

        cout << "Driver " << driver[i].getName() << endl;

        cout << "\tNumber of deliveries completed: " << driver[i].getTotalDeliveries() << endl;

        cout << "\tAverage time per delivery: ";

        int totalMinDelivering = driver[i].getTotalMinDelivering();
        int totalDeliveries = driver[i].getTotalDeliveries();

        if (totalMinDelivering == 0 || totalDeliveries == 0) {
            cout << "0" << endl;
        }
        else {
            cout << (totalMinDelivering) / (totalDeliveries) << endl;
        }

        cout << "\tTotal driving time: " << driver[i].getTotalMinDriving() << endl;

        cout << "\tTotal tips: " << driver[i].getTotalTips() << endl;

    }

}

Driver * Restaurant::getDriver(string name) {

    int check = 0;
    int found = 0;

    if (!driver.empty()) {

        auto foundDriver = driver.begin();
        for (vector<Driver>::iterator itr = driver.begin(); itr != driver.end(); itr++) {

            string nameToCompare = itr->toString();

            if (nameToCompare.find(name) != string::npos) {
                check = 1;
                return &(driver[found]);
            }

            found++;
        }
    }

    if (check == 0) {
        return nullptr;
    }
}

void Restaurant::addDriver(Driver *drivers) {

    Driver test = *drivers;
    driver.push_back(test);

}

void Restaurant::addOrder(Order *order) {

    Order testCook = *order;
    cooking.emplace_back(testCook);

}

void Restaurant::serveNextOrder() throw (logic_error) {

    if (cooking.empty()) {
        throw logic_error ("The cooking queue is empty.");
    }

    else {
        Order cooked = cooking.front();
        cooking.pop_front();
        departure.emplace_back(cooked);
    }
}

Order * Restaurant::departNextOrder() throw (logic_error) {

    if (departure.empty()) {
        throw logic_error ("The departure queue is empty.");
    }

    else {

        departureFront = &departure.front();
        departure.pop_front();
        return departureFront;
    }
}

// The order carried by the driver is delivered at the given time. The driver receives the given tip.
void Restaurant::deliver(Driver * driver, Time time, float tip) {

    Order orderToDeliver = departure.front();

    driver->depart(orderToDeliver.getOrderPlacedTime(), orderToDeliver);

    driver->deliver(time,tip);

}

void Restaurant::orderCompleted() {
    numOfOrdersComplete++;
}

void Restaurant::setStartTime(Time time) {
    orderStartTime = time;
}

void Restaurant::setEndTime(Time time) {
    deliverEndTime = time;
}

void Restaurant::setTotalMinutes(Driver * driver) {
    totalMinForOrders += driver->getTotalOrderTime();
}
// ==========================================================================
//
//                   Restaurant.h
//
// ==========================================================================

#ifndef FINALPROJECT_RESTAURANT_H
#define FINALPROJECT_RESTAURANT_H

#include <iostream>
#include <stdexcept>
#include <list>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include "Time.h"
#include "Order.h"
#include "Driver.h"

using namespace std;

class Restaurant {

public:

    // Creates a Restaurant class.
    // Pre: none
    // Post: A Restaurant class with no drivers or orders is created.
    Restaurant();

    // Displays the status of orders.
    // Pre: none
    // Post: The status of all the orders till then is printed.
    void status();

    // Displays the summary of the orders and drivers. Everything that was logged in the system is displayed
    // Pre: none
    // Post: The summary of the orders and drivers is printed.
    void summary();

    // Returns a pointers to the driver, if the driver exists. Returns a null pointer otherwise.
    // Pre: none
    // Post: Pointer to the driver is returned, if the driver exists within the system. Null otherwise.
    Driver * getDriver(string name);

    // Adds the driver to the system
    // Pre: none
    // Post: The driver is added to the system.
    void addDriver(Driver *drivers);

    // Enqueues the order to the system
    // Pre: none
    // Post: The order in enqueued in the system.
    void addOrder(Order *order);

    // Removes the oldest order and enqueues to the departure queue.
    // Pre: !cooking.empty(), the cooking queue is not empty.
    // Post: The oldest order is removed from the cooking queue and enqueued in the departure queue.
    void serveNextOrder() throw (logic_error);

    // Removes the oldest order from the departure queue and returns it.
    // Pre: !departure.empty(), the departure queue is not empty.
    // Post: The oldest order is removed from the departure queue and returned.
    Order * departNextOrder() throw (logic_error);

    // The driver delivers the order at the respective time and receives the respective tip.
    // Pre: none
    // Post: The driver's name, time he delivered the order and his tip is recorded.
    void deliver(Driver * driver, Time time, float tip);    // <-- Unused function, but keep it

    // Records the number of orders completed.
    // Pre: none
    // Post: The number of orders completed is recorded.
    void orderCompleted();

    // Notes the time of the order.
    // Pre: none
    // Post: The time of the order is noted.
    void setStartTime(Time time);

    // Notes the time of the delivery of the order.
    // Pre: none
    // Post: The time of order's delivery is noted.
    void setEndTime(Time time);

    // Gives the total time in minutes for an order.
    // Pre: none
    // Post: The total time in minutes for an order is noted.
    void setTotalMinutes(Driver * driver);


private:

    int numOfOrdersComplete,
        totalMinForOrders;

    deque<Order>cooking,
            departure;

    Order * departureFront{};

    Time orderStartTime,
         deliverEndTime;

    vector<Driver>driver;

};

#endif //FINALPROJECT_RESTAURANT_H

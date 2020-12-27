// ==========================================================================
//
//                    Order.h
//
// ==========================================================================

#ifndef FINALPROJECT_ORDER_H
#define FINALPROJECT_ORDER_H

#include <iostream>
#include <stdexcept>
#include "Time.h"
using namespace std;

class Order {

public:

    // Default Constructor
    // Creates an order class.
    // Pre: none
    // Post: Order class is created.
    Order();

    // Parameterized Constructor
    // Creates an order class with parameters.
    // Pre: none
    // Post: Order class is created with given order time and info.
    Order(Time time, string info);

    // Check if the order is out for delivery.
    // Pre: Order is at the restaurant.
    // Post: Order is out for delivery.
    void depart() throw (logic_error);  // <-- Unused function, but keep it

    // Check if the order is delivered or not.
    // Pre: Order is out for delivery.
    // Post: Order is delivered and time is noted.
    void deliver(Time time) throw (logic_error);    // <-- Unused function, but keep it

    // Returns the minutes until the order is delivered
    // Pre: Order is delivered.
    // Post: Order time - deliver time is returned.
    int getMinToDelivery() throw (logic_error);     // <-- Unused function, but keep it

    // Returns the time when order was placed
    // Pre: none
    // Post: Time when order was placed is returned.
    Time getOrderPlacedTime() const;

    // Returns the time when order was delivered
    // Pre: none
    // Post: Time when order was delivered is returned.
    Time getOrderDeliveredTime() const;     // <-- Unused function, but keep it

    // Returns a string containing the order time and info.
    // Pre: none
    // Post: A string containing order time and info is returned.
    string toString();



private:

    Time orderPlaced;
    Time orderDelivered;
    string orderInfo;
    int minToDelivery;

    bool departed;
    bool delivered;
};

#endif //FINALPROJECT_ORDER_H

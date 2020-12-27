// ==========================================================================
//
//                     Order.cpp
//
// ==========================================================================

#include <iostream>
#include "Order.h"
using namespace std;

Order::Order() {
    orderPlaced = Time();
    orderDelivered = Time();
    orderInfo = "";
    minToDelivery = 0;
    departed = false;
    delivered = false;
}

Order::Order(Time time, string info) {
    orderPlaced = time;
    orderDelivered = Time();
    orderInfo = info;
    minToDelivery = 0;
    departed = false;
    delivered = false;
}

void Order::depart() throw (logic_error) {
    if (orderPlaced.toString() == "00:00" || orderInfo.empty()) {
        throw logic_error("Error: Please create an order first.");
    }

    departed = true;
}

void Order::deliver(Time time) throw (logic_error) {
    if (!departed) {
        throw logic_error("Error: Cannot deliver when driver has not departed.");
    }

    orderDelivered = time;
    delivered = true;
}

int Order::getMinToDelivery() throw (logic_error) {
    if (!delivered) {
        throw logic_error("Error: Driver has not delivered order yet.");
    }

    minToDelivery = Time::elapsedMin(orderPlaced, orderDelivered);
    return minToDelivery;
}

Time Order::getOrderPlacedTime() const {
    return orderPlaced;
}

Time Order::getOrderDeliveredTime() const {
    return orderDelivered;
}

string Order::toString() {
    string orderSummary;

    orderSummary += orderPlaced.toString();
    orderSummary += " ; ";

    orderSummary += orderInfo;

    return orderSummary;
}

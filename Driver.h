// ==========================================================================
//
//                      Driver.h
//
// ==========================================================================

#ifndef FINALPROJECT_DRIVER_H
#define FINALPROJECT_DRIVER_H

#include <iostream>
#include <stdexcept>
#include <list>
#include "Time.h"
#include "Order.h"
using namespace std;

class Driver {
public:

    /** Parametrized constructor. Creates a Driver object with the given name.
        Name must be a single-word username and the driver must manually login.
    * @pre: None
    * @post: A Driver object with the given name is created */
    explicit Driver(string name);

    /** Logs in the driver.
    * @pre: Driver must not be logged in already
    * @post: The driver is logged in */
    void login() throw (logic_error);

    /** Logs out the driver.
    * @pre: Driver is logged in and at the restaurant
    * @post: The driver is logged out */
    void logout() throw (logic_error);

    /** The driver departs with the order. Departure time is recorded.
    * @pre: Driver is logged in and at the restaurant
    * @post: The driver departs and departure time is recorded */
    void depart(Time time, Order order) throw (logic_error);

    /** The driver delivers the order. Deliver time and tip amount is recorded.
    * @pre: Driver is delivering an order and tip >= 0
    * @post: The driver delivers the order; deliver time and tip amount is recorded */
    void deliver(Time time, float tip) throw (logic_error);

    /** The driver arrives back at the restaurant. Arrival time is recorded.
    * @pre: Driver is out driving and out on delivery
    * @post: The driver arrives and arrival time is recorded */
    void arrive(Time time) throw (logic_error);

    /** Returns the driver's single-word username.
    * @pre: None
    * @post: The driver's name is returned */
    string getName() const;

    /** Returns true if the driver is logged in. Returns false otherwise.
    * @pre: None
    * @post: Returns true if driver is logged in, false otherwise */
    bool isLoggedIn() const;

    /** Returns the total number of completed deliveries.
    * @pre: None
    * @post: The total number of completed deliveries is returned */
    int getTotalDeliveries() const;

    /** Returns the total minutes spent delivering
        (i.e. time between "depart" and "deliver" commands).
    * @pre: None
    * @post: The total minutes spent delivering is returned */
    int getTotalMinDelivering();

    /** Returns the total minutes spent driving
        (i.e. time between "depart" and "arrive" commands).
    * @pre: None
    * @post: A Driver object with the given name is created */
    int getTotalMinDriving();

    /** Returns the total minutes the order was undelivered
        (i.e. the time between "order" and "deliver" commands).
    * @pre: None
    * @post: The total minutes the order was undelivered is returned */
    int getTotalOrderTime();

    /** Returns the total amount of tips received, in dollars.
    * @pre: None
    * @post: The total tips received is returned */
    float getTotalTips() const;

    /** Returns the order being delivered.
        @NOTE: Unused in the final implementation.
    * @pre: The driver is delivering an order
    * @post: The order being delivered is returned */
    Order getOrder() throw (logic_error);

    /** Returns a string containing: the driver's name, whether or not they are
        logged in or not, (and if the driver is delivering an order) the toString
        of the order being delivered.
    * @pre: None
    * @post: A string containing the appropriate info about driver is returned */
    string toString();

private:

    string driverName;
    bool loggedIn;
    bool outOnDelivery;
    bool outDriving;

    Time departTime;
    Time deliverTime;
    Time arriveTime;
    Order driversOrder;

    int totalDeliveries;
    int totalMinDelivering;
    int totalMinDriving;
    float totalTips;
};

#endif //FINALPROJECT_DRIVER_H

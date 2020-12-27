// ==========================================================================
//
//                      Driver.cpp
//
// ==========================================================================

#include <stdexcept>
#include "Time.h"
#include "Order.h"
#include "Driver.h"
using namespace std;

// ==========================================================================
/** Parametrized constructor. Creates a Driver object with the given name.
    Name must be a single-word username and the driver must manually login.
  * @pre: None
  * @post: A Driver object with the given name is created
  */
Driver::Driver(string name) {
    driverName = name;
    loggedIn = false;
    outOnDelivery = false;
    outDriving = false;

    departTime = Time();
    deliverTime = Time();
    arriveTime = Time();
    driversOrder = Order();

    totalDeliveries = 0;
    totalMinDelivering = 0;
    totalMinDriving = 0;
    totalTips = 0.0;
}

// ==========================================================================
/** Logs in the driver.
  * @pre: Driver must not be logged in already
  * @post: The driver is logged in
  */
void Driver::login() throw (logic_error) {
    if (loggedIn) {
        throw logic_error("Error: User is already logged in.");
    }

    loggedIn = true;
}

// ==========================================================================
/** Logs out the driver.
  * @pre: Driver is logged in and at the restaurant
  * @post: The driver is logged out
  */
void Driver::logout() throw (logic_error) {
    if (!loggedIn || outOnDelivery) {
        throw logic_error("Error: User is either not logged in or out on delivery.");
    }

    loggedIn = false;
    outOnDelivery = false;
}

// ==========================================================================
/** The driver departs with the order. Departure time is recorded.
  * @pre: Driver is logged in and at the restaurant
  * @post: The driver departs and departure time is recorded
  */
void Driver::depart(Time time, Order order) throw (logic_error) {
    if (!loggedIn || outOnDelivery) {
        throw logic_error("Error: User is either not logged in or out on delivery.");
    }

    departTime = time;
    driversOrder = order;
    outOnDelivery = true;
}

// ==========================================================================
/** The driver delivers the order. Deliver time and tip amount is recorded.
  * @pre: Driver is delivering an order and tip >= 0
  * @post: The driver delivers the order; deliver time and tip amount is recorded
  */
void Driver::deliver(Time time, float tip) throw (logic_error) {
    if (!outOnDelivery || tip < 0) {
        throw logic_error("Error: User is not out on delivery or the tip is less than 0.");
    }

    deliverTime = time;
    totalTips += tip;
    outDriving = true;
}

// ==========================================================================
/** The driver arrives back at the restaurant. Arrival time is recorded.
  * @pre: Driver is out driving and out on delivery
  * @post: The driver arrives and arrival time is recorded
  */
void Driver::arrive(Time time) throw (logic_error) {
    if (!outDriving || !outOnDelivery) {
        throw logic_error("Error: User is either not out driving or is not delivering an order.");
    }

    arriveTime = time;
    totalDeliveries += 1;
    outOnDelivery = false;
    outDriving = false;
}

// ==========================================================================
/** Returns the driver's single-word username.
  * @pre: None
  * @post: The driver's name is returned
  */
string Driver::getName() const {
    return driverName;
}

// ==========================================================================
/** Returns true if the driver is logged in. Returns false otherwise.
  * @pre: None
  * @post: Returns true if driver is logged in, false otherwise
  */
bool Driver::isLoggedIn() const {
    return loggedIn;
}

// ==========================================================================
/** Returns the total number of completed deliveries.
  * @pre: None
  * @post: The total number of completed deliveries is returned
  */
int Driver::getTotalDeliveries() const {
    return totalDeliveries;
}

// ==========================================================================
/** Returns the total minutes spent delivering
    (i.e. time between "depart" and "deliver" commands).
  * @pre: None
  * @post: The total minutes spent delivering is returned
  */
int Driver::getTotalMinDelivering() {
    if (outOnDelivery) {
        return totalMinDriving;
    }
    else {
        totalMinDelivering += Time::elapsedMin(deliverTime, departTime);
        return totalMinDelivering;
    }
}

// ==========================================================================
/** Returns the total minutes spent driving
    (i.e. time between "depart" and "arrive" commands).
  * @pre: None
  * @post: A Driver object with the given name is created
  */
int Driver::getTotalMinDriving() {
    if (outOnDelivery) {
        return totalMinDriving;
    }
    else {
        totalMinDriving += Time::elapsedMin(arriveTime, departTime);
        return totalMinDriving;
    }
}

// ==========================================================================
/** Returns the total minutes the order was undelivered
    (i.e. the time between "order" and "deliver" commands).
  * @pre: None
  * @post: The total minutes the order was undelivered is returned
  */
int Driver::getTotalOrderTime() {
    return (Time::elapsedMin(driversOrder.getOrderPlacedTime(), deliverTime));
}

// ==========================================================================
/** Returns the total amount of tips received, in dollars.
  * @pre: None
  * @post: The total tips received is returned
  */
float Driver::getTotalTips() const {
    return totalTips;
}

// ==========================================================================
/** Returns the order being delivered.
    @NOTE: Unused in the final implementation.
  * @pre: The driver is delivering an order
  * @post: The order being delivered is returned
  */
Order Driver::getOrder() throw (logic_error) {
    if (!outOnDelivery) {
        throw logic_error("Error: User is not delivering an order.");
    }

    return driversOrder;
}

// ==========================================================================
/** Returns a string containing: the driver's name, whether or not they are
    logged in or not, (and if the driver is delivering an order) the toString
    of the order being delivered.
  * @pre: None
  * @post: A string containing the appropriate info about driver is returned
  */
string Driver::toString() {
    string driverSummary;

    driverSummary += driverName;
    driverSummary += " ; ";

    if (loggedIn) {
        driverSummary += "Logged in";
        driverSummary += " ; ";
    }
    else {
        driverSummary += "Not logged in";
        driverSummary += " ; ";
    }

    if (outOnDelivery) {
        driverSummary += "Out on delivery:";
        driverSummary += ' ';

        driverSummary += driversOrder.toString();
    }
    else {
        driverSummary += "Not out on delivery";
    }

    return driverSummary;
}

// ==========================================================================
//
//                      Time.h
//
// ==========================================================================

#ifndef FINALPROJECT_TIME_H
#define FINALPROJECT_TIME_H

#include <iostream>
#include <stdexcept>
#include <list>
using namespace std;

class Time {
public:

    /** Constructor. Creates a Time object with default values for data members.
    * @pre: None
    * @post: A Time object with default values is created */
    Time();

    /** Parametrized Constructor. Creates a Time object with the given hour and minute.
    * @pre: 0 <= hour <= 23 and 0 <= min <= 59
    * @post: A Time object with the given hour and minute is created */
    Time(int hour, int min) throw (logic_error);

    /** Returns the difference (in minutes) between Time t1 and Time t2. Takes into
        account whether t1 or t2 is larger for subtraction to avoid negative minutes.
    * @pre: None
    * @post: The difference between t1 and t2 is returned, in minutes */
    static int elapsedMin(Time t1, Time t2);

    /** Returns a string containing the hour and minute (i.e. "13:01").
    * @pre: None
    * @post: A string containing the hour and minute is returned */
    string toString();

    /** Helpful function used to combine hourPart[0] and hourPart[1] into one int
        in the elapsedMin function (same for minutePart[0] and minutePart[1]).
    * @pre: None
    * @post: Combines two parts of a Time object into a single int and returns it */
    static int concatenate(int a, int b);

private:

    int *hourPart;
    int *minutePart;
};

#endif //FINALPROJECT_TIME_H

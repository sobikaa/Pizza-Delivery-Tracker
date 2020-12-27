// ==========================================================================
//
//                      Time.cpp
//
// ==========================================================================

#include <stdexcept>
#include <string>
#include <list>
#include "Time.h"
using namespace std;

// ==========================================================================
/** Constructor. Creates a Time object with default values for data members.
  * @pre: None
  * @post: A Time object with default values is created
  */
Time::Time() {
    hourPart = new (int [2]){0,0};
    minutePart = new (int[2]){0,0};

    hourPart[0] = 0;
    hourPart[1] = 0;
    minutePart[0] = 0;
    minutePart[1] = 0;
}

// ==========================================================================
/** Parametrized Constructor. Creates a Time object with the given hour and minute.
  * @pre: 0 <= hour <= 23 and 0 <= min <= 59
  * @post: A Time object with the given hour and minute is created
  */
Time::Time(int hour, int min) throw (class logic_error) {

    if (hour > 23 || hour < 0) {
        throw logic_error("Error: Hour must be in the range from 0 to 23.");
    }
    if (min > 59 || min < 0) {
        throw logic_error("Error: Minutes must be in the range from 0 to 59.");
    }

    hourPart = new (int [2]){0,0};
    minutePart = new (int[2]){0,0};

    int hourAcc = 1;
    int minAcc = 1;

    while (hour > 0) {
        int digit = hour % 10;
        hourPart[hourAcc] = digit;
        hour /= 10;
        hourAcc -= 1;
    }

    while (min > 0) {
        int digit = min % 10;
        minutePart[minAcc] = digit;
        min /= 10;
        minAcc -= 1;
    }
}

// ==========================================================================
/** Returns the difference (in minutes) between Time t1 and Time t2. Takes into
    account whether t1 or t2 is larger for subtraction to avoid negative minutes.
  * @pre: None
  * @post: The difference between t1 and t2 is returned, in minutes
  */
int Time::elapsedMin(Time t1, Time t2) {

    int t1InMinutes = ((concatenate(t1.hourPart[0],t1.hourPart[1])) * 60)
                    + concatenate(t1.minutePart[0], t1.minutePart[1]);
    int t2InMinutes = ((concatenate(t2.hourPart[0],t2.hourPart[1])) * 60)
                      + concatenate(t2.minutePart[0], t2.minutePart[1]);

    if (t1InMinutes == t2InMinutes) {
        return 0;
    }
    else if (t1InMinutes > t2InMinutes) {
        return (t1InMinutes - t2InMinutes);
    }
    else {
        return (t2InMinutes - t1InMinutes);
    }
}

// ==========================================================================
/** Returns a string containing the hour and minute (i.e. "13:01").
  * @pre: None
  * @post: A string containing the hour and minute is returned
  */
string Time::toString() {
    string completeTime;

    completeTime += to_string(hourPart[0]);
    completeTime += to_string(hourPart[1]);
    completeTime += ':';
    completeTime += to_string(minutePart[0]);
    completeTime += to_string(minutePart[1]);

    return completeTime;
}

// ==========================================================================
/** Helpful function used to combine hourPart[0] and hourPart[1] into one int
    in the elapsedMin function (same for minutePart[0] and minutePart[1]).
  * @pre: None
  * @post: Combines two parts of a Time object into a single int and returns it
  */
int Time::concatenate(int a, int b) {

    string part1 = to_string(a);
    string part2 = to_string(b);

    string combo = part1 + part2;
    int endResult = stoi(combo);

    return endResult;
}
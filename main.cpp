// Sobika Thapa
// ==========================================================================
//
//       Command-line main.cpp
//
// ==========================================================================

#include <iostream>
#include <string>
#include "Time.h"
#include "Order.h"
#include "Driver.h"
#include "Restaurant.h"
using namespace std;

//--------------------------------------------------------------------

/** When called, this function displays the help menu to the user.
  * @pre: None
  * @post: The help menu is displayed to the user */
void print_help();

//--------------------------------------------------------------------

int main()
{
    Restaurant res1;            // Default restaurant object

    string cmd;                 // String used for reading user input
    string junk;                // Used when an invalid command is entered
    int keepRunning = 0;        // Variable used to keep reading commands
    int commandChecker = 0;     // Variable to check if a command is valid

    print_help();

    while (keepRunning == 0) {
        cout << endl << "Command: ";
        cin >> cmd;

        /** Case 1 -- help **/
        if (cmd == "Help" || cmd == "help") {
            print_help();
            commandChecker = 1;
        }

            /** Case 2 -- login **/
        else if (cmd.find("login") != string::npos) {

            Driver newDriver("");
            string driverName;

            cin >> driverName;

            if (res1.getDriver(driverName) != nullptr) {

                if (!res1.getDriver(driverName)->isLoggedIn()) {
                    res1.getDriver(driverName)->login();
                    cout << driverName << " is now logged in." << endl;
                    commandChecker = 2;
                }
                else {
                    cout << driverName << " is already logged in." << endl;
                }
            }
            else {
                newDriver = Driver(driverName);

                res1.addDriver(&newDriver);
                res1.getDriver(driverName)->login();

                cout << driverName << " is now logged in." << endl;
                commandChecker = 2;
            }
        }

            /** Case 3 -- logout **/
        else if (cmd.find("logout") != string::npos) {

            string driverName;
            cin >> driverName;

            if (res1.getDriver(driverName) == nullptr) {
                cout << driverName << " is not logged in; cannot log out." << endl;
            }
            else {
                res1.getDriver(driverName)->logout();

                cout << driverName << " is now logged out." << endl;
                commandChecker = 3;
            }
        }

            /** Case 4 -- order **/
        else if (cmd.find("order") != string::npos) {

            string inputtedTime;
            string inputtedOrder;

            cin >> inputtedTime;
            getline(cin, inputtedOrder);
            inputtedOrder.erase(0,1);

            string combo1;
            combo1.push_back(inputtedTime[0]);
            combo1.push_back(inputtedTime[1]);

            string combo2;
            combo2.push_back(inputtedTime[3]);
            combo2.push_back(inputtedTime[4]);

            int hourPart = stoi(combo1);
            int minPart = stoi(combo2);

            Time orderTime(hourPart, minPart);
            Order orderToAdd(orderTime, inputtedOrder);

            res1.addOrder(&orderToAdd);
            res1.setStartTime(orderTime);

            cout << "Order placed." << endl;
            commandChecker = 4;
        }

            /** Case 5 -- serve **/
        else if (cmd.find("serve") != string::npos) {
            string inputtedTime;
            cin >> inputtedTime;

            /** The time served is not needed, but code is here in case it is ever needed. **/

            //string combo1;
            //combo1.push_back(inputtedTime[0]);
            //combo1.push_back(inputtedTime[1]);

            //string combo2;
            //combo2.push_back(inputtedTime[3]);
            //combo2.push_back(inputtedTime[4]);

            //int hourPart = stoi(combo1);
            //int minPart = stoi(combo2);

            //Time serveTime(hourPart, minPart);

            /** End of time served code **/

            res1.serveNextOrder();

            cout << "Order served." << endl;
            commandChecker = 5;
        }

            /** Case 6 -- depart **/
        else if (cmd.find("depart") != string::npos) {
            string inputtedTime;
            string inputtedDriver;

            cin >> inputtedTime;
            cin >> inputtedDriver;

            string combo1;
            combo1.push_back(inputtedTime[0]);
            combo1.push_back(inputtedTime[1]);

            string combo2;
            combo2.push_back(inputtedTime[3]);
            combo2.push_back(inputtedTime[4]);

            int hourPart = stoi(combo1);
            int minPart = stoi(combo2);

            Time departTime(hourPart, minPart);
            res1.getDriver(inputtedDriver)->depart(departTime, *res1.departNextOrder());

            cout << "Order departed." << endl;
            commandChecker = 6;
        }

            /** Case 7 -- deliver **/
        else if (cmd.find("deliver") != string::npos) {

            string inputtedTime;
            string inputtedDriver;
            float inputtedTip;

            cin >> inputtedTime;
            cin >> inputtedDriver;
            cin >> inputtedTip;

            string combo1;
            combo1.push_back(inputtedTime[0]);
            combo1.push_back(inputtedTime[1]);

            string combo2;
            combo2.push_back(inputtedTime[3]);
            combo2.push_back(inputtedTime[4]);

            int hourPart = stoi(combo1);
            int minPart = stoi(combo2);

            Time deliverTime(hourPart, minPart);

            res1.getDriver(inputtedDriver)->deliver(deliverTime, inputtedTip);
            res1.setEndTime(deliverTime);
            res1.setTotalMinutes(res1.getDriver(inputtedDriver));
            res1.orderCompleted();

            cout << "Order delivered." << endl;
            commandChecker = 7;
        }

            /** Case 8 -- arrive **/
        else if (cmd.find("arrive") != string::npos) {

            string inputtedTime;
            string inputtedDriver;

            cin >> inputtedTime;
            cin >> inputtedDriver;

            if (res1.getDriver(inputtedDriver) == nullptr || !res1.getDriver(inputtedDriver)->isLoggedIn()) {
                cout << "Error: Driver is unable to arrive. Is the driver logged in?" << endl;
                break;
            }

            string combo1;
            combo1.push_back(inputtedTime[0]);
            combo1.push_back(inputtedTime[1]);

            string combo2;
            combo2.push_back(inputtedTime[3]);
            combo2.push_back(inputtedTime[4]);

            int hourPart = stoi(combo1);
            int minPart = stoi(combo2);

            Time arriveTime(hourPart, minPart);

            res1.getDriver(inputtedDriver)->arrive(arriveTime);

            cout << "Driver arrived." << endl;
            commandChecker = 8;
        }

            /** Case 9 -- status **/
        else if (cmd.find("status") != string::npos) {
            res1.status();
            commandChecker = 9;
        }

            /** Case 10 -- summary **/
        else if (cmd.find("summary") != string::npos) {
            res1.summary();
            commandChecker = 10;
        }

            /** Case 11 -- quit **/
        else if (cmd == "Quit" || cmd == "quit") {
            keepRunning = 11;
        }

            /** Error-checking **/
        else {
            commandChecker = 0;
        }

        if (commandChecker == 0) {
            getline(cin, junk);
            junk = "";
            cout << "Error: Invalid input; Please refer to the proper format." << endl;
            commandChecker = 0;
        }
    }

    return 0;
}

//--------------------------------------------------------------------

/** When called, this function displays the help menu to the user.
  * @pre: None
  * @post: The help menu is displayed to the user
  */
void print_help()
{
    cout << endl << "Commands:" << endl;
    cout << "help                    : Displays help (This menu)" << endl;
    cout << "login DRIVER            : This logs in DRIVER" << endl;
    cout << "logout DRIVER           : This logs out DRIVER" << endl;
    cout << "order TIME INFO         : Example -> order 9:55 2 veggie to 100 Liberty" << endl;
    cout << "serve TIME              : Order is done cooking at TIME and ready to be served" << endl;
    cout << "depart TIME DRIVER      : DRIVER departs for delivery at TIME" << endl;
    cout << "deliver TIME DRIVER TIP : DRIVER delivers order at TIME and gets TIP" << endl;
    cout << "arrive TIME DRIVER      : DRIVER returns from delivery at TIME" << endl;
    cout << "status                  : Status of orders and drivers is displayed" << endl;
    cout << "summary                 : Summary statistics on orders and drivers is displayed" << endl;
    cout << "quit                    : Terminates the program" << endl;
    cout << endl;
}
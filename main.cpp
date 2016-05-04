/*
TODO:
make flight class 3, for function printStatusOfSeats() to print seats in both classes
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int flightClass;                            // First/economy
int seatPick;                               // Which seat you pick (1-10). Also used to exit loops (when value is 0, certain loops are broken)
int switchClass;                            // Variable used to switch classes
//int reserveAnother=1;                     // Integer which changes according to client's need to reserve another seat (1=reserve one more, 0=stop reserving)
const int firstClassSeats[2]={1,5};         // Settings for the seats of the First class (first number - "from" seat, second - "to" seat)
const int economyClassSeats[2]={6,10};      // Settings for the seats of the Economy class (first number - "from" seat, second - "to" seat)
    /*  It is assumed that:
            First class seat indexes will be smaller than the indexes of the Economy class
            Both for First and Economy class, the first ("from") number will be smaller than the second ("to")
    */
bool seatStatus[10];                        // Taken/free. Set seatStatus[] to whatever value economyClassSeats[1] is
string seatStatusString;                    // Taken/free

void printStatusOfSeats(int flightClass)    // Function to print the available seats in the selected class.
{
    if (flightClass==1)
    {
        cout << endl <<  "Availiable seats in First Class: " << endl;
        for (int i=firstClassSeats[0]; i<=firstClassSeats[1]; i++)
        {
            if (seatStatus[i]==0)
            {
                seatStatusString = "free";
            }
            else if (seatStatus[i]==1)
            {
                seatStatusString = "taken";
            }
            cout << "Seat " << i << " is " << seatStatusString << endl;
        }

    }
    else if (flightClass==2)
    {
        cout << endl << "Availiable seats in Economy Class: " << endl;
        for (int i=economyClassSeats[0]; i<=economyClassSeats[1]; i++)
        {
            if (seatStatus[i]==0)
            {
                seatStatusString = "free";
            }
            else if (seatStatus[i]==1)
            {
                seatStatusString = "taken";
            }
            cout << "Seat " << i << " is " << seatStatusString << endl;
        }
    }
}

void printTickets()                         // Print tickets to file
{
}

int main()
{
    // Loop to set all seatStatus[] array values to 0 (seat free)
    // --------------------------- FOR LOOP START ---------------------------
    for (int i=firstClassSeats[0]; i<economyClassSeats[1]; i++)
    {
        seatStatus[i]=0;
    }
    // --------------------------- FOR LOOP END ---------------------------

    cout << "\t\t\tAirline flight reservation system" << endl;
    cout << "\t\t\tPick a Class:" << endl;

    // Only allows clint to pick class 1 or 2
    // --------------------------- WHILE LOOP START ---------------------------
    while (true)
    {
        cout << "\t\t\t1: First Class" << endl;
        cout << "\t\t\t2: Economy Class" << endl;
        cin >> flightClass;
        if (flightClass==1 || flightClass==2)
        {
            break;
        }
        else
        {
            cout << "Invalid choice, please pick a valid class" << endl;
        }
    }
    // --------------------------- WHILE LOOP END ---------------------------

    if (flightClass==2)
    {
        //while (true)
        //{
            cout << endl << "Pick a seat or enter 0 to exit:" << endl;
            printStatusOfSeats(flightClass);
            cin >> seatPick;
            //if (seatPick>=economyClassSeats[0] && seatPick<=economyClassSeats[1])
            //{
                while (true)
                {
                    if (seatPick==0) // Exits loop
                    {
                        break;
                    }
                    else if (seatPick<firstClassSeats[0] || seatPick>economyClassSeats[1]) // Seat not in range on flight class seats
                    {
                        cout << "Invalid seat, pick a valid one or enter 0 to exit" << endl;
                        printStatusOfSeats(flightClass);
                        cin >> seatPick;
                    }
                    else if (seatPick>=1 && seatPick<=5) // Seat is in the other class
                    {
                        cout << "Seat is in First class, would you like to pick a seat in the first class?" << endl;
                        cout << "1 - Yes" << endl;
                        cout << "0 - No, continue picking in Economy class" << endl;
                        cin >> switchClass;
                        if (switchClass==1)
                        {
                        }
                        else if (switchClass==0)
                        {
                        }
                    }
                    else if (seatStatus[seatPick]==1) // Seat is already taken
                    {
                        cout << endl << "Seat is already taken, pick another one or enter 0 to exit" << endl;
                        printStatusOfSeats(flightClass);
                        cin >> seatPick;
                    }
                    else // Reserves the seat
                    {
                        seatStatus[seatPick]=1;
                        cout << "Seat reserved" << endl;
                        cout << endl <<  "If you do not want to reserve anymore seats, input 0. Otherwise, enter the number of the seat you would like to reserve" << endl;
                        printStatusOfSeats(flightClass);
                        cin >> seatPick;
                    }
                }
            //}
            /*else
            {
                cout << "Invalid seat, please pick between 5th and 10th seat" << endl;
            }*/
            //break;
        //}
    }
    return 0;
}

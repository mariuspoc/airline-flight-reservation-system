#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

// Global variables
int flightClass;                            // First/second
int seatPick;                               // Which seat you pick (1-10). Also used to exit loops (when value is 0, certain loops are broken)
int switchClass;                            // Variable used to switch classes
const int firstClassSeats[2]={1,5};         // Settings for the seats of the First class (first number - "from" seat, second - "to" seat). These numbers are INCLUSIVE
const int secondClassSeats[2]={6,10};       // Settings for the seats of the Economy class (first number - "from" seat, second - "to" seat). These numbers are INCLUSIVE
/*  It is assumed that:
        First class "to" seat will be 1 smaller than the "from" seat of the second class (ignoring this will cause empty indexes)
        Both for First and Economy class, the first ("from") number will be smaller than the second ("to")
*/
bool seatStatus[10];                        // Taken/free. Set this to however many seats there are.
                                            // If there are seat gaps (between classes), set this to the absolute value of secondClassSeats[1].
                                            // A non-standard seat configuration, causes empty indexes, other problems
string seatStatusString;                    // Taken/free
const string nameOfClass1="First class";          // Name of the first class (default: First class)
const string nameOfClass2="Economy class";        // Name of the second class (default: Economy class)

/*
Currently, seat settings do not support a non-standard seat configuration.
Standard seat configuration can be described with these rules:
STRICT:
*Seat numbers of first class must be smaller than of the second class (Ignoring this will cause seats to become invalid)
*Seat ranges must not overlap (You will not be able to reserve overlapping seats, because you will just be redirected to the other class)
*Seat index "from" must be smaller than "to". Ignoring this will cause seats to become invalid and menu will not show any seats.

NON-STRICT, but you should follow anyway:
*Seat indexes shouldn't be negative
*Seat range should not include 0, as picking this seat will exit the program
*There shouldn't be a gap between first class and second class as you will be able to reserve "gap" seats, however they will not be displayed in the reservation menu. (there is an index in the array for it, but the seat "isn't there")
*Biggest seat index should not be over 99. (Otherwise, boarding passes will be printed incorrectly)
*/

const string currentDate() // Gets current date (YY-mm-dd)
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return buf;
}

const string currentTime() // Gets current time (HH:mm:ss)
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%X", &tstruct);

    return buf;
}

// Function prototypes
void printStatusOfSeats(int flightClass);           // Function to print the available seats in the selected class.
void printBoardingPass(int seatPick);               // Print boarding passes to file
void seatReservationMenu(int flightClass);          // Seat reservation menu

// ----------------------------------------------------------------------
int main()
{
    ofstream tickets;
    tickets.open("tickets.txt",ofstream::out | ofstream::trunc); // Creates the file if it doesn't exist, opens it, deletes all of it's content

    // Loop to set all seatStatus[] array values to 0 (seat free)
    for (int i=firstClassSeats[0]; i<secondClassSeats[1]; i++)
    {
        seatStatus[i]=0;
    }

    cout << "\t\t\tAirline flight reservation system" << endl;
    cout << "\t\t\tPick a Class:" << endl;

    // Only allows client to pick class 1 or 2
    while (true)
    {
        cout << "\t\t\t1: " << nameOfClass1 << endl;
        cout << "\t\t\t2: " << nameOfClass2 << endl;
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

    seatReservationMenu(flightClass);

    cout << endl << "Printing boarding passes" << endl << endl;
    for (int i=firstClassSeats[0]-1; i<secondClassSeats[1]; i++)
    {
        if (seatStatus[i]==1)
        {
            printBoardingPass(i+1);
        }
    }
    cout << endl << "Done printing boarding passes" << endl;
    return 0;
}
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
void printStatusOfSeats(int flightClass)
{
    if (flightClass==1)
    {
        cout << endl <<  "Availiable seats in the " << nameOfClass1 << ": " << endl;
        for (int i=firstClassSeats[0]-1; i<firstClassSeats[1]; i++)
        {
            if (seatStatus[i]==0)
            {
                seatStatusString = "free";
            }
            else if (seatStatus[i]==1)
            {
                seatStatusString = "taken";
            }
            cout << "Seat " << i+1 << " is " << seatStatusString << endl;
        }

    }
    else if (flightClass==2)
    {
        cout << endl << "Availiable seats in the " << nameOfClass2 << ": " << endl;
        for (int i=secondClassSeats[0]-1; i<secondClassSeats[1]; i++)
        {
            if (seatStatus[i]==0)
            {
                seatStatusString = "free";
            }
            else if (seatStatus[i]==1)
            {
                seatStatusString = "taken";
            }
            cout << "Seat " << i+1 << " is " << seatStatusString << endl;
        }
    }
    else if (flightClass==0)
    {
        //cout << endl << "Availiable seats in the " << nameOfClass2 << ": " << endl; // Commented because printing all seats isn't flight class specific
        for (int i=firstClassSeats[0]-1; i<secondClassSeats[1]; i++)
        {
            if (seatStatus[i]==0)
            {
                seatStatusString = "free";
            }
            else if (seatStatus[i]==1)
            {
                seatStatusString = "taken";
            }
            cout << "Seat " << i+1 << " is " << seatStatusString << endl;
        }
    }
}
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
void printBoardingPass(int seatPick)
{
    ofstream tickets;
    tickets.open("tickets.txt",ofstream::out | ofstream::app);
    cout << "Printing boarding pass for seat " << seatPick << endl;
    if (seatPick<10 && seatPick>0)
    {
        tickets << "______________________________________________________________" << endl;
        tickets << "|  UNITED               BOARDING PASS        |     UNITED    |" << endl;
        tickets << "| AIRLINES            ELECTRONIC TICKET      |    AIRLINES   |" << endl;
        tickets << "|                                            |               |" << endl;
        tickets << "|  FLIGHT: QF433             FROM: POINT A   |     A -> B    |" << endl;
        tickets << "|                            TO:   POINT B   |               |" << endl;
        tickets << "|  BOARDING DATE: " << currentDate() << "                 | FLIGHT: QF433 |" << endl;
        tickets << "|  BOARDING TILL: " << currentTime() << "                   | SEAT: 0" << seatPick << "      |" << endl;
        tickets << "|                                            | TIME: " << currentTime() << "|" << endl;
        tickets << "|  GATE:  A14                |||||||||||||   |               |" << endl;
        tickets << "|  SEAT:  0" << seatPick << "                                 | ||||||||||||| |" << endl;
        tickets << "|____________________________________________|_______________|" << endl << endl << endl;
    }
    else
    {
        tickets << "______________________________________________________________" << endl;
        tickets << "|  UNITED               BOARDING PASS        |     UNITED    |" << endl;
        tickets << "| AIRLINES            ELECTRONIC TICKET      |    AIRLINES   |" << endl;
        tickets << "|                                            |               |" << endl;
        tickets << "|  FLIGHT: QF433             FROM: POINT A   |     A -> B    |" << endl;
        tickets << "|                            TO:   POINT B   |               |" << endl;
        tickets << "|  BOARDING DATE: " << currentDate() << "                 | FLIGHT: QF433 |" << endl;
        tickets << "|  BOARDING TILL: " << currentTime() << "                   | SEAT: " << seatPick << "      |" << endl;
        tickets << "|                                            | TIME: " << currentTime() << "|" << endl;
        tickets << "|  GATE:  A14                |||||||||||||   |               |" << endl;
        tickets << "|  SEAT:  " << seatPick << "                                 | ||||||||||||| |" << endl;
        tickets << "|____________________________________________|_______________|" << endl << endl << endl;
    }
    tickets.close();
    cout << "Done" << endl;
}
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
void seatReservationMenu(int flightClass)
{
    if (flightClass==1) // First
    {
        cout << "You picked the " << nameOfClass1 << endl << endl;
        cout << endl << "Pick a seat or enter 0 to exit:" << endl;
        printStatusOfSeats(flightClass);
        cin >> seatPick;
        while (true)
        {
            if (seatPick==0) // Exits loop
            {
                break;
            }
            else if (seatPick<firstClassSeats[0] || seatPick>secondClassSeats[1]) // Seat not in range on flight class seats
            {
                cout << "Invalid seat, pick a valid one or enter 0 to exit" << endl;
                printStatusOfSeats(flightClass);
                cin >> seatPick;
            }
            else if (seatPick>=secondClassSeats[0] && seatPick<=secondClassSeats[1]) // Seat is in the other class
            {
                cout << endl << "Seat is in the " << nameOfClass2 << ", would you like to pick a seat in the " << nameOfClass2 << "?" << endl;
                cout << "1 - Yes" << endl;
                cout << "0 - No, continue picking in the " << nameOfClass1 << endl;
                cin >> switchClass;
                while (true)
                {
                    if (switchClass==1)
                    {
                        flightClass=2;
                        break;
                    }
                    else if (switchClass==0)
                    {
                        cout << "Continuing to pick in the " << nameOfClass1 << endl;
                        break;
                    }
                    else
                    {
                        cout << "Invalid choice, pick either 1 or 0" << endl;
                        cin >> switchClass;
                    }
                }
                seatReservationMenu(flightClass);
            }
            else if (seatStatus[seatPick-1]==1) // Seat is already taken
            {
                cout << endl << "Seat is already taken, pick another one or enter 0 to exit" << endl;
                printStatusOfSeats(flightClass);
                cin >> seatPick;
            }
            else // Reserves the seat
            {
                seatStatus[seatPick-1]=1;
                cout << "Seat reserved" << endl;
                cout << endl << "If you do not want to reserve anymore seats, input 0."
                     << endl << "Otherwise, enter the number of the seat you would like to reserve" << endl;
                printStatusOfSeats(flightClass);
                cin >> seatPick;
            }
        }
    }
    else if (flightClass==2) // Second
    {
        cout << "You picked the " << nameOfClass2 << endl << endl;
        printStatusOfSeats(flightClass);
        cin >> seatPick;
        while (true)
        {
            if (seatPick==0) // Exits loop
            {
                break;
            }
            else if (seatPick<firstClassSeats[0] || seatPick>secondClassSeats[1]) // Seat not in range on flight class seats
            {
                cout << "Invalid seat, pick a valid one or enter 0 to exit" << endl;
                printStatusOfSeats(flightClass);
                cin >> seatPick;
            }
            else if (seatPick>=firstClassSeats[0] && seatPick<=firstClassSeats[1]) // Seat is in the other class
            {
                cout << endl << "Seat is in the " << nameOfClass1 << ", would you like to pick a seat in the " << nameOfClass1 << "?" << endl;
                cout << "1 - Yes" << endl;
                cout << "0 - No, continue picking in the " << nameOfClass2 << endl;
                cin >> switchClass;
                while (true)
                {
                    if (switchClass==1)
                    {
                        flightClass=1;
                        break;
                    }
                    else if (switchClass==0)
                    {
                        cout << "Continuing to pick in the " << nameOfClass2 << endl;
                        break;
                    }
                    else
                    {
                        cout << "Invalid choice, pick either 1 or 0" << endl;
                        cin >> switchClass;
                    }
                }
                seatReservationMenu(flightClass);
            }
            else if (seatStatus[seatPick-1]==1) // Seat is already taken
            {
                cout << endl << "Seat is already taken, pick another one or enter 0 to exit" << endl;
                printStatusOfSeats(flightClass);
                cin >> seatPick;
            }
            else // Reserves the seat
            {
                seatStatus[seatPick-1]=1;
                cout << "Seat reserved" << endl;
                cout << endl <<  "If you do not want to reserve anymore seats, input 0. Otherwise, enter the number of the seat you would like to reserve" << endl;
                printStatusOfSeats(flightClass);
                cin >> seatPick;
            }
        }
    }
}
// ----------------------------------------------------------------------

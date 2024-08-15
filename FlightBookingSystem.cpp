#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

enum class FlightClass { Economy, Business, First };

class Passenger {
private:
    string name;

public:
    Passenger(const string& n) : name(n) {}

    string getName() const {
        return name;
    }
};

class Seat {
private:
    bool isOccupied;
    string passengerName;

public:
    Seat() : isOccupied(false), passengerName("") {}

    bool getIsOccupied() const {
        return isOccupied;
    }

    void occupy(const string& name) {
        isOccupied = true;
        passengerName = name;
    }

    void vacate() {
        isOccupied = false;
        passengerName = "";
    }

    string getPassengerName() const {
        return passengerName;
    }
};

class Flight {
private:
    string flightNumber;
    string origin;
    string destination;
    int capacity;
    map<FlightClass, vector<Seat>> seats;

public:
    Flight(const string& number, const string& src, const string& dest, int cap) : flightNumber(number), origin(src), destination(dest), capacity(cap) {
        seats[FlightClass::Economy] = vector<Seat>(capacity);
        seats[FlightClass::Business] = vector<Seat>(capacity);
        seats[FlightClass::First] = vector<Seat>(capacity);
    }

    string getFlightNumber() const {
        return flightNumber;
    }

    string getOrigin() const {
        return origin;
    }

    string getDestination() const {
        return destination;
    }

    int getAvailableSeats(FlightClass flightClass) const {
        int availableSeats = 0;
        for (const Seat& seat : seats.at(flightClass)) {
            if (!seat.getIsOccupied()) {
                availableSeats++;
            }
        }
        return availableSeats;
    }

    bool bookTicket(FlightClass flightClass, const Passenger& passenger, int seatNumber) {
        if (seatNumber < 1 || seatNumber > capacity) {
            cout << "Invalid seat number!" << endl;
            return false;
        }

        Seat& seat = seats.at(flightClass).at(seatNumber - 1);
        if (!seat.getIsOccupied()) {
            seat.occupy(passenger.getName());
            cout << "Ticket booked successfully for " << passenger.getName() << " in seat " << seatNumber << "." << endl;
            return true;
        } else {
            cout << "Seat " << seatNumber << " is already occupied." << endl;
            return false;
        }
    }

    bool cancelTicket(FlightClass flightClass, int seatNumber) {
        if (seatNumber < 1 || seatNumber > capacity) {
            cout << "Invalid seat number!" << endl;
            return false;
        }

        Seat& seat = seats.at(flightClass).at(seatNumber - 1);
        if (seat.getIsOccupied()) {
            seat.vacate();
            cout << "Ticket canceled successfully for seat " << seatNumber << "." << endl;
            return true;
        } else {
            cout << "Seat " << seatNumber << " is not occupied." << endl;
            return false;
        }
    }

    void displaySeatMap(FlightClass flightClass) const {
        cout << "Seat Map for Flight " << flightNumber << " (" << origin << " to " << destination << "):" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << setw(10) << "Seat No." << setw(20) << "Passenger Name" << endl;
        cout << "-----------------------------------------------" << endl;
        int seatNumber = 1;
        for (const Seat& seat : seats.at(flightClass)) {
            cout << setw(10) << seatNumber;
            if (seat.getIsOccupied()) {
                cout << setw(20) << seat.getPassengerName();
            } else {
                cout << setw(20) << "Available";
            }
            cout << endl;
            seatNumber++;
        }
        cout << "-----------------------------------------------" << endl;
    }
};

class FlightBookingSystem {
private:
    vector<Flight> flights;

public:
    const vector<Flight>& getFlights() const {
        return flights;
    }

    void addFlight(const Flight& flight) {
        flights.push_back(flight);
    }

    void displayAvailableFlights() const {
        cout << "Available Flights:" << endl;
        for (const Flight& flight : flights) {
            cout << "Flight " << flight.getFlightNumber() << ": " << flight.getOrigin() << " to " << flight.getDestination() << endl;
            cout << "Economy Class: " << flight.getAvailableSeats(FlightClass::Economy) << " seats available" << endl;
            cout << "Business Class: " << flight.getAvailableSeats(FlightClass::Business) << " seats available" << endl;
            cout << "First Class: " << flight.getAvailableSeats(FlightClass::First) << " seats available" << endl;
            cout << endl;
        }
    }

    bool bookTicket(const string& flightNumber, FlightClass flightClass, const Passenger& passenger, int seatNumber) {
        for (Flight& flight : flights) {
            if (flight.getFlightNumber() == flightNumber) {
                return flight.bookTicket(flightClass, passenger, seatNumber);
            }
        }
        cout << "Flight " << flightNumber << " not found." << endl;
        return false;
    }

    bool cancelTicket(const string& flightNumber, FlightClass flightClass, int seatNumber) {
        for (Flight& flight : flights) {
            if (flight.getFlightNumber() == flightNumber) {
                return flight.cancelTicket(flightClass, seatNumber);
            }
        }
        cout << "Flight " << flightNumber << " not found." << endl;
        return false;
    }

    void displaySeatMap(const string& flightNumber, FlightClass flightClass) const {
        for (const Flight& flight : flights) {
            if (flight.getFlightNumber() == flightNumber) {
                flight.displaySeatMap(flightClass);
                return;
            }
        }
        cout << "Flight " << flightNumber << " not found." << endl;
    }
};

int main() {
    FlightBookingSystem system;

    system.addFlight(Flight("FL001", "Visakhapatnam", "Silchar", 100));
    system.addFlight(Flight("FL002", "Silchar", "Hyderabad", 100));
    system.addFlight(Flight("FL003", "Silchar", "Kolkata", 50));
    system.addFlight(Flight("FL004", "Mumbai", "Chennai", 150));
    system.addFlight(Flight("FL005", "Banglore", "Silchar", 150));

    int choice;
    do {
        cout<<"\n Welcome To NITS Flight bookings \n";
        cout << "\nFlight Booking System Menu:\n";
        cout << "1. Display available flights\n";
        cout << "2. Book ticket\n";
        cout << "3. Cancel ticket\n"; 
        cout << "4. Show seat map\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                system.displayAvailableFlights();
                break;
            }
            case 2: {
    string flightNumber;
    FlightClass flightClass;
    int numPassengers;

    cout << "Enter flight number: ";
    cin >> flightNumber;
    bool flightFound = false;
    for (const Flight& flight : system.getFlights()) {
        if (flight.getFlightNumber() == flightNumber) {
            flightFound = true;
            break;
        }
    }
    if (!flightFound) {
        cout << "Flight " << flightNumber << " not found." << endl;
        break;
    }

    cout << "Enter class (1 - Economy, 2 - Business, 3 - First): ";
    int classChoice;
    cin >> classChoice;
    switch (classChoice) {
        case 1:
            flightClass = FlightClass::Economy;
            break;
        case 2:
            flightClass = FlightClass::Business;
            break;
        case 3:
            flightClass = FlightClass::First;
            break;
        default:
            cout << "Invalid choice!" << endl;
            continue;
    }

    cout << "Enter number of passengers: ";
    cin >> numPassengers;

    for (int i = 0; i < numPassengers; ++i) {
        string passengerName;
        int seatNumber;

        cout << "Enter passenger name: ";
        cin >> passengerName;

        cout << "Enter seat number: ";
        cin >> seatNumber;

        if (seatNumber < 1 || seatNumber > system.getFlights().front().getAvailableSeats(flightClass)) {
            cout << "Invalid seat number!" << endl;
            continue;
        }

        Passenger passenger(passengerName);

        if (system.bookTicket(flightNumber, flightClass, passenger, seatNumber)) {
        } else {
            cout << "Failed to book ticket for " << passenger.getName() << "." << endl;
        }
    }
    break;
}
           case 3: {
    string flightNumber;
    int classChoice;
    int seatNumber;

    cout << "Enter flight number: ";
    cin >> flightNumber;
    bool flightFound = false;
    for (const Flight& flight : system.getFlights()) {
        if (flight.getFlightNumber() == flightNumber) {
            flightFound = true;
            break;
        }
    }
    if (!flightFound) {
        cout << "Flight " << flightNumber << " not found." << endl;
        break;
    }

    cout << "Enter class (1 - Economy, 2 - Business, 3 - First): ";
    cin >> classChoice;
    FlightClass flightClass;
    switch (classChoice) {
        case 1:
            flightClass = FlightClass::Economy;
            break;
        case 2:
            flightClass = FlightClass::Business;
            break;
        case 3:
            flightClass = FlightClass::First;
            break;
        default:
            cout << "Invalid choice!" << endl;
            continue;
    }

    cout << "Enter seat number to cancel: ";
    cin >> seatNumber;

    if (system.cancelTicket(flightNumber, flightClass, seatNumber)) {
    } else {
        cout << "Failed to cancel ticket for seat " << seatNumber << "." << endl;
    }
    break;
}

            case 4: {
                string flightNumber;
    int classChoice;

    cout << "Enter flight number: ";
    cin >> flightNumber;
    bool flightFound = false;
    for (const Flight& flight : system.getFlights()) {
        if (flight.getFlightNumber() == flightNumber) {
            flightFound = true;
            break;
        }
    }
    if (!flightFound) {
        cout << "Flight " << flightNumber << " not found." << endl;
        break;
    }

    cout << "Enter class (1 - Economy, 2 - Business, 3 - First): ";
    cin >> classChoice;
    FlightClass flightClass;
    switch (classChoice) {
        case 1:
            flightClass = FlightClass::Economy;
            break;
        case 2:
            flightClass = FlightClass::Business;
            break;
        case 3:
            flightClass = FlightClass::First;
            break;
        default:
            cout << "Invalid choice!" << endl;
            continue;
    }

    system.displaySeatMap(flightNumber, flightClass);
    
                break;
            }
            case 5: {
                cout << "Exiting... Thank you for using the NITS Flight Booking System!" << endl;
                break;
            }
            default: {
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        }
    } while (choice != 5);

    return 0;


}

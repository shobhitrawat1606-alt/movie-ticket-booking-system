#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Screen {
private:
    int screenNumber;
    vector<Seat> seats;

public:
    Screen(int screenNumber) : screenNumber(screenNumber) {}

    int getScreenNumber() const { return screenNumber; }

    void addSeat(const Seat& seat) {
        seats.push_back(seat);
    }

    vector<Seat>& getSeats() { return seats; }
    const vector<Seat>& getSeats() const { return seats; }

    void displaySeats() const {
        for (const Seat& seat : seats) {
            cout << seat.getSeatNumber() << "("
                 << seat.getTypeName() << ") ";
        }
        cout << '\n';
    }
};

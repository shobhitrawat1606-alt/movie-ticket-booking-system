#include <string>
using namespace std;

class ShowSeat {
public:
    enum Status { AVAILABLE, BOOKED };

private:
    Seat* seat;
    Status status;

public:
    explicit ShowSeat(Seat* seat)
        : seat(seat), status(AVAILABLE) {}

    string getSeatNumber() const {
        return seat->getSeatNumber();
    }

    string getTypeName() const {
        return seat->getTypeName();
    }

    double getPrice() const {
        return seat->getPrice();
    }

    bool isAvailable() const {
        return status == AVAILABLE;
    }

    bool book() {
        if (!isAvailable()) return false;
        status = BOOKED;
        return true;
    }

    void release() {
        status = AVAILABLE;
    }

    string getStatusName() const {
        return isAvailable() ? "AVAILABLE" : "BOOKED";
    }
};

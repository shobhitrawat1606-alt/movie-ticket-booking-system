#include <string>
#include <vector>
using namespace std;

class Booking {
public:
    enum Status { PENDING, CONFIRMED, FAILED, CANCELLED };

private:
    static int nextBookingId;
    int bookingId;
    Customer* customer;
    Show* show;
    vector<ShowSeat*> seats;
    AddFood* food;
    double totalAmount;
    Status status;

public:
    Booking(Customer* customer, Show* show, const vector<ShowSeat*>& seats, AddFood* food, double totalAmount)
        : bookingId(nextBookingId++), customer(customer), show(show), seats(seats), food(food), totalAmount(totalAmount), status(PENDING) {}

    int getBookingId() const { return bookingId; }
    Customer* getCustomer() const { return customer; }
    Show* getShow() const { return show; }
    const vector<ShowSeat*>& getSeats() const { return seats; }
    AddFood* getFood() const { return food; }
    double getTotalAmount() const { return totalAmount; }
    Status getStatus() const { return status; }

    void confirm() { status = CONFIRMED; }
    void fail() { status = FAILED; }
    void cancel() { status = CANCELLED; }

    string getStatusName() const {
        switch (status) {
            case PENDING: return "PENDING";
            case CONFIRMED: return "CONFIRMED";
            case FAILED: return "FAILED";
            case CANCELLED: return "CANCELLED";
        }
        return "UNKNOWN";
    }
};

int Booking::nextBookingId = 1001;

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BookingService {
private:
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

public:
    Booking* createBooking(Customer* customer,
                           Show* show,
                           const vector<string>& seatNumbers,
                           AddFood* food) {
        vector<ShowSeat*> selectedSeats;

        for (const string& seatNumber : seatNumbers) {
            ShowSeat* seat = show->findShowSeat(seatNumber);

            if (seat == nullptr) {
                cout << "Invalid seat: " << seatNumber
                     << "\nBooking rejected. No seats changed.\n";
                return nullptr;
            }

            if (!seat->isAvailable()) {
                cout << "Seat " << seatNumber
                     << " is already BOOKED.\n"
                     << "Booking rejected. No seats changed.\n";
                return nullptr;
            }

            selectedSeats.push_back(seat);
        }

        if (selectedSeats.empty()) {
            cout << "No seat selected.\n";
            return nullptr;
        }

        double total = priceCalculator.calculateTotal(selectedSeats, food);
        Booking* booking =
            new Booking(customer, show, selectedSeats, food, total);

        for (ShowSeat* seat : selectedSeats) {
            seat->book();
        }

        return booking;
    }

    bool makePayment(Booking* booking, Payment* payment) {
        if (booking == nullptr || payment == nullptr)
            return false;

        bool paid = payment->pay(booking->getTotalAmount());

        if (paid) {
            booking->confirm();
            cout << "Payment successful. Booking confirmed.\n";
            return true;
        }

        for (ShowSeat* seat : booking->getSeats()) {
            seat->release();
        }

        booking->fail();
        cout << "Payment failed.\n";
        cout << "Seats have been released.\n";
        return false;
    }

    void printTicket(const Booking& booking) const {
        ticketPrinter.printTicket(booking);
    }

    bool cancelBooking(Booking* booking) {
        if (booking == nullptr ||
            booking->getStatus() != Booking::CONFIRMED) {
            cout << "Only a confirmed booking can be cancelled.\n";
            return false;
        }

        for (ShowSeat* seat : booking->getSeats()) {
            seat->release();
        }

        booking->cancel();

        cout << "Booking cancelled successfully.\n";
        cout << "Seats are AVAILABLE again.\n";
        return true;
    }
};

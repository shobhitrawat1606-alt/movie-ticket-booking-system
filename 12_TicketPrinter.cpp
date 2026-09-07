#include <iostream>
using namespace std;

class TicketPrinter {
public:
    void printTicket(const Booking& booking) const {
        const AddFood* food = booking.getFood();
        cout << "\n========== MOVIE TICKET ==========\n";
        cout << "Booking ID : " << booking.getBookingId() << '\n';
        cout << "Customer   : " << booking.getCustomer()->getName() << '\n';
        cout << "Phone      : " << booking.getCustomer()->getPhone() << '\n';
        cout << "Movie      : " << booking.getShow()->getMovie()->getTitle() << '\n';
        cout << "Screen     : " << booking.getShow()->getScreen()->getScreenNumber() << '\n';
        cout << "Start Time : " << booking.getShow()->getStartTime() << '\n';
        cout << "Seats      : ";
        for (size_t i = 0; i < booking.getSeats().size(); ++i) {
            if (i > 0) cout << ", ";
            cout << booking.getSeats()[i]->getSeatNumber();
        }
        cout << "\nFood       : " << ((food != nullptr && food->hasPopcorn()) ? "Popcorn" : "No Food");
        cout << "\nFood Amount: Rs. " << (food != nullptr ? food->getFoodPrice() : 0.0);
        cout << "\nTotal      : Rs. " << booking.getTotalAmount() << '\n';
        cout << "Status     : " << booking.getStatusName() << '\n';
        cout << "==================================\n";
    }
};

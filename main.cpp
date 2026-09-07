#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// No header files are used.
// Each major class is kept in its own .cpp file as required.
#include "01_Movie.cpp"
#include "02_Seat.cpp"
#include "03_Screen.cpp"
#include "04_Cinema.cpp"
#include "05_AddFood.cpp"
#include "06_ShowSeat.cpp"
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
#include "13_BookingService.cpp"

void showMenu() {
    cout << "\n========== MOVIE TICKET BOOKING ==========\n";
    cout << "1. List Movies\n";
    cout << "2. List Shows for a Movie\n";
    cout << "3. Display Seat Layout\n";
    cout << "4. Book Seats\n";
    cout << "5. Print Ticket\n";
    cout << "6. Cancel Booking\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

vector<string> readSeatNumbers() {
    cout << "Enter seat numbers separated by spaces: ";

    string line;
    getline(cin, line);

    stringstream input(line);
    vector<string> seats;
    string seat;

    while (input >> seat) {
        seats.push_back(seat);
    }

    return seats;
}

void addSeats(Screen& screen) {
    const Seat::Type rowTypes[] = {
        Seat::SILVER, Seat::SILVER,
        Seat::GOLD, Seat::GOLD,
        Seat::PLATINUM, Seat::PLATINUM
    };

    for (int row = 0; row < 6; ++row) {
        char rowLetter = static_cast<char>('A' + row);
        for (int number = 1; number <= 10; ++number) {
            string seatNumber(1, rowLetter);
            seatNumber += to_string(number);
            screen.addSeat(Seat(seatNumber, rowTypes[row]));
        }
    }
}

int main() {
    Cinema cinema("City Cinema");

    Movie movie1("3 Idiots", "Hindi", 170);
    Movie movie2("Interstellar", "English", 169);

    cinema.addMovie(movie1);
    cinema.addMovie(movie2);

    Screen screen1(1);
    Screen screen2(2);

    // Seat layout:
    // SILVER   -> A[10], B[10]
    // GOLD     -> C[10], D[10]
    // PLATINUM -> E[10], F[10]
    addSeats(screen1);
    addSeats(screen2);

    cinema.addScreen(screen1);
    cinema.addScreen(screen2);

    vector<Show> shows;
    shows.emplace_back(&cinema.getMovies()[0],
                       &cinema.getScreens()[0], "06:00 PM");
    shows.emplace_back(&cinema.getMovies()[0],
                       &cinema.getScreens()[1], "09:00 PM");
    shows.emplace_back(&cinema.getMovies()[1],
                       &cinema.getScreens()[1], "07:00 PM");

    for (Show& show : shows) {
        show.createShowSeats();
    }

    BookingService bookingService;
    vector<Booking*> bookings;
    vector<Customer*> customers;

    while (true) {
        showMenu();

        int choice;
        cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice == 1) {
            cinema.listMovies();
        }
        else if (choice == 2) {
            cout << "\nMovies:\n";
            cinema.listMovies();
            cout << "Select movie number: ";

            int movieChoice;
            cin >> movieChoice;

            if (movieChoice < 1 ||
                movieChoice > static_cast<int>(cinema.getMovies().size())) {
                cout << "Invalid movie choice.\n";
                continue;
            }

            cout << "\nShows for "
                 << cinema.getMovies()[movieChoice - 1].getTitle()
                 << ":\n";

            for (size_t i = 0; i < shows.size(); ++i) {
                if (shows[i].getMovie() ==
                    &cinema.getMovies()[movieChoice - 1]) {
                    cout << "[" << i + 1 << "] Screen "
                         << shows[i].getScreen()->getScreenNumber()
                         << " | " << shows[i].getStartTime() << '\n';
                }
            }
        }
        else if (choice == 3) {
            cout << "Select show number:\n";

            for (size_t i = 0; i < shows.size(); ++i) {
                cout << "[" << i + 1 << "] "
                     << shows[i].getMovie()->getTitle()
                     << " | Screen "
                     << shows[i].getScreen()->getScreenNumber()
                     << " | " << shows[i].getStartTime() << '\n';
            }

            int showChoice;
            cin >> showChoice;

            if (showChoice < 1 ||
                showChoice > static_cast<int>(shows.size())) {
                cout << "Invalid show choice.\n";
                continue;
            }

            shows[showChoice - 1].displaySeats();
        }
        else if (choice == 4) {
            cout << "Select show number:\n";

            for (size_t i = 0; i < shows.size(); ++i) {
                cout << "[" << i + 1 << "] "
                     << shows[i].getMovie()->getTitle()
                     << " | Screen "
                     << shows[i].getScreen()->getScreenNumber()
                     << " | " << shows[i].getStartTime() << '\n';
            }

            int showChoice;
            cin >> showChoice;

            if (showChoice < 1 ||
                showChoice > static_cast<int>(shows.size())) {
                cout << "Invalid show choice.\n";
                continue;
            }

            cout << "\n========== CUSTOMER DETAILS ==========" << '\n';

            string customerName;
            string customerPhone;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter your name: ";
            getline(cin, customerName);

            cout << "Enter your phone number: ";
            getline(cin, customerPhone);

            if (customerName.empty() || customerPhone.empty()) {
                cout << "Customer details cannot be empty. Booking cancelled.\n";
                continue;
            }

            Customer* customer = new Customer(customerName, customerPhone);
            customers.push_back(customer);

            vector<string> seatNumbers = readSeatNumbers();

            if (seatNumbers.empty()) {
                cout << "No seat selected. Booking cancelled.\n";
                continue;
            }

            cout << "\nWould you like to add popcorn for Rs. 120?\n";
            cout << "1. Yes\n";
            cout << "2. No\n";
            cout << "Enter choice: ";

            int foodChoice;
            cin >> foodChoice;

            if (foodChoice != 1 && foodChoice != 2) {
                cout << "Invalid food choice. Booking cancelled.\n";
                continue;
            }

            AddFood* food = new AddFood();
            food->setPopcorn(foodChoice == 1);

            Booking* booking =
                bookingService.createBooking(
                    customer,
                    &shows[showChoice - 1],
                    seatNumbers,
                    food);

            if (booking == nullptr) {
                delete food;
                continue;
            }

            cout << "\nChoose payment method:\n";
            cout << "1. UPI\n";
            cout << "2. Card\n";
            cout << "3. Cash\n";
            cout << "Enter choice: ";

            int paymentChoice;
            cin >> paymentChoice;

            Payment* payment = nullptr;

            if (paymentChoice == 1) {
                string upiId;
                cout << "Enter UPI ID: ";
                cin >> upiId;
                payment = new UpiPayment(upiId);
            }
            else if (paymentChoice == 2) {
                string cardNumber;
                cout << "Enter card number: ";
                cin >> cardNumber;
                payment = new CardPayment(cardNumber);
            }
            else if (paymentChoice == 3) {
                payment = new CashPayment();
            }
            else {
                cout << "Invalid payment method.\n";
                for (ShowSeat* seat : booking->getSeats()) {
                    seat->release();
                }
                booking->fail();
                delete booking->getFood();
                delete booking;
                continue;
            }

            bool successful =
                bookingService.makePayment(booking, payment);

            if (successful) {
                bookings.push_back(booking);
                bookingService.printTicket(*booking);
            }
            else {
                delete booking->getFood();
                delete booking;
            }

            delete payment;
        }
        else if (choice == 5) {
            if (bookings.empty()) {
                cout << "No bookings available.\n";
                continue;
            }

            cout << "Enter Booking ID: ";
            int bookingId;
            cin >> bookingId;

            bool found = false;

            for (Booking* booking : bookings) {
                if (booking->getBookingId() == bookingId) {
                    bookingService.printTicket(*booking);
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Booking not found.\n";
            }
        }
        else if (choice == 6) {
            if (bookings.empty()) {
                cout << "No bookings available.\n";
                continue;
            }

            cout << "Enter Booking ID to cancel: ";
            int bookingId;
            cin >> bookingId;

            bool found = false;

            for (Booking* booking : bookings) {
                if (booking->getBookingId() == bookingId) {
                    bookingService.cancelBooking(booking);
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Booking not found.\n";
            }
        }
        else {
            cout << "Invalid menu choice. Please try again.\n";
        }
    }

    for (Booking* booking : bookings) {
        delete booking->getFood();
        delete booking;
    }

    for (Customer* customer : customers) {
        delete customer;
    }

    cout << "\nThank you for using Movie Ticket Booking System.\n";
    return 0;
}

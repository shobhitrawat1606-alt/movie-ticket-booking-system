MOVIE TICKET BOOKING SYSTEM
TCS-504 System Design Assignment - Part F

FILE STRUCTURE
01_Movie.cpp
02_Seat.cpp
03_Screen.cpp
04_Cinema.cpp
05_Show.cpp
06_ShowSeat.cpp
07_Customer.cpp
08_Booking.cpp
09_Payment.cpp
10_PaymentTypes.cpp
11_PriceCalculator.cpp
12_TicketPrinter.cpp
13_BookingService.cpp
main.cpp

IMPORTANT:
- No header files are used.
- Each major class is in its own .cpp file.
- main.cpp includes the class .cpp files in dependency order.
- Compile main.cpp only.

WINDOWS / MIN-GW:
g++ main.cpp -std=c++17 -o movie_booking.exe
movie_booking.exe

FEATURES:
1. List movies
2. List shows for a movie
3. Display seat layout
4. Book one or more seats
5. Seat pricing: SILVER 150, GOLD 250, PLATINUM 400
6. UPI / Card / Cash payment
7. Print ticket
8. Cancel booking

EDGE CASES:
- Already-booked seat rejects the entire booking without changing seat states.
- Failed payment releases all temporarily booked seats.
- Cancellation makes booked seats AVAILABLE again.
- Invalid menu/movie/show/seat/payment choices are handled without crashing.

OOP:
- Encapsulation
- Abstraction
- Inheritance
- Runtime polymorphism
- Compile-time polymorphism
- Static member
- this keyword
- Composition
- Aggregation
- Association


LATEST CHANGES
- Seat layout is grouped into SILVER, GOLD and PLATINUM sections.
- SILVER: A[10], B[10]; GOLD: C[10], D[10]; PLATINUM: E[10], F[10].
- Each row contains 10 seats. [A1] means available; [XX] means booked.
- Customer must enter name and phone number before selecting seats and proceeding with payment.

NEW FOOD FEATURE:
- AddFood.cpp manages optional popcorn selection.
- Popcorn price is Rs. 120.
- Food is selected before payment.
- PriceCalculator adds food cost to seat cost.
- Booking and TicketPrinter store/display the food selection and amount.

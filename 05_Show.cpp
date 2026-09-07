#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Show {
private:
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;

    void displayRow(char rowLetter) const {
        cout << rowLetter << "  ";

        for (int number = 1; number <= 10; ++number) {
            string seatNumber(1, rowLetter);
            seatNumber += to_string(number);

            const ShowSeat* seat = nullptr;
            for (const ShowSeat& showSeat : showSeats) {
                if (showSeat.getSeatNumber() == seatNumber) {
                    seat = &showSeat;
                    break;
                }
            }

            if (seat != nullptr) {
                if (seat->isAvailable())
                    cout << "[" << seatNumber << "] ";
                else
                    cout << "[XX] ";
            }
        }
        cout << '\n';
    }

    void displayCategory(const string& category,
                         char firstRow,
                         char secondRow) const {
        cout << "\n================ " << category << " ================\n";
        displayRow(firstRow);
        displayRow(secondRow);
    }

public:
    Show(Movie* movie, Screen* screen, const string& startTime)
        : movie(movie), screen(screen), startTime(startTime) {}

    void createShowSeats() {
        showSeats.clear();
        for (Seat& seat : screen->getSeats()) {
            showSeats.emplace_back(&seat);
        }
    }

    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }

    vector<ShowSeat>& getShowSeats() { return showSeats; }
    const vector<ShowSeat>& getShowSeats() const { return showSeats; }

    ShowSeat* findShowSeat(const string& seatNumber) {
        for (ShowSeat& showSeat : showSeats) {
            if (showSeat.getSeatNumber() == seatNumber)
                return &showSeat;
        }
        return nullptr;
    }

    void displaySeats() const {
        cout << "\n============================================================\n";
        cout << "Movie  : " << movie->getTitle() << '\n';
        cout << "Screen : " << screen->getScreenNumber()
             << "    Time : " << startTime << '\n';
        cout << "============================================================\n";
        cout << "[A1] = AVAILABLE     [XX] = BOOKED\n";

        displayCategory("SILVER - Rs.150", 'A', 'B');
        displayCategory("GOLD - Rs.250", 'C', 'D');
        displayCategory("PLATINUM - Rs.400", 'E', 'F');

        cout << "\nSeat format: A[10] means row A has 10 seats.\n";
    }
};

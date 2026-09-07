#include <string>
using namespace std;

class Seat {
public:
    enum Type { SILVER, GOLD, PLATINUM };

private:
    string seatNumber;
    Type seatType;

public:
    Seat(const string& seatNumber, Type seatType)
        : seatNumber(seatNumber), seatType(seatType) {}

    string getSeatNumber() const { return seatNumber; }
    Type getSeatType() const { return seatType; }

    double getPrice() const {
        const double SILVER_PRICE = 150.0;
        const double GOLD_PRICE = 250.0;
        const double PLATINUM_PRICE = 400.0;

        if (seatType == SILVER) return SILVER_PRICE;
        if (seatType == GOLD) return GOLD_PRICE;
        return PLATINUM_PRICE;
    }

    string getTypeName() const {
        if (seatType == SILVER) return "SILVER";
        if (seatType == GOLD) return "GOLD";
        return "PLATINUM";
    }
};

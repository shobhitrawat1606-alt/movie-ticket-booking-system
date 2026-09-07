#include <vector>
using namespace std;

class PriceCalculator {
public:
    double calculateTotal(const vector<ShowSeat*>& seats, const AddFood* food) const {
        double total = 0.0;
        for (const ShowSeat* seat : seats) total += seat->getPrice();
        if (food != nullptr) total += food->getFoodPrice();
        return total;
    }

    double calculateTotal(const ShowSeat* seat) const { return seat->getPrice(); }
    double getFoodPrice(const AddFood* food) const {
        return food == nullptr ? 0.0 : food->getFoodPrice();
    }
};

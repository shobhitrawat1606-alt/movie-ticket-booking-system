#include <iostream>
using namespace std;

class AddFood {
private:
    bool wantPopcorn;
    double popcornPrice;

public:
    AddFood() : wantPopcorn(false), popcornPrice(120.0) {}

    void setPopcorn(bool choice) { wantPopcorn = choice; }
    bool hasPopcorn() const { return wantPopcorn; }
    double getFoodPrice() const { return wantPopcorn ? popcornPrice : 0.0; }
};

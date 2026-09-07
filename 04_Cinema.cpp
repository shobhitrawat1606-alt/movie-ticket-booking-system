#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Cinema {
private:
    string name;
    vector<Screen> screens;
    vector<Movie> movies;

public:
    Cinema(const string& name) : name(name) {}

    void addScreen(const Screen& screen) {
        screens.push_back(screen);
    }

    void addMovie(const Movie& movie) {
        movies.push_back(movie);
    }

    vector<Screen>& getScreens() { return screens; }
    vector<Movie>& getMovies() { return movies; }

    const vector<Screen>& getScreens() const { return screens; }
    const vector<Movie>& getMovies() const { return movies; }

    void listMovies() const {
        if (movies.empty()) {
            cout << "No movies currently playing.\n";
            return;
        }

        for (size_t i = 0; i < movies.size(); ++i) {
            cout << "[" << i + 1 << "] ";
            movies[i].display();
            cout << '\n';
        }
    }
};

#include <iostream>
#include <string>

class AuditoriumEvent {
    std::string eventName;
    int rows;
    int seatsPerRow;
    char** grid;

public:
    AuditoriumEvent(const std::string& name, int r, int s)
        : eventName(name), rows(r), seatsPerRow(s), grid(nullptr) {
        if (rows > 0 && seatsPerRow > 0) {
            grid = new char*[rows];
            for (int i = 0; i < rows; ++i) {
                grid[i] = new char[seatsPerRow];
                for (int j = 0; j < seatsPerRow; ++j) {
                    grid[i][j] = 'O';
                }
            }
        }
        std::cout << "[CTOR] " << eventName << " (" << rows << "x" << seatsPerRow << ")\n";
    }

    ~AuditoriumEvent() {
        int bookedCount = 0;
        if (grid != nullptr) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < seatsPerRow; ++j) {
                    if (grid[i][j] == 'B') ++bookedCount;
                }
                delete[] grid[i];
            }
            delete[] grid;
        }
        std::cout << "[DTOR] " << eventName << " released; booked seats = " << bookedCount << '\n';
    }

    bool book(int r, int s) {
        if (r >= 0 && r < rows && s >= 0 && s < seatsPerRow && grid[r][s] == 'O') {
            grid[r][s] = 'B';
            return true;
        }
        return false;
    }

    bool cancel(int r, int s) {
        if (r >= 0 && r < rows && s >= 0 && s < seatsPerRow && grid[r][s] == 'B') {
            grid[r][s] = 'O';
            return true;
        }
        return false;
    }
};

int main() {
    AuditoriumEvent mainHall("TechSummit", 10, 20);
    mainHall.book(2, 5);
    mainHall.book(2, 6);
    mainHall.cancel(2, 6);

    {
        AuditoriumEvent miniBlock("Workshop", 0, 10);
    }

    AuditoriumEvent* heapEvent = new AuditoriumEvent("Concert", 100, 200);
    delete heapEvent;
    return 0;
}
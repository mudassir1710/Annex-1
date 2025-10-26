#include <iostream>
#include <cstdlib>   // provides rand() and srand()
#include <ctime>     // provides time() so the randomness varies each run
using namespace std;

// Function declarations (we keep the same signatures as before)
void startDay();
int getWeather();
bool checkObstacle();
void deliverPackage(string location, int& battery, int& success, int& failed, int& delayed);
void showSummary(int success, int failed, int delayed, int battery);

int main() {
    // Seed the random number generator so outcomes change each time
    srand(time(0));

    // Program state: battery percentage and counters for delivery outcomes
    int battery = 100;              // drone starts fully charged (100%)
    int success = 0, failed = 0, delayed = 0;   // track delivery results
    char start;

    // Print a small intro for the user
    startDay();

    // Ask the user to begin the delivery day. We accept 'S' or 's'.
    cout << "Press S to start delivery day: ";
    cin >> start;

    // If the user doesn't press S, end the program gracefully
    if (start != 'S' && start != 's') {
        cout << "Mission cancelled." << endl;
        return 0;
    }

    // Perform three deliveries to fixed locations. Each call updates
    // battery and the counters (success/failed/delayed) by reference.
    deliverPackage("Location A", battery, success, failed, delayed);
    deliverPackage("Location B", battery, success, failed, delayed);
    deliverPackage("Location C", battery, success, failed, delayed);

    // After all attempts, show a human-readable summary of the day.
    showSummary(success, failed, delayed, battery);

    return 0;
}

// ---------------- Function Definitions ----------------

// Print a short introduction. This tells the user what to expect.
void startDay() {
    cout << "=============================" << endl;
    cout << "   DRONE DELIVERY PROGRAM\n";
    cout << "=============================" << endl;
    cout << "Starting battery: 100%\n";
    cout << "Weather and obstacles are random.\n"<< endl;
}

// Return a simple coded weather value.
// 1 = sunny (good), 2 = windy (can be tricky), 3 = rainy (no flights)
int getWeather() {
    return rand() % 3 + 1; // returns 1, 2, or 3
}

// Randomly say whether an obstacle appears in the route.
// This is a 50/50 chance (true or false).
bool checkObstacle() {
    return (rand() % 2 == 1);
}

// Try to deliver a package to `location`.
// - `battery` is passed by reference and will be decreased according to usage.
// - `success`, `failed`, `delayed` are counters updated by reference.
// This function prints short, friendly messages describing each event.
void deliverPackage(string location, int& battery, int& success, int& failed, int& delayed) {
    cout << "\nDelivering to " << location << "..." << endl;

    int weather = getWeather();        // determine current weather
    bool obstacle = checkObstacle();   // randomly see if an obstacle shows up
    int drain = 10 + rand() % 16;      // base battery use: 10–25%

    // Rain means we postpone the delivery: no battery is used now.
    if (weather == 3) {
        cout << "Rainy weather! Delivery delayed." << endl;
        delayed++;
        return; // leave early — no flight in rain
    }

    // If it's windy and the battery is already low, drone returns to base
    // to recharge a little (we simulate a small recharge of 10%).
    if (weather == 2 && battery < 40) {
        cout << "Windy and low battery! Returning to base for recharge." << endl;
        battery += 10;   // simulate a short recharge
        if (battery > 100) battery = 100;  // cap battery at 100%
        delayed++;
        return; // delivery postponed
    }

    // If there's an obstacle, the drone uses slightly more battery to avoid it.
    if (obstacle) {
        cout << "Obstacle found! Using more battery." << endl;
        drain += 5; // extra cost for detour/avoidance
    }

    // There's a small chance (10%) of an unexpected system problem.
    // If that happens, the delivery fails and we still apply battery drain.
    bool malfunction = (rand() % 10 == 0);

    if (malfunction) {
        cout << "System problem! Delivery failed." << endl;
        failed++;
        battery -= drain;
        if (battery < 0) battery = 0;
        return;
    }

    // If we have enough battery to cover the drain, delivery succeeds.
    if (battery >= drain) {
        battery -= drain;    // subtract battery used
        cout << "Delivery successful!" << endl;
        success++;
    }
    else {
        // Not enough battery left to complete the mission
        cout << "Not enough battery! Mission failed." << endl;
        failed++;
    }

    cout << "Battery left: " << battery << "%" << endl;
}

// Print a simple, human-friendly summary of the day's deliveries.
void showSummary(int success, int failed, int delayed, int battery) {
    cout << "\n=============================" << endl;
    cout << "      DAY SUMMARY\n";
    cout << "=============================" << endl;
    cout << "Successful deliveries: " << success << endl;
    cout << "Failed deliveries: " << failed << endl;
    cout << "Delayed deliveries: " << delayed << endl;
    cout << "Battery remaining: " << battery << "%" << endl;
    cout << "=============================" << endl;
}
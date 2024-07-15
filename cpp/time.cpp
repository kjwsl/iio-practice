#include <chrono>
#include <ctime>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main() {
    auto now {system_clock::now()};
    time_t tm { system_clock::to_time_t(now)};
    cout << tm << endl;
    return 0;
}

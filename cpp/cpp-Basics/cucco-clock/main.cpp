#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>
#include <string>
#include <bitset>

void clear_line(int n) {
    std::string line_up = "\x1b[A";
    std::string line_clear = "\33[2K\r";
    for (int i {0}; i < n; ++i) {
        std::cout << line_up << line_clear << std::flush;
    }
}

int main() {
    while (true) {
        // outputs the date and time
        const std::chrono::time_point now = std::chrono::system_clock::now();
        const std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::cout << std::ctime(&time);

        // outputes the hours
        long hours = std::chrono::duration_cast<std::chrono::hours>(now.time_since_epoch()).count() % 24 - 5;
        std::cout << "Current hours: " << hours << '\n';

        // outputs the minutes
        long minutes = std::chrono::duration_cast<std::chrono::minutes>(now.time_since_epoch()).count() % 60;
        std::cout << "Current minutes: " << minutes << '\n';

        // outputs the seconds
        long seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count() % 60;
        std::cout << "Current seconds: " << seconds << "\n\n";

        // outputs the binary hours
        std::string b_hours = std::bitset<8>(static_cast<unsigned long>(hours)).to_string();
        std::cout << "Current binary hours: " << b_hours << '\n';

        // outputs the binary minutes
        std::string b_minutes = std::bitset<8>(static_cast<unsigned long>(minutes)).to_string();
        std::cout << "Current binary minutes: " << b_minutes << '\n';

        // outputs the binary seconds
        std::string b_seconds = std::bitset<8>(static_cast<unsigned long>(seconds)).to_string();
        std::cout << "Current binary seconds: " << b_seconds << "\n\n";

        // change output to hexadecimal
        std::cout << std::hex;

        // outputs the hexadecimal hours
        std::cout << "Current hexadecimal hours: " << hours << '\n';

        // outputs the hexadecimal minutes
        std::cout << "Current hexadecimal minutes: " << minutes << '\n';

        // outputs the hexadecimal seconds
        std::cout << "Current hexadecimal seconds: " << seconds << '\n';

        // change output back to decimal
        std::cout << std::dec;

        // Wait for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // clears the lines that were output
        clear_line(12);
    }

    return 0;
}

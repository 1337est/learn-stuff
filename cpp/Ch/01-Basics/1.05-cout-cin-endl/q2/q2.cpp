#include <iostream>

// Asks user for 3 inputs. Output those inputs in a sentence.
int main() {
    std::cout << "Enter three numbers: ";

    int a{};
    int b{};
    int c{};
    std::cin >> a >> b >> c;

    std::cout << "You entered " << a << ", " << b << ", and " << c << "." << std::endl;

    return 0;
}

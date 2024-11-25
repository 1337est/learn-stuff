#include <iostream>

// template class
template <typename T, typename U>
class Operations {
private:
    T m_a{};
    U m_b{};

public:
    Operations(const T& a, const U& b)
        : m_a { a }
        , m_b { b }
    {}

    // addition function
    double add(T a, U b) {
        return a + b;
    }

    // subtraction function
    double subtract(T a, U b) {
        return a - b;
    }

    // multiplication function
    double multiply(T a, U b) {
        return a * b;
    }

    // division function
    double divide(T a, U b) {
        if (b  == 0) {
            std::cerr << "Error: Division by zero is not allowed\n";
            return 0;
        }

        return a / b;
    }
};

// Function to loop and exit the calculator app
template <typename T, typename U>
void calculatorLoop() {
    char operation{};
    T a{};
    U b{};
    Operations<T, U> op{a, b};

    while (true) {
        std::cout << "Enter what operation (+, -, *, /) you want to perform ";
        std::cout << "on 2 numbers, or Enter 'q' to quit: ";
        std::cin >> operation;
        std::cout << '\n';

        if (operation == 'q') break;

        std::cout << "Enter the 2 numbers you want to perform " << operation
            << " on: ";
        std::cin >> a >> b;
        std::cout << "\nResult of " << a << " " << operation << " " << b
            << " is: ";

        switch (operation) {
            case '+': std::cout << op.add(a, b) << '\n'; break;
            case '-': std::cout << op.subtract(a, b) << '\n'; break;
            case '*': std::cout << op.multiply(a, b) << '\n'; break;
            case '/': std::cout << op.divide(a, b) << '\n'; break;
            default:  std::cout << "Invalid operation!\n"; break;
        }
        std::cout << '\n';
    }

}

int main() {
    calculatorLoop<int, double>();

    return 0;
}

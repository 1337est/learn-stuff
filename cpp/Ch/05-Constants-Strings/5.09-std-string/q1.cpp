#include <iostream> // for user input/output
#include <string> // for std::string and std::getline()

/*
 * Ask user for their name
 * Ask user for their age
 * Output the users age + letters.length of their name
 * std::string::length() returns unsigned value, use std::ssize() for signed value
*/

int main()
{
    // Ask user for name
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // read full line

    // Ask user for age
    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    // Calculate age + name.length
    std::cout << "Your age + length of name (with whitespace) is: " << age + std::ssize(name) << '\n';

    return 0;
}

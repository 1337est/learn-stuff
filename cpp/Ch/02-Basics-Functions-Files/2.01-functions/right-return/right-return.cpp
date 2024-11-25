#include <iostream>

int getValueFromUser() // this function now returns an integer value!
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;

    return input; // returns the value the user entered back to the caller
}

int main()
{
    int num { getValueFromUser() }; //initialize num with the return value from getValueFromUser()
    
    std::cout << num << " doubled is: " << num * 2 << '\n';

    return 0;
}

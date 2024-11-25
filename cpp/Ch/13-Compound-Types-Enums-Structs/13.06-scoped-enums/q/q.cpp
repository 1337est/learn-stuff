#include <iostream>
#include <string_view>

enum class Animal
{
    pig, chicken, goat, cat, dog, duck,
};

constexpr std::string_view getAnimalName(Animal animal)
{
    using enum Animal; // bring all Animal enums into function scope

    switch (animal)
    {
    case pig:       return "pig";
    case chicken:   return "chicken";
    case goat:      return "goat";
    case cat:       return "cat";
    case dog:       return "dog";
    case duck:      return "duck";
    default:        return "???";
    }
}

void printNumberOfLegs(Animal animal)
{
    using enum Animal; // bring all Animal enums into function scope

    std::cout << "A " << getAnimalName(animal) << " has ";

    switch (animal)
    {
    case pig:
    case goat:
    case cat:
    case dog:
        std::cout << 4;
        break;

    case duck:
    case chicken:
        std::cout << 2;
        break;
    default:
        std::cout << "???";
        break;
    }

    std::cout << " legs.\n";
}

int main()
{
    printNumberOfLegs(Animal::cat);
    printNumberOfLegs(Animal::chicken);

    return 0;
}

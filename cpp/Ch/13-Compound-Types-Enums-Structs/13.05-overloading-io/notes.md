In the previous lesson we had an example where we used a function to convert an enumeration into an equivalent string:
```cpp
#include <iostream>
#include <string_view>

enum Color
{
    black,
    red,
    blue,
};

constexpr std::string_view getColorName(Color color)
{
    switch (color)
    {
    case black: return "black";
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

int main()
{
    constexpr Color shirt{ blue };

    std::cout << "Your shirt is " << getColorName(shirt) << '\n';

    return 0;
}
```

We can do better. Ideally we would want to somehow teach `operator<<` to output an enumeration, so we could do something like this: `std::cout << shirt` and have it do what we expect.

## Introduction to operator overloading

**Operator overloading** allows us to define overloads of existing operators, so that we can make those operators work with our program-defined data types.

Basic operator overloading is fairly straightforward:
- Define a function using the name of the operator as the function's name.
- Add a parameter of the appropriate type for each operand (in left-to-right order). One of these parameters must be a user-defined type (a class or enumerated type), otherwise the compiler will error.
- Set the return type to whatever makes sense
- Use a return statement to return the result of the operation

When the compiler encounters the user of an operator in an expression and one or more of the operands is a user-defined type, the compiler will check to see if there is an overloaded operator function that it can use to resolve that call. E.g. given some expression `x + y`, the compiler will use function overload resolution to see if there is an `operator+(x, y)` function call that it can use to evaluate the operation. If a non-ambiguous `operator+` function can be found, it will be called, and the result of the operation returned as the return value. This is pretty neat.

## Overloading `operator<<` to print an enumerator

Let's review how `operator<<` works for output.

Consider this expression: `std::cout << 5`. `std::cout` has type `std::ostream` and `5` is a literal of type `int`.

When this expression is evaluated, the compiler will look for an overloaded `operator<<` function that can handle arguments of type `std::ostream` and `int`. It will find such a function and call it. Inside that function, `std::cout` is used to output `x` to the console. Finally the `operator<<` function returns its left-operand (which in this case is `std::cout`), so that subsequent calls to `operator<<` can be chained.

Now with that out of the way, let's implement an overload of `operator<<` to print a `Color`:
```cpp
#include <iostream>
#include <string_view>

enum Color
{
	black,
	red,
	blue,
};

constexpr std::string_view getColorName(Color color)
{
    switch (color)
    {
    case black: return "black";
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout, std::cerr, etc...
// The return type and parameter type are references (to prevent copies from being made)
std::ostream& operator<<(std::ostream& out, Color color)
{
    out << getColorName(color); // print our color's name to whatever output stream out
    return out;                 // operator<< conventionally returns its left operand

    // The above can be condensed to the following single line:
    // return out << getColorName(color)
}

int main()
{
	Color shirt{ blue };
	std::cout << "Your shirt is " << shirt << '\n'; // it works!

	return 0;
}
```

```
Your shirt is blue
```

You probably have no idea what's going on, so let's break it down.

1. We name of the function `operator<<`, since that is the name of the operator we're overloading.
2. The function `operator<<` has 2 parameters:
    - The left parameter is our output stream of type `std::ostream` which we pass by non-const reference because we don't want to make a copy of the `std::ostream` object when the function is called, but we do want the object to be modified in order to do output.
    - The right parameter is our `Color` object.
    - Since `operator<<` conventionally returns its left operand, the return type matches the type of the left-operand, which is `std::ostream&`
3. A `std::ostream` object already knows how to print a `std::string_view` using `operator<<` as part of the standard library. So `out << getColorName(color)` simply fetches our color's name as a `std::string_view` and then prints it to the output stream.
4. Returning the left operand is also easy since the left operand is parameter `out`, so we just return `out`.

Putting it all together now: when we call `std::cout << shirt`, the compiler will see that we've overloaded `operator<<` to work with objects of type `Color`. Our overloaded `operator<<` function is then called with `std::cout` as the `out` parameter, and our `shirt` variable (which has value `blue`) as parameter `color`. Since `out` is a reference to `std::cout`, and `color` is a copy of enumerator `blue`, the expression `out << getColorName(color)` within the function, prints `"blue"` to the console. Finally, `out` is returned back to the caller in case we want to chain additional output.

## Overloading `operator>>` to input an enumerator

```cpp
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <string_view>

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}

constexpr std::optional<Pet> getPetFromString(std::string_view sv)
{
    if (sv == "cat")   return cat;
    if (sv == "dog")   return dog;
    if (sv == "pig")   return pig;
    if (sv == "whale") return whale;

    return {};
}

// pet is an in/out parameter
std::istream& operator>>(std::istream& in, Pet& pet)
{
    std::string s{};
    in >> s; // get input string from user

    std::optional<Pet> match { getPetFromString(s) };
    if (match) // if we found a match
    {
        pet = *match; // set Pet to the matching enumerator
        return in;
    }

    // We didn't find a match, so input must have been invalid
    // so we will set input stream to fail state
    in.setstate(std::ios_base::failbit);

    // On an extraction failure, operator>> zero-initializes fundamental types
    // Uncomment the following line to make this operator do the same thing
    // pet = {};

    return in;
}

int main()
{
    std::cout << "Enter a pet: cat, dog, pig, or whale: ";
    Pet pet{};
    std::cin >> pet;

    if (std::cin) // if we found a match
        std::cout << "You chose: " << getPetName(pet) << '\n';
    else
    {
        std::cin.clear(); // reset the input stream to good
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Your pet was not valid\n";
    }

    return 0;
}
```

Go through this code line by line.

There are a few differences from the output case. First, `std::cin` has type `std::istream` so we use `std::istream&` as the type of our left parameter and return value instead of `std::ostream&`. Secondly, the `pet` parameter is a non-const reference as well. This is to allow our `operator>>` to modify  the value of the right operand that is passed in if our extraction results in a match.



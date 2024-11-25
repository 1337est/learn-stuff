## Some quick things on C-style strings

C-style strings, as discussed by just using `std::cout << "Hello, world!";` have some wonkyness to them:

- You can't use assignment to assign a C-syle string variable a new value
- If you copy a larger C-style string into the space for a shorter C-style string, undefined behavior will result.

## Introducing `std::string`
```cpp
#include <iostream>
#include <string> // allows use of std::string

int main()
{
    std::string name { "Alex" }; // empty string
    std::cout << name << '\n';

    name = "Jason";             // allows changing name to longer string
    std::cout << name << '\n';

    name = "Jay";               // allows changing name to shorter string
    std::cout << name << '\n';

    return 0;
}
```

##  String input with `std::cin`
`std::cin` only takes in the first string value before a space character. Therefore, if you have a long input from a user with spaces like a "Enter: firstname lastname":
```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::cin >> name; // this won't work as expected since std::cin breaks with whitespace

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::cin >> color; // std::cin will take the next space character into color

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

    return 0;
}
```

```
Enter your full name: John Doe
Enter your favorite color: Your name is John and your favorite color is Doe
```

The `operator>>` that extracts the string from `std::cin` returns only the trailing character until the first whitespace it encounters.

## `std::getline()` to input text

Use `std::getline()` from `<string>` to get whitespace separated text passed into `std::cin`.

- `std::getline()` requires two arguments: the first is `std::cin` and the second is the string variable.

```cpp
#include <iostream>
#include <string> // For std::string and std::getline

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // read a full line of text into name

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::getline(std::cin >> std::ws, color); // read a full line of text into color

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

    return 0;
}
```

```
Enter your full name: John Doe
Enter your favorite color: blue
Your name is John Doe and your favorite color is blue
```

Now you may have noticed something odd here...

## WTF is `std::ws`

Just as there's output manipulators like `std::setprecision()` which we used to change the number of digits of precision that `std::cout` displays, there is also input manipulators which alter the way input is accepted.

`std::ws` is an input manipulator that tells `std::cin` to ignore any leading whitespace before extraction. A leading whitespace is simply any whitespace characters (spaces, tabs, newlines) that occur at the start of the string. Now you may be thinking, "Leading whitespace?"

Well, when we press the "Return" key on our keyboard after input, that's also captured. So instead of "input" we get "input\n" as input. What's captured by `std::cin` is the entire "input\n", but what's extracted is the "input", leaving the "\n" queued up in "std::cin". Any further calls to `std::cin` will cause `std::cin` to think that we've already got a queued up "\n", and just figures "I'll take it", completely disregarding that we actually wanted to input something from the user.

Here's an example:
```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;

    std::cout << "Now enter your name: ";
    std::string name{};
    std::getline(std::cin, name); // note: no std::ws here

    std::cout << "Hello, " << name << ", you picked " << choice << '\n';

    return 0;
}
```

```
Pick 1 or 2: 2
Now enter your name: Hello, , you picked 2
```

As you can see, `choice` is 2, but since `std::cin` has the queued "\n", it simply puts "\n" into name and continues the program none the wiser.

We simply amend the program by putting `std::cin >> std::ws, name` into the program. As you have probably guessed by now, `ws` in `std::ws` stands for "whitespace".

## The length of `std::string`

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{ "Alex" };
    std::cout << name << " has " << name.length() << " characters\n";

    return 0;
}
```

Pretty straightforward.

## Do not pass `std::string` by value

When `std::string` is passed to a function by value, the `std::string` function parameter must be instantiated band initialized with the argument, resulting in an expensive copy.

- Don't pass `std::string` by value. Use `std::string_view` parameters instead (discussed in the next section).

## Returning `std::string`

It's okay to return `std::string` by value when the expression of the return statement resolves to any of the following:

- A local variable of type `std::string`
- A `std::string` that has been returned by value from another function call or operator
- A `std::string` temporary that is created as part of the return statement

## Literals for `std::string`

Double quoted string literals like "Hello world!" are C-style strings by default.

We can create string literals with type `std::string` by using a `s` suffix after the double-quoted text (which must be lowercase `s`).

```cpp
#include <iostream>
#include <string> // for std::string

int main()
{
    using namespace std::string_literals; // easy access to the s suffix

    std::cout << "foo\n"; // no suffix is a C-style string literal
    std::cout << "goo\n"s; // s suffix is a std::string literal

    return 0;
}
```

The use case involves type deduction where using `std::string` literals instead of C-style string literals makes things easier.

## Constexpr strings

`constexpr std::string` will likely make your compiler generate an error because it isn't supported at all in C++17 or earlier and only works in limited cases in C++20/23. Just use `std::string_view` instead. Discussed in the next section.



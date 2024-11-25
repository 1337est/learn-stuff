The process of matching function calls to a specific overloaded function is called **overload resolution**.

What happens when the argument types in the function call don't exactly match the parameter types in any of the overloaded functions?:

```cpp
#include <iostream>

void print(int x)
{
     std::cout << x << '\n';
}

void print(double d)
{
     std::cout << d << '\n';
}

int main()
{
     print('a'); // char does not match int or double, so what happens?
     print(5L); // long does not match int or double, so what happens?

     return 0;
}
```

## Resolving overloaded function calls

The compiler steps through a sequence of rules to determine which (if any) of the overloaded functions is the best match.

At each step, the compiler applies a bunch of different type conversions to the argument(s) in the function call. For each conversion applied, the compiler checks if any of the overloaded functions are now a match. The result will be one of 3 possible outcomes:
1. No matching functions were found. The compiler moves to the next step in the sequence.
2. A single matching function was found. This function is considered to be the best match. The matching process is now complete, and subsequent steps are not executed.
3. More than once matching function was found. The compiler will issue an ambiguous match compile error.

If the compiler reaches the end without finding a match, it will generate a compile error that no matching overloaded function could be found for the function call.

## The argument matching sequence

Step 1) The compiler tries to find an exact match.
1. The compiler will see if there's an overloaded function where the type of the arguments in the function call exactly matches the type of the parameters in the overloaded functions.

```cpp
void foo(int)
{
}

void foo(double)
{
}

int main()
{
    foo(0);   // exact match with foo(int)
    foo(3.4); // exact match with foo(double)

    return 0;
}
```

2. The compiler will apply a number of **trivial conversions**, which are a set of specific conversion rules that will modify types (without modifying values) for purposes of finding a match
    - lvalue to rvalue conversions
    - qualification conversions (e.g. non-const to const)
    - non-reference to reference conversions
```cpp
void foo(const int)
{
}

void foo(const double&)
{
}

int main()
{
    int x { 1 };
    foo(x); // x trivially converted from int to const int

    double d { 2.3 };
    foo(d); // d trivially converted from double to const double&

    return 0;
}
```

Matches made via the trivial conversions are considered exact matches. The following results in an ambiguous match:
```cpp
void foo(int)
{
}

void foo(const int&)
{
}

int main()
{
    int x { 1 };
    foo(x); // ambiguous match with foo(int) and foo(const int&)

    return 0;
}
```

Step 2) If no exact match is found, the compiler tries to find a match by applying numeric promotion to the argument(s).

```cpp
void foo(int)
{
}

void foo(double)
{
}

int main()
{
    foo('a');  // promoted to match foo(int)
    foo(true); // promoted to match foo(int)
    foo(4.5f); // promoted to match foo(double)

    return 0;
}
```

Step 3) If no match is found via numeric promotion, the compiler tries to find a match by applying numeric conversions to the arguments.

```cpp
#include <string> // for std::string

void foo(double)
{
}

void foo(std::string)
{
}

int main()
{
    foo('a'); // 'a' converted to match foo(double)

    return 0;
}
```

Step 4) If no match is found via numeric conversion, the compiler tries to find a match through any user-defined conversions. Although we haven't covered user-defined conversions yet, certain types (e.g. classes) can define conversions to other types that can be implicitly invoked.

```cpp
// We haven't covered classes yet, so don't worry if this doesn't make sense
class X // this defines a new type called X
{
public:
    operator int() { return 0; } // Here's a user-defined conversion from X to int
};

void foo(int)
{
}

void foo(double)
{
}

int main()
{
    X x; // Here, we're creating an object of type X (named x)
    foo(x); // x is converted to type int using the user-defined conversion from X to int

    return 0;
}
```

Step 5) If no match is found via user-defined conversions, the compiler will look for a matching funciton that uses ellipsis.

Step 6) If no matches have been found by this point, the compiler gives up and will issue a compile error about not being able to find a matching function.

## Ambiguous matches

Consider the following:
```cpp
void foo(int)
{
}

void foo(double)
{
}

int main()
{
    foo(5L); // 5L is type long

    return 0;
}
```

This won't have an exact match, long can't be promoted, but tries to apply numeric conversion to the long argument. Now if the long argument is converted to an int, it'll match `foo(int)` but if it's converted to double, it'll match `foo(double)`. Since there's 2 possible matches via numeric conversion, the function call is considered ambiguous.

## Resolving ambiguous matches

Because ambiguous matches are a compile-time error, an ambiguous match needs to be disambiguated before your program will compile. This is done in a few ways:
1. Define a new overloaded function that takes parameters of exactly the type you are trying to call the function with.
2. Explicitly cast the ambiguous argument(s) to match the type of the function you want to call.
3. If the argument is a literal, use the literal suffix to ensure your literal is interpreted as  the correct type.

```cpp
void foo(unsigned int)
{
}

void foo(float)
{
}

int main()
{
    // ambiguous
    foo(0); // int can be numerically converted to unsigned int or to float
    foo(3.14159); // double can be numerically converted to unsigned int or to float

    // NOT ambiguous
    int x{ 0 };
    foo(static_cast<unsigned int>(x)); // will call foo(unsigned int)

    // NOT ambiguous
    foo(0u); // will call foo(unsigned int) since 'u' suffix is unsigned int, so this is now an exact match

    return 0;
}
```

## Matching for functions with multiple arguments

For multiple arguments, the compiler applies the matching rules for each argument. The function chosen must provide a better match than all the other dandidate functions for at least one parameter, and no worse for all of the other parameters.

```cpp
#include <iostream>

void print(char, int)
{
	std::cout << 'a' << '\n';
}

void print(char, double)
{
	std::cout << 'b' << '\n';
}

void print(char, float)
{
	std::cout << 'c' << '\n';
}

int main()
{
	print('x', 'a');

	return 0;
}
```

Because the functions match the first argument exactly, but the second parameter matches the first function via promotion and the others via conversion, the `print(char, int)` is the unambiguously best match.

Consider the following program where we want to check if there's a divide by zero case:

```cpp
void printDivision(int x, int y)
{
    if (y != 0)
        std::cout << static_cast<double>(x) / y;
    else
        std::cerr << "Error: Could not divide by zero\n";
}
```

## Preconditions, invariants, and postconditions

- A **precondition** is any condition that must be true prior to the execution of some section of code (typically the body of a function).

Preconditions are best placed at the top of a function, using an early return to return back to the caller if the precondition isn't met.

```cpp
void printDivision(int x, int y)
{
    if (y == 0) // handle
    {
        std::cerr << "Error: Could not divide by zero\n";
        return; // bounce the user back to the caller
    }

    // We now know that y != 0
    std::cout << static_cast<double>(x) / y;
}
```

- An **invariant** is a condition that must be true while some section of code is executing (often used with loops where the loop body will only execute so long as the invariant is true).

- A **postcondition** is something that must be true after the execution of some section of code.

## Assertions

An **assertion** is an expression that will be true unless there is a bug in the program. If the expression is `true`, the assertion does nothing, and if `false` displays an error message and the program is terminated (via `std::abort`).

C++ runtime assertions are implemented via the **assert** preprocessor macro, which lives in the `<cassert>` header file.

```cpp
#include <cassert> // for assert()
#include <cmath> // for std::sqrt
#include <iostream>

double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity)
{
  assert(gravity > 0.0); // The object won't reach the ground unless there is positive gravity.

  if (initialHeight <= 0.0)
  {
    // The object is already on the ground. Or buried.
    return 0.0;
  }

  return std::sqrt((2.0 * initialHeight) / gravity);
}

int main()
{
  std::cout << "Took " << calculateTimeUntilObjectHitsGround(100.0, -9.8) << " second(s)\n";

  return 0;
}
```

When we run the above program we get:
```
dropsimulator: src/main.cpp:6: double calculateTimeUntilObjectHitsGround(double, double): Assertion 'gravity > 0.0' failed.
```

As you can see here, we accidentally made our gravity negative.

## Making assert statements sexy

Imagine you have this:
```cpp
assert(found)
```

With triggered assert output:
```
Assertion failed: found, file C:\\VCProjects\\Test.cpp, line 34
```

Hardly sexy I know. So we know that found was false, but what else?

Just do this instead:
```cpp
assert(found && "Car could not be found in database");
```

Now we get this as assert output:
```
Assertion failed: found && "Car could not be found in database", file C:\\VCProjects\\Test.cpp, line 34
```

Way sexier right?

- Use assertions to document cases that should be logically impossible

## NDEBUG

`assert` macro comes with a small performance cost and therefore should prefer that asserts are only active in debug builds. C++ comes with a way to turn off asserts in production code via the `NDEBUG` macro. If the `NDEBUG` macro is defined, the assert macro gets disabled.

## static_assert

A **static_assert** is an assertion that is checked at compile-time rather than runtime, and causes a compile error when `static_assert` fails. While regular assert is declared in the `<cassert>` header file, `static_assert` is a keyword, so no header needs to be included to use it.

The form of `static_assert` is:

```
static_assert(condition, diagnostic_message)
```

If the condition is not true, the diagnostic message is printed. Here's an example using static_assert to ensure types have a certain size:

```cpp
static_assert(sizeof(long) == 8, "long must be 8 bytes");
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

int main()
{
    return 0;
}
```

```
1>c:\consoleapplication1\main.cpp(19): error C2338: long must be 8 bytes
```

A few notes about `static_assert`:
- Since `static_assert` is evaluated by the compiler, the condition must be a constexpr
- `static_assert` can be placed anywhere in the code file (even in global)
- `static_assert` is not deactivated in release builds
- Pre C++17 diagnostic messages we required as second parameters. Post C++17, diagnostic messages are optional.



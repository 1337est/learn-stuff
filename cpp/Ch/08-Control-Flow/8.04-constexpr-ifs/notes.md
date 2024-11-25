- Normally if-statements are evaluated at runtime.

However, consider the following:
```cpp
#include <iostream>

int main()
{
	constexpr double gravity{ 9.8 };

	// reminder: low-precision floating point literals of the same type can be tested for equality
	if (gravity == 9.8) // constant expression, always true
		std::cout << "Gravity is normal.\n";   // will always be executed
	else
		std::cout << "We are not on Earth.\n"; // will never be executed

	return 0;
}
```

The else statement here will never execute because `gravity` is constexpr and initialized to `9.8`. Therefore, `gravity == 9.8` will always evaluate to `true`.

## Constexpr if statements C++17

C++17 introduced the **constexpr if statement**, which requires the conditional to be a constexpr and will be evaluated at compile-time.

If the contexpr conditional evaluates to `true`, the ENTIRE if-else will be replaced by the true-statement, and vice-versa the `false` statement if one exists (or do nothing if it doesn't exist).

```cpp
#include <iostream>

int main()
{
    constexpr double gravity{ 9.8 };

    if constexpr (gravity == 9.8) // no uwing constexpr if
        std::cout << "Gravity is normal.\n";
    else
        std::cout << "We are not on Earth.\n";

    return 0;
}
```

Below is what we get when we compile the above program:
```cpp
int main()
{
	constexpr double gravity{ 9.8 };

	std::cout << "Gravity is normal.\n";

	return 0;
}
```



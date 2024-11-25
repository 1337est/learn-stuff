## Implicit type conversion

When the compiler does type conversion on our behalf without us explicitly asking, we call this **implicit type conversion**.

## Type conversion produces a new value

What happens to the original value? A type conversion doesn't actually change  the value. Instead, the value to be "converted" is used as input, and the conversion results in a new value of the target type (via direct initialization).

## An introduction to EXPLICIT type conversion via the `static_cast` operator

Since we don't want to get rid of our "treat warnings as errors" compiler flag, and say we really need to pass a double into an int. We can do so with the `static_cast<new_type>(expression)` syntax (which looks a little wonky).

Here's an example:
```cpp
#include <iostream>

void print(int x)
{
	std::cout << x << '\n';
}

int main()
{
	print( static_cast<int>(5.5) ); // explicitly convert double value 5.5 to an int

	return 0;
}
```

The compiler will not generate a warning about a possible loss of data upon compilation now (Huzzah!).

## Using static_cast to convert char to int

```cpp
#include <iostream>

int main()
{
    char ch{ 97 }; // 97 is ASCII code for 'a'
    std::cout << ch << '\n';

    return 0;
}
```

Outputs
```
a
```

If instead we want to print the integral value of the char instead, we can use static_cast to cast the value from char to an int:
```cpp
#include <iostream>

int main()
{
    char ch{ 97 }; // 97 is ASCII code for 'a'
    std::cout << ch << " has value " << static_cast<int>(ch) << '\n'; // print value of variable ch as an int

    return 0;
}
```

Outputs
```
a has value 97
```



## Boolean variables

`true` or `false` are the only 2 possible values for a boolean variable.

To declare a Boolean variable:
```cpp
bool b;
```

To initialize or assign `true`/`false` value to a Boolean variable:
```cpp
bool b1 { true };
bool b2 { false };
b1 = false;
bool b3 {}; // default initialize to false
```

The logical NOT operator `!` can be used to flip a Boolean value. `!true == false` and vice versa.

## Printing Boolean values

`0` prints for `false` and `1` prints for `true`.
```cpp
#include <iostream>

int main()
{
    std::cout << true << '\n'; // true evaluates to 1
    std::cout << !true << '\n'; // !true evaluates to 0

    bool b {false};
    std::cout << b << '\n'; // b is false, which evaluates to 0
    std::cout << !b << '\n'; // !b is true, which evaluates to 1
    return 0;
}
```

Outputs:
```
1
0
0
1
```

If however, you want the boolean values instead of a numerical value to output, you can use `std::boolalpha`

```cpp
#include <iostream>

int main()
{
    std::cout << true << '\n';
    std::cout << false << '\n';

    std::cout << std::boolalpha; // print bools as true or false

    std::cout << true << '\n';
    std::cout << false << '\n';

    std::cout << std::noboolalpha; // turns the behavior back off

    std::cout << true << '\n';
    std::cout << false << '\n';

    return 0;
}
```
This prints:
```
1
0
true
false
1
0
```

## Inputting Boolean values

Inputting Boolean values using `std::cin` can trip a new programmer up. This is because `std::cin` only accepts 0 or 1 for false or true.

```cpp
#include <iostream>

int main()
{
    bool b{}; // default initialize to false
    std::cout << "Enter a boolean value: ";
    std::cin >> b;
    std::cout << "You entered: " << b << '\n';

    return 0;
}
```

Ouputs:
```
Enter a Boolean value: true
You entered: 0
```

Here we can see that `std::cin` silently failed and therefore outputs 0.

To allow `std::cin` to accept `true` and `false` as inputs, we must first input to `std::boolalpha`:
```cpp
#include <iostream>

int main()
{
    bool b{};
    std::cout << "Enter a boolean value: ";

    // Allow the user to input 'true' or 'false' for boolean values
    // This is case-sensitive, so True or TRUE will not work
    std::cin >> std::boolalpha;
    std::cin >> b;

    // Let's also output bool values as true or false
    std::cout << std::boolalpha;
    std::cout << "You entered: " << b << '\n';

    return 0
}
```



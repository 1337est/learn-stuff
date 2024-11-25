# Chars

The **char** data type was designed to hold a single character, whether that be a single letter, number, symbol, or whitespace.

The integer stored by a `char` variable is interpreted as an ASCII character.

## Interesting behavior inputting chars

Since `std::cin` allows you to enter multiple characters, but `char` only holds 1 character, the rest of the user input is left in the input buffer that `std::cin` uses, and can be extracted with subsequent calls to `std::cin`.

```cpp
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "abcd" (without quotes)

    char ch{};
    std::cin >> ch; // ch = 'a', "bcd" is left queued.
    std::cout << "You entered: " << ch << '\n';

    // Note: The following cin doesn't ask the user for input, it grabs queued input!
    std::cin >> ch; // ch = 'b', "cd" is left queued.
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```

Outputs:
```
Input a keyboard character: abcd
You entered: a
You entered: b
```

## Char size, range, and default sign

Char is defined in C++ to always be 1 byte in size.

By default, char may be signed or unsigned, though is usually signed.

A signed char ranges from -128 to 127, and an unsigned char ranges from 0 to 255.

## Escape sequences

- **escape sequence:** starts with a backslash character, then follows with a letter or number.

Examples:

```cpp
#include <iostream>

int main()
{
    std::cout << "\"This is quoted text\"\n";
    std::cout << "This string contains a single backslash \\\n";
    std::cout << "6F in hex is char '\x6F'\n";
    return 0;
}
```

Outputs:
```
"This is quoted text"
This string contains a single backslash \
6F in hex is char 'o'
```

## Single vs Double quotes

It's best practice to put single chars with single quotes, and string text with double quotes. This helps the compiler optimize more effectively.



## `std::string_view`

`std::string` is expensive to initialize or copy, so C++17 introduced `std::string_view` which is in the `<string_view>` header.

`std::string_view` provides read-only access to an existing string (C-style, `std::string`, or `std::string_view`) without making a copy. Therefore we can access and use the value, but cannot modify it.

- What the `std::string s{ "Hello, world!" }` implementation does, is copies "Hello, world!" into memory allocated for `std::string s` which is slow.
- What the `std::string_view s{ "Hello, world!" }` implementation does, is just allows read access to "Hello, world!" without copying into memory, which is faster.

This would be fine if `std::string` was a fundamental type, but it's not.

You should prefer `std::string_view` over `std::string` WHEN YOU NEED A READ-ONLY STRING, especially for function parameters.

- `std::string_view` is flexible due to the read-only nature. It can be initialized with C-style strings, `std::string` strings, or other `std::string_view` strings.

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string_view s1 { "Hello, world!" }; // initialize with C-style string literal
    std::cout << s1 << '\n';

    std::string s{ "Hello, world!" };
    std::string_view s2 { s };  // initialize with std::string
    std::cout << s2 << '\n';

    std::string_view s3 { s2 }; // initialize with std::string_view
    std::cout << s3 << '\n';

    return 0;
}
```

## `std::string_view` parameters will accept different types of string arguments

C-style strings and `std::string` strings, will implicitly convert to a `std::string_view`. So use `std::string_view` parameters for your functions since other string arguments will work fine.

```cpp
#include <iostream>
#include <string>
#include <string_view>

void printSV(std::string_view str)
{
    std::cout << str << '\n';
}

int main()
{
    printSV("Hello, world!"); // call with C-style string literal

    std::string s2{ "Hello, world!" };
    printSV(s2); // call with std::string

    std::string_view s3 { s2 };
    printSV(s3); // call with std::string_view

    return 0;
}
```

However, `std::string_view` will not implicitly convert to `std::string` unless we:

1. Explicitly create a `std::string` with a `std::string_view` initializer (which is allowed, since this will rarely be done unintentionally).
2. Convert an existing `std::string_view` to a `std::string` using `static_cast`.

## Literals for `std::string_view`

Similar to `std::string` with the `s` suffix, we can do an `sv` suffix after the double quoted C-style (default) string to create a string literal of type `std::string_view`.

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    using namespace std::string_literals; // access the s suffix
    using namespace std::string_view_literals; // access the sv suffix

    std::cout << "foo\n";   // no suffix, C-style string literal
    std::cout << "goo\n"s;  // s suffix, std::string literal
    std::cout << "moo\n"sv; // sv suffix is a std::string_view literal

    return 0;
}
```

## constexpr `std::string_view`

Unlike `std::string`, `std::string_view` has full support for constexpr:

```cpp
#include <iostream>
#include <string_view>

int main()
{
    constexpr std::string_view s{ "Hello, world!" }; // s is a string symbolic constant
    std::cout << s << '\n'; // s will be replaced with "Hello, world!" at compile-time

    return 0;
}
```

## Tips

1. It's best to use `std::string_view` as a read-only function parameter
2. Use a `std::string` function parameter when the function needs to modifythe string passed in as an argument without affecting the caller (rare), or you're using <= C++14 and aren't comfortable with references yet.
3. Use `std::string_view` function parameters when the function returns a C-style string literal or local `std::string_view` that's been initialized with a C-style string literal, or the function returns a `std::string_view` parameter.

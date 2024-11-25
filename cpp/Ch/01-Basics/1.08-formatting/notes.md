## Whitespace

The following variable definitions are all valid:
```cpp
int x;
int                y;
            int
z;
```

Think about readability and whether whitespace in the form of a space or even newline, would be acceptable.

Preprocessor directives must be placed on separate lines:
```cpp
#include <iostream>
#include <string>
```

## Quoted text

Quoted text takes whitespace literally, but newlines are not allowed in quoted text

```cpp
std::cout << "Hello
    world!"; // Not allowed!
```

C++ code can be long, so try and use whitespace efficiently to format your code.
The following will be 3 ways to do the same thing but the last one is the most desirable:
```cpp
// This is pretty hard to read.
#include <iostream>
int main(){std::cout<<"Hello world";return 0;}
```
```cpp
// This is better but still too condensed.
#include <iostream>
int main() {
std::cout << "Hello world";
return 0;
}
```
```cpp
// This is much better (the one I prefer I think, I should start writing like this)
#include <iostream>

int main()
{
    std::cout << "Hello world";

    return 0;
}
```
```cpp
// Or is this the best? I see a lot of people write like this.
#include <iostream>

int main() {
    std::cout << "Hello world";

    return 0;
}
```
```cpp
// Statements may be split over multiple lines like this
#include <iostream>

int main()
{
    std::cout
        << "Hello world"; // works fine
    return 0;
}
```

Lines shouldn't be too long. Typically, 80 characters is the de facto standard for maximum length a line should be.
```cpp
int main()
{
    std::cout << "This is a really, really, really, really, really, really, really, "
        "really long line\n"; // one extra indentation for continuation line

    std::cout << "This is another really, really, really, really, really, really, really, "
                 "really long line\n"; // text aligned with the previous line for continuation line

    std::cout << "This one is short\n";
}
```

Try to put operators at the beginning of the newline instead of the end of the current line
```cpp
std::cout << 3 + 4
    + 5 + 6
    * 7 * 8; // following this is much easier

std::cout << 3 + 4 +
    5 + 6 * 
    7 * 8; // not like this
```

Use whitespace to make the code easier to read by aligning values/comments or by adding space between blocks of code and pairing like entities.
```cpp
// Harder to read
cost = 57;
pricePerItem = 24;
value = 5;
numberOfItems = 17;

// Easier to read
cost          = 57;
pricePerItem  = 24;
value         = 5;
numberOfItems = 17;
```
```cpp
// Harder to read
std::cout << "Hello world!\n"; // cout lives in the iostream library
std::cout << "It is very nice to meet you!\n"; // these comments make the code hard to read
std::cout << "Yeah!\n"; // especially when lines are different lengths

// Easier to read
std::cout << "Hello world!\n";                  // cout lives in the iostream library
std::cout << "It is very nice to meet you!\n";  // these comments are easier to read
std::cout << "Yeah!\n";                         // especially when all lined up
```
```cpp
// Harder to read
// cout lives in the iostream library
std::cout << "Hello world!\n";
// these comments make the code hard to read
std::cout << "It is very nice to meet you!\n";
// especially when all bunched together
std::cout << "Yeah!\n";

// Easier to read
// cout lives in the iostream library
std::cout << "Hello world!\n";

// these comments are easier to read
std::cout << "It is very nice to meet you!\n";

// when separated by whitespace
std::cout << "Yeah!\n";
```

However, when working in someone else's code or another project, it's best to follow the standard that they use. Favor consistency over preference.

If you want to read up on a good C++ style guide, look at the C++ Core Guidelines, maintained by Bjarne Stroustrup and Herb Sutter

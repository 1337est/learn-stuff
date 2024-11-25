## Basic debugging tactics

### 1. Commenting out your code

What it sounds like. You comment out your code to debug. This could be as simple as commenting out the "problem" code.

### 2. Validating your code flow through print statements

When printing information for debugging purposes, use `std::cerr` instead of `std::cout`. The reason for this is because std::cout may be buffered, which means there may be a pause between when you ask std::cout to output information and when it actually does. If you output using std::cout and your program crashes, std::cout may or may not have actually output yet. This can mislead you about where the actual issue is. On the other hand, std::cerr is unbuffered, which means anything you send to it will output immediately. This essentially means the debug information will appear when the bug is encountered without buffer (this is at the cost of some performance, which we don't really care about when debugging anyways).

Let's look at the following with debug statements:
```cpp
#include <iostream>

int getValue()
{
std::cerr << "getValue() called\n";
    return 4;
}

int main()
{
std::cerr << "main() called\n";
    std::cout << getValue << '\n';

    return 0;
}
```

If this was run, you'd see the output:

```
main() called
1
```

As you can see, getValue was never called because we forgot to add parenthesis. Adding the parenthesis yields:
```cpp
#include <iostream>

int getValue()
{
std::cerr << "getValue() called\n";
    return 4;
}

int main()
{
std::cerr << "main() called\n";
    std::cout << getValue() << '\n';

    return 0;
}
```
Outputs:
```
main() called
getValue() called
4
```

### 3. Printing values
It's exactly as it sounds. Print out std::cerr messages that show what values are being passed as parameters for values and functions. Below is an example:

```cpp
#include <iostream>

int add(int x, int y)
{
std::cerr << "add() called (x=" << x <<", y=" << y << ")\n";
	return x + y;
}

void printResult(int z)
{
	std::cout << "The answer is: " << z << '\n';
}

int getUserInput()
{
	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
	int x{ getUserInput() };
std::cerr << "main::x = " << x << '\n';
	int y{ getUserInput() };
std::cerr << "main::y = " << y << '\n';

	int z{ add(x, 5) };
std::cerr << "main::z = " << z << '\n';
	printResult(z);

	return 0;
}
```

Output:
```
Enter a number: 4
main::x = 4
Enter a number: 3
main::y = 3
add() called (x=4, y=5)
main::z = 9
The answer is: 9
```

Now we can see that the `y` parameter was passed in the wrong argument.

### Why using print statements aren't the best for debugging

Print statements are a common technique. However, these are the reasons they kinda suck:
1. Debug statements clutter your code
2. Debug statements clutter the output of your program
3. Debug statements require modifications of your code, which can add/remove new bugs.
4. Debug statements must be removed when you're done with them, but will you get them all?

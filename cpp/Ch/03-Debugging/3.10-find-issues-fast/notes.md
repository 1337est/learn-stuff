## An introduction to defensive programming

- **defensive programming:** practice where a programmer tries to anticipate how the software/program could be used in a way that isn't intended.

## An introduction to testing functions

Here's a primitive form of unit testing for illustrative purposes:
```cpp
#include <iostream>

int add(int x, int y)
{
	return x + y;
}

void testadd()
{
	std::cout << "This function should print: 2 0 0 -2\n";
	std::cout << add(1, 1) << ' ';
	std::cout << add(-1, 1) << ' ';
	std::cout << add(1, -1) << ' ';
	std::cout << add(-1, -1) << ' ';
}

int main()
{
	testadd();

	return 0;
}
```

- **unit testing:** software testing method where the smallest units of the code are tested to determine correct functionality (works as INTENDED).

## An introduction to constraints

Code that checks that some set of assumptions/expectations are being met. If they are not, throw an error, instead of just pumping out garbage. This ensures that errors are caught immediately. You constrain the code.

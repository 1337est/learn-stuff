To access randomization capabilities in C++, we include the `<random>` header.

## Generating random numbers in C++ using Mersenne Twister

- `mt19937` is a Mersenne Twister that generates 32-bit unsigned integers
- `mt19937_64` is a Mersenne Twister that generates 64-bit unsigned integers

```cpp
#include <iostream>
#include <random> // for std::mt19937

int main()
{
	std::mt19937 mt{}; // Instantiate a 32-bit Mersenne Twister

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << mt() << '\t'; // generate a random number

		// If we've printed 5 numbers, start a new row
		if (count % 5 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

```
3499211612      581869302       3890346734      3586334585      545404204
4161255391      3922919429      949333985       2715962298      1323567403
418932835       2350294565      1196140740      809094426       2348838239
4264392720      4112460519      4279768804      4144164697      4156218106
676943009       3117454609      4168664243      4213834039      4111000746
471852626       2084672536      3427838553      3437178460      1275731771
609397212       20544909        1811450929      483031418       3933054126
2747762695      3402504553      3772830893      4120988587      2163214728
```

We instantiate the 32-bit Mersenne Twister engine via the `std::mt19937 mt` statement. now each time we want a 32-bit unsigned integer, we simply call the `mt()` function.

## Rolling a dice using Mersenne Twister

A 32-bit PRNG will generate random numbers between 0 and 4,294,967,295, but we don't always need numbers in that specific range.

We need a way to convert a number that is output from PRNG to the range that we want. 

- A **random number distribution** converts the output of a PRNG into some other distribution of numbers.

And luckily for us, the random library has many random number distributions (most of which won't be used unless you're a statistician or a nerd, which you are right?) There is one random number distribution amongst these that is very usefule: a **uniform distribution** is a random number distribution that produces outputs between two numbers X and Y (inclusive) with equal probability.

```cpp
#include <iostream>
#include <random> // for std::mt19937 and std::uniform_int_distribution

int main()
{
	std::mt19937 mt{};

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

```
3       1       3       6       5       2       6       6       1       2
2       6       1       1       6       1       4       5       2       5
6       2       6       2       1       3       5       4       5       6
1       4       2       3       1       2       2       6       2       1

```

The above always prints the same numbers...

Now to fix the issue, we need to pick a seed that's not a fixed number, i.e. a random number to go along with our randomness, a number that changes every time the program is run.

- Usually the system clock, or the system's random device is used for this random seeding

## Seeding with the system clock

C++ has a `<chrono>` library containing various clocks that we can use to generate a seed value:
```cpp
#include <iostream>
#include <random> // for std::mt19937
#include <chrono> // for std::chrono

int main()
{
	// Seed our Mersenne Twister using steady_clock
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

The above program has only changed in two areas: we're including `<chrono>` which gives us our clock, and we're using the current time from the clock as a seed value from our Mersenne Twister.

## Seeding with the random device

The random library contains a type called `std::random_device` that is an implementation-defined PRNG. Typically `std::random_device` will ask the OS for a PRN:

```cpp
#include <iostream>
#include <random> // for std::mt19937 and std::random_device

int main()
{
	std::mt19937 mt{ std::random_device{}() };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

- Use `std::random_device` to seed your PRNGs (unless it's not implemented properly for your target compiler/architecture).



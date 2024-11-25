- An **algorithm** is a finite sequence of instructions that can be followed to solve some problem or produce some useful result.

- A **pseudo-random number generators (PRNGs)** is an algorithm that generates a sequence of numbers whose properties simulate a sequence of random numbers.

For illustrative purposes:
```cpp
#include <iostream>

// For illustrative purposes only, don't use this
unsigned int LCG16() // our PRNG
{
    static unsigned int s_state{ 0 }; // only initialized the first time this function is called

    // Generate the next number

    // We modify the state using large constants and intentional overflow to make it hard
    // for someone to casually determine what the next number in the sequence will be.

    s_state = 8253729 * s_state + 2396403; // first we modify the state
    return s_state % 32768; // then we use the new state to generate the next number in the sequence
}

int main()
{
    // Print 100 random numbers
    for (int count{ 1 }; count <= 100; ++count)
    {
        std::cout << LCG16() << '\t';

        // If we've printed 10 numbers, start a new row
        if (count % 10 == 0)
            std::cout << '\n';
    }

    return 0;
}
```

```
4339	838	25337	15372	6783	2642	6021	19992	14859	26462	
25105	13860	28567	6762	17053	29744	15139	9078	14633	2108	
7343	642	17845	29256	5179	14222	26689	12884	8647	17050	
8397	18528	17747	9126	28505	13420	32479	23218	21477	30328	
20075	26558	20081	3716	13303	19146	24317	31888	12163	982	
1417	16540	16655	4834	16917	23208	26779	30702	5281	19124	
9767	13050	32045	4288	31155	17414	31673	11468	25407	11026	
4165	7896	25291	26654	15057	26340	30807	31530	31581	1264	
9187	25654	20969	30972	25967	9026	15989	17160	15611	14414	
16641	25364	10887	9050	22925	22816	11795	25702	2073	9516
```

- Seeding a PRNG is when the value used to set the initial state of a PRNG is deterministic when the following input is the same.

```cpp
#include <iostream>

unsigned int g_state{ 0 };

void seedPRNG(unsigned int seed)
{
    g_state = seed;
}

// For illustrative purposes only, don't use this
unsigned int LCG16() // our PRNG
{
    // We modify the state using large constants and intentional overflow to make it hard
    // for someone to casually determine what the next number in the sequence will be.

    g_state = 8253729 * g_state + 2396403; // first we modify the state
    return g_state % 32768; // then we use the new state to generate the next number in the sequence
}

void print10()
{
    // Print 10 random numbers
    for (int count{ 1 }; count <= 10; ++count)
    {
        std::cout << LCG16() << '\t';
    }

    std::cout << '\n';
}

int main()
{
    unsigned int x {};
    std::cout << "Enter a seed value: ";
    std::cin >> x;

    seedPRNG(x); // seed our PRNG
    print10();   // generate 10 random values

    return 0;
}
```
```
Enter a seed value: 7
10458	3853	16032	17299	10726	32153	19116	7455	242	549
```
```
Enter a seed value: 7
10458	3853	16032	17299	10726	32153	19116	7455	242	549
```
```
Enter a seed value: 9876
24071	18138	27917	23712	8595	18406	23449	26796	31519	7922
```

- When creating a PRNG system, make sure you don't have skewed results that lean in favor of certain outputs.

- The length of a PRNG before it begins to repeat itself is called its period/periodicity.

## Randomization in C++

The randomization capabilities in C++ are accessible via the <random> header in the standard library. Within the random library are 6 PRNG families for use (as of C++20):

- `minstd_rand` && `minstd_rand0`
    - Family: Linear congruential generator
    - Period: 2^31
    - State size: 4 bytes
    - Performance: Bad
    - Quality: Awful
    - SHOULD USE? NO
- `mt19937` && `mt19937_64`
    - Family: Mersenne twister
    - Period: 2^19937
    - State size: 2500 bytes
    - Performance: Decent
    - Quality: Decent
    - SHOULD USE? Probs
- `ranlux24` && `ranlux48`
    - Family: Subtract and carry
    - Period: 10^171
    - State size: 96 bytes
    - Performance: Awful
    - Quality: Good
    - SHOULD USE? NO
- `knuth_b`
    - Family: Shuffled linear congruential generator
    - Period: 2^31
    - State size: 1028 bytes
    - Performance: Awful
    - Quality: Bad
    - SHOULD USE? NO
- `default_random_engine`
    - Family: Any of above (implementation defined)
    - Period: Varies
    - State size: Varies
    - Performance: ?
    - Quality: ?
    - SHOULD USE? NO<sup>2</sup>
- `rand()`
    - Family: Linear congruential generator
    - Period: 2^31
    - State size: 4 bytes
    - Performance: Bad
    - Quality: Awful
    - SHOULD USE? NO<sup>NO</sup>


There is ZERO reason to use `knuth_b`, `default_random_engine`, or `rand()` (which is a random number generator provided for compatibility reasons with C).

As of C++20, the Mersenne Twister algorithm is the only PRNG that ships with C++ that has both decent performance and quality.

## So... use the Mersenne Twister?

Probably.

HOWEVER, by modern PRNG standards, the Mersenne Twister is a bit outdated since results can be predicted after seeing 624 generated numbers, making it non-suitable for any application that requires non-predictability.

If you're developing an app that requires high quality randomness, you either make your own, or use a 3rd party library. Popular choices include:
- The Xoshira family and Wyrand for non-cryptographic PRNGs.
- The Chacha family for cryptographic (non-predictable) PRNGs.



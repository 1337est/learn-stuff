Now that we have vectors, let's consider an example of using them efficiently:
```cpp
#include <iostream>

int main()
{
    // allocate 5 integer variables (each with a different name)
    int testScore1{ 84 };
    int testScore2{ 92 };
    int testScore3{ 76 };
    int testScore4{ 81 };
    int testScore5{ 56 };

    int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5) / 5 };

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
```

Now consider using a vector instead:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector testScore { 84, 92, 76, 81, 56 };
    std::size_t length { testScore.size() };

    int average { (testScore[0] + testScore[1] + testScore[2] + testScore[3] + testScore[4])
        / static_cast<int>(length) };

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
```

## Arrays and loops

Note that there's a pattern above. We are moving from index 0 (the start) to the last index n (the end). Let's rewrite the example above with a for loop and looping through the array:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector testScore { 84, 92, 76, 81, 56 };
    std::size_t length { testScore.size() };

    int average { 0 };
    for (std::size_t index{ 0 }; index < length; ++index) // index from 0 to length-1
        average += testScore[index];                      // add the value of element with index `index`
    average /= static_cast<int>(length);                  // calculate the average

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
```

Now we don't have to write `testScore[0] + testScore[1] + ... testScore[n]`, where n should potentially be 100 or more!

Accessing each element of a container in some order is called **traversal**, or **traversing** the container. Traversal is often called **iteration**.

- Note that since the container classes use type `size_t` for length and indices, in this lesson, we'll do the same.

## Combining templates, arrays, and loops unlocks scalability

- Arrays allow us to store multiple objects without having to name each element.
- Loops allow us to traverse an array without having to explicitly list each element.
- Templates allow us to parameterize the element type

```cpp
#include <iostream>
#include <vector>

// Function template to calculate the average of the values in a std::vector
template <typename T>
T calculateAverage(const std::vector<T>& arr)
{
    std::size_t length { arr.size() };

    T average { 0 };                                      // if our array has elements of type T, our average should of type T too
    for (std::size_t index{ 0 }; index < length; ++index) // iterate through all the elements
        average += arr[index];                            // sum up all the elements
    average /= static_cast<int>(length);

    return average;
}

int main()
{
    std::vector class1 { 84, 92, 76, 81, 56 };
    std::cout << "The class 1 average is: " << calculateAverage(class1) << '\n'; // calc average of 5 ints

    std::vector class2 { 93.2, 88.6, 64.2, 81.0 };
    std::cout << "The class 2 average is: " << calculateAverage(class2) << '\n'; // calc average of 4 doubles

    return 0;
}
```

```
The class 1 average is: 77
The class 2 average is: 81.75
```

Nice.

## Typical uses for arrays and loops

1. Calculate a value based on the values of the elements in the array (e.g. average value, sum of values).
2. Search for an existing element in the array (e.g. has exact match, count number of matches, find highest value).
3. Operations over each element in the array (e.g. output each element, multiply all elements by 2).
4. Sorting elements in the array to a specific arrangement (e.g. sort the elements in ascending order).
5. And whatever else you wanna do.




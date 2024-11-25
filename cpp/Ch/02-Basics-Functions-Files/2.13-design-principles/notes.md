# How to design your first programs

I'm now currently equipped with the tools and skills necessary to solve problems, acquired from everyday life. All I need to do to not f-it-up, is a little up-front planning that will save me both time and frustration in the long run.

### Design step 1: Define your goal
Define what your goal is. Ideally, you should be able to state this in a sentence or 2 as a user-facing outcome. E.g.
- Allow the user to organize a list of names and associated phone numbers.
- Generate randomized dungeons that will produce interesting looking caverns.
- Generate a list of stock recommendations for stocks that have high dividends.
- Model how long it takes for a ball dropped off a tower to hit the ground.

Although obvious, this step is important. You wanna make sure your outcome is intended.

### Design step 2: Define requirements
Requirements is a fancy word for both the constraints that your solution needs to abide by (e.g. budget, timeline, space, memory, etc...), as well as the capabilities that the program must exhibit in order to meet the user's needs.

Requirements should focus on the "what", not the "how"

E.g.
- Phone numbers should be saved, so they can be recalled later.
- The randomized dungeon should always contain a way to get from the entrance to an exit.
- The stock recommendations should leverage historical pricing data.
- The user should be able to enter the height of the tower.
- We need a testable version within 7 days.
- The program should produce results within 10 seconds of the user submitting their request.
- The program should crash in less than 0.1% of user sessions.

### Design step 3: Define your tools, targets, and backup plan

Some general steps that would typically take place at this point for an EXPERIENCED programmer:
- Defining what target architecture and/or OS your program will run on.
- Determining what set of tools you will be using.
- Determining whether you will write your program alone or as part of a team.
- Defining your testing/feedback/release strategy.
- Determining how you will back up your code.

However, as a NOOB programmer, the answer to these questions will be: You are writing a program for your own use, on your own system, using an IDE/editor of your choice that you downloaded, and your code is probably not used by anybody but you. This makes things easy.

### Design step 4: Break hard problems into easy ones

Common sense. As an example, many people go to work or school on weekdays, so let's say we want to solve the problem of "go to work".

- Pick out clothes
- Get dressed
- Eat breakfast
- Travel to work
- Brush teeth
- Get out of bed
- Prepare breakfast
- Get on your bicycle
- Take a shower

You can assign these to different categories like so:
- Get from bed to work
    - Bedroom things
        - Turn off alarm
        - Get out of bed
        - Pick out clothes
    - Bathroom things
        - Take a shower
        - Get dressed
        - Brush your teeth
    - Breakfast things
        - Make coffee or tea
        - Eat cereal
    - Transportation things
        - Get on your bicycle
        - Bike to work

### Design step 5: Figure out the sequence of events

More common sense. Ordering the above from first to last thing to do...

### Implementation step 1: Outlining your main function
In the case of a calculator app:
```cpp
int main()
{
    // Get first number from user
//    getUserInput();

    // Get mathematical operation from user
//    getMathematicalOperation();

    // Get second number from user
//    getUserInput();

    // Calculate result
//    calculateResult();

    // Print result
//    printResult();

    return 0;
}
```

### Implementation step 2: Implement each function

In this step, for each function, you'll do these 3 things:

1. Define the function prototype (input and outputs)
2. Write the function
3. Test the function

```cpp
#include <iostream>

// Full implementation of the getUserInput function
int getUserInput()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;

    return input;
}

int main()
{
    // Get first number from user
    int value{ getUserInput() }; // Note we've included code here to test the return value!
    std::cout << value << '\n'; // debug code to ensure getUserInput() is working, we'll remove this later

    // Get mathematical operation from user
//    getMathematicalOperation();

    // Get second number from user
//    getUserInput();

    // Calculate result
//    calculateResult();

    // Print result
//    printResult();

    return 0;
}
```

Remember to implement your functions step by step instead of all in one go.

### Implementation step 3: Final testing

Once the program's finished up, the last step is to make sure the entirety of your program works as intended. If it doesn't, then you fix it. Easy enough, right?

## Words of advice when writing programs
- Keep your programs simple to start.
- Add features over time.
- Focus on one area at a time.
- Test each piece of code as you go.
- Don't invest in premature code perfection.
- Optimize for maintainability, not performance.

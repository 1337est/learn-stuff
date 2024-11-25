You know about matrices right?

If we were to make an array to represent a game of tic-tac-toe with players taking turns placing X and O symbols, you might store board data as 9 individual variables:
```cpp
int ttt[9]; // a C-style array of ints (value 0 = empty, 1 = player 1, 2 = player 2)
```
This defines a C-style array with 9 elements:
```
// ttt[0] ttt[1] ttt[2] ttt[3] ttt[4] ttt[5] ttt[6] ttt[7] ttt[8]
```

This is a 1d array. Pretty obvious right? Put even more plainly, we could say the board looks like this right now
```
0(empty) 1(empty) 2(empty) 3(empty) 4(empty) 5(empty) 6(empty) 7(empty) 8(empty)
```

That's only a single line. Tic-Tac-Toe is represented on a plane (meaning 2 dimensions).

## Two-dimensional arrays

We can define an array of arrays! It's simple:
```cpp
int a[3][5]; // a 3-element array of 5-element arrays of int
```

This produces an array that looks something like this:
```
// col 0    col 1    col 2    col 3    col 4
// a[0][0]  a[0][1]  a[0][2]  a[0][3]  a[0][4]  row 0
// a[1][0]  a[1][1]  a[1][2]  a[1][3]  a[1][4]  row 1
// a[2][0]  a[2][1]  a[2][2]  a[2][3]  a[2][4]  row 2
```

To access such an array is also simple:
```cpp
a[2][3] = 7; // a[row][col], where row = 2 and col = 3
```

So in order to represent our Tic-Tac-Toe board, we need a 2d array:
```cpp
int ttt[3][3];
```

You get the idea now right?
```
// col 0    col 1    col 2
// a[0][0]  a[0][1]  a[0][2]  row 0
// a[1][0]  a[1][1]  a[1][2]  row 1
// a[2][0]  a[2][1]  a[2][2]  row 2
```

Of course, you can apply this to any dimensional plane you want.

## How 2d arrays are laid out in memory

C++ uses **row-major order**, which means elements are sequentially placed in memory row-by-row (left to right), then moving down to the next column at the end of each row and repeating. For a row of ints in our 2d tic-tac-toe board, we would have:
```
// col 0    col 1   col 2
// 1st      2nd     3rd     row 0
// 4th      5th     6th     row 1
// 7th      8th     9th     row 2
```

## Initializing 2d arrays

It's done how you would expect it to be done:
```cpp
int array[3][5]
{
  {  1,  2,  3,  4,  5 },   // row 0
  {  6,  7,  8,  9, 10 },   // row 1
  { 11, 12, 13, 14, 15 }    // row 2
};
```



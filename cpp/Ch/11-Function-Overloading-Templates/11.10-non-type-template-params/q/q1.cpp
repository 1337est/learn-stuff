// define your factorial() function emplate here
template <int N>
constexpr int factorial()
{
    static_assert(N >= 0, "factorial(): N must be non-negative");

    int sum{ 1 }; // factorial of 0 && 1 is 1
    for (int i { 2 }; i <= N; ++i)
    {
        sum *= i;
    }
    return sum;
}

int main()
{
    static_assert(factorial<0>() == 1);
    static_assert(factorial<3>() == 6);
    static_assert(factorial<5>() == 120);

    factorial<3>(); // should fail to compile

    return 0;
}

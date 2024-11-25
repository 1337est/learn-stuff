int readNumber();
void writeAnswer(int input);

int main()
{
    int a { readNumber() };
    int b { readNumber() };

    writeAnswer(a + b);

    return 0;
}

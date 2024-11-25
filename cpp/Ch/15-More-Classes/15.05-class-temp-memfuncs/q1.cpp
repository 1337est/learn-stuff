#include <iostream>
#include <string>

template <typename T, typename U, typename V>
class Triad
{
private:
    T m_a{};
    U m_b{};
    V m_c{};
public:
    Triad(const T& a, const U& b, const V& c)
        : m_a { a }
        , m_b { b }
        , m_c { c }
    {
    }

    const T& a() const { return m_a; };
    const T& b() const { return m_b; };
    const T& c() const { return m_c; };

    void print() const;
};

template <typename T, typename U, typename V>
void Triad<T, U, V>::print() const
{
    std::cout << '[' << m_a << ", " << m_b << ", " << m_c << ']';
}

int main()
{
	Triad<int, int, int> t1{ 1, 2, 3 };
	t1.print();
	std::cout << '\n';
	std::cout << t1.a() << '\n';

	using namespace std::literals::string_literals;
	const Triad t2{ 1, 2.3, "Hello"s };
	t2.print();
	std::cout << '\n';

	return 0;
}

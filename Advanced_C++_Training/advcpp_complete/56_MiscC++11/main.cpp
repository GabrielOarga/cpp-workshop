#include <array>
#include <iostream>
#include <numeric>


using namespace std;

/**
 * std::array should be preferred instead of C-style arrays
 * It has the benefits of C arrays when it comes to size: same size, no 
 */
void test_std_array()
{
    array<int, 10> cpp_arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int c_arr[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // std::array has the benefits of both C arrays (size) and STL vectors (functionality)

    static_assert(sizeof(cpp_arr) == 10 * sizeof(int), "CPP array: wrong size!");
    static_assert(sizeof(cpp_arr) == sizeof(c_arr), "CPP array is different in size than C array");

    // std::array - functionality benefits:
    cout << accumulate(cpp_arr.begin(), cpp_arr.end(), 0) << endl;
    cout << accumulate(cpp_arr.begin(), cpp_arr.end(), 1, [](int a, int b) { return a * b; }) << endl;
}


void test_func()
{
    // __func__ is a string containing the value of the current function
    cout << __func__ << endl;
}


void test_cast_operator()
{
    // you can define implicit and explicit operators for converting
    // an object from a class to another
    class A
    {
    public:
        explicit A(int x) : x(x) {}
        operator int() const { return x; }
    private:
        int x{};
    };

    A a{ 10 };
    auto b = int(a);
    auto c = static_cast<int>(a);   // of course, the preferred way
    cout << b << endl;
    cout << c << endl;
}


int main()
{
    test_std_array();
    test_func();
    test_cast_operator();

    getchar();
    return 0;
}

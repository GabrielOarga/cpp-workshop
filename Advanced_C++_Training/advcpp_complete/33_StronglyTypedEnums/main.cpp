#include <iostream>

using namespace std;

// in C++ 03 enums are integral types
enum cpp03_1 { a, b, c };
enum cpp03_2 { m, n, o };

// these are still supported, but we also have strongly-typed enums
// strongly-typed enums are preffered in all cases
enum class cpp11_1 { a, b, c };
enum class cpp11_2 { m, n, o };

enum class Day { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };

enum class Planet
{
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE
};


int main()
{
    auto a1{ cpp03_1::a };
    auto a2{ cpp03_2::m };

    if (a1 == a2) {
        cout << "a1 and a2 are equal" << endl;
    } else {
        cout << "a1 and a2 are not equal" << endl;
    }

    auto m1{ cpp11_1::a };
    auto m2{ cpp11_2::m };

    //    if (m1 == m2) // not compiling

	auto day{ Day::SUNDAY };
	auto planet{ Planet::MERCURY };

    // the code bellow doesn't even compile:
    //if (day == planet)
    //    cout << "two variables of DIFFERENT enum types ARE equal" << endl;

    switch (m1) {
    case cpp11_1::a:
        break;
    case cpp11_1::b:
        break;
    case cpp11_1::c:
        break;
    default:
        break;
    }

    getchar();
    return 0;
}

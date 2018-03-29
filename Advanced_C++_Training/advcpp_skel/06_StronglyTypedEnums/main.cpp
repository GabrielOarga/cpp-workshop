#include <iostream>

using namespace std;


// In C++ 03 enums are integral types
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

    getchar();
    return 0;
}

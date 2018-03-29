#include "Matrix.h"
#include <iostream>
#include <string>

using namespace std;


int main()
{
    // create and display a 10x10 matrix
    cout << "Matrix<int> m(10, 10):" << endl;
    Matrix<int> m(10, 10);
    for (auto i = 0u; i < 10u; i++)
        for (auto j = 0u; j < 10u; j++)
            m.add(i, j, j);
    cout << m << endl << endl;  // operator<<

    cout << "Matrix<int> m2 = m:" << endl;
    auto m2 = m;  // call copy constructor
    cout << m2 << endl << endl;

    cout << "Matrix<int> mat(5, 5):" << endl;
    Matrix<int> mat(5, 5);
    for (auto i = 0u; i < 5u; i++)
        for (auto j = 0u; j < 5u; j++)
            mat.add(i, j, j);
    cout << mat << endl << endl;

    cout << "m2 = mat:" << endl;
    m2 = mat;
    cout << m2 << endl << endl;

    cout << "m2 = m2 + 1:" << endl;
    m2 = m2 + 1;
    cout << m2 << endl << endl;

    cout << "m2 += 1:" << endl;
    m2 += 1;
    cout << m2 << endl << endl;

    cout << "m2 -= 1:" << endl;
    m2 -= 1;
    cout << m2 << endl << endl;

    cout << "m2 = m + m:" << endl;
    m2 = m + m;
    cout << m2 << endl << endl;

    Matrix<string> strings(5u, 5u);
    for (auto i = 0u; i < 5u; i++) {
        for (auto j = 0u; j < 5u; j++) {
            strings.add(i, j, "text" + j);
        }
    }

    cout << strings << endl;
    cout << strings + "1" << endl;
    strings += "2";
    cout << strings << endl << endl;
    cout << strings << endl << endl;

    getchar();
    return 0;
}

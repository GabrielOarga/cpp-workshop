#include <iostream>
#include <vector>
#include "RandomUtil.h"

using namespace std;
using namespace edocti::utils;


void showMat1(vector<vector<int>>& mat)
{
    for (auto i = 0u; i < mat.size(); i++) {
        for (auto j = 0u; j < mat[i].size(); j++)
            cout << mat[i][j] << " ";
        cout << "size: " << mat[i].size() << ", capacity: " << mat[i].capacity() << endl;
    }
    cout << endl;
}


void showMat2(vector<vector<int>>& mat)
{
    for (auto vv : mat) {
        for (auto elem : vv)
            cout << elem << " ";
        cout << "size: " << vv.size() << ", capacity: " << vv.capacity() << endl;
    }
    cout << endl;
}


// old-school iteration
void showMat3(vector<vector<int>>& mat)
{
    for (vector<vector<int>>::iterator it = mat.begin(); it != mat.end(); ++it) {
        for (vector<int>::iterator i = it->begin(); i != it->end(); ++i)
            cout << *i << " ";
        cout << "size: " << it->size() << ", capacity: " << it->capacity() << endl;
    }
    cout << endl;
}


void generate_vector(int n, vector<int>& v)
{
    RandomUtil::randomize();
    auto len = RandomUtil::nextInt(1, n);

    for (auto i = 0; i < len; i++) {
        v.push_back(RandomUtil::nextInt(50, 100));
    }
}


void generate_2d_vector(int n, int m, vector<vector<int>>& v)
{
    for (auto i = 0; i < n; i++) {
        vector<int> vv;
        generate_vector(m, vv);
        v.push_back(vv);
    }
}


void generate_3d_vector(int x, int y, int z, vector<vector<vector<int>>>& v)
{
    for (auto i = 0u; i < x; i++) {
        vector<vector<int>> vv;
        generate_2d_vector(y, z, vv);
        v.push_back(vv);
    }
}


void test_capacity()
{
    vector<double> numbers(20);
    cout << "Size: " << numbers.size() << endl;
    unsigned int capacity = numbers.capacity();
    cout << "Capacity: " << capacity << endl;
}


int main()
{
    vector<vector<vector<int>>> v;
    generate_3d_vector(3, 10, 10, v);
    for (auto elem : v)
        showMat1(elem);

    for (auto elem : v)
        showMat2(elem);

    for (auto elem : v)
        showMat3(elem);

    test_capacity();
    getchar();

    return 0;
}

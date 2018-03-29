#include <iostream>
#include <cstdlib>

using namespace std;

int main(void)
{
	int a[3] = {0, 1, 2}; // Fixed-Length array decalered with init list

	int var;
	cout << "Var-Length array size pls: " << endl;
	cin >> var;
	int b[var]; //Variable Length array declared (not dynamic)

	b[0] = 0;
	b[1] = 1;
	b[2] = 2;

	int* c; //Pointer to int declared (to be dynamic array)
	c = (int*)malloc(sizeof(int) * 3);

	if (c)
	{
		c[0] = 0;
		c[1] = 1;
		c[2] = 2;
	}

	// --------- Fixed-Length array
	cout << "Fixed length array" << endl;
	cout << a << endl;
	cout << &a << endl;

	cout << &(*a) << endl;
	cout << &a[0] << endl;

	cout << *a << endl;
	//cout << *(a++) << endl; //not a pointer, not arithmetics can be used
	cout << a[0] << endl;
	cout << a[1] << endl;

	// --------- Var-Length array
	cout << "\nVar length array" << endl;
	cout << b << endl;
	cout << &b << endl;

	cout << &(*b) << endl;
	cout << &b[0] << endl;

	cout << *b << endl;
	//cout << *(a++) << endl; //not a pointer, not arithmetics can be used
	cout << b[0] << endl;
	cout << b[1] << endl;

	// --------- Dynamic length array
	cout << "\nVar length array" << endl;
	cout << c << endl;
	cout << ++c << endl;
	cout << ++c << endl;
	c--;
	c--;
	cout << &c << endl;

	cout << "---" << endl;
	cout << &(*c) << endl;
	cout << &c[0] << endl;
	cout << &c[1] << endl;
	cout << &c[2] << endl;

	cout << "---" << endl;
	cout << *c << endl;
	//cout << *(++c) << endl; // is a pointer
	cout << c[0] << endl;
	cout << c[1] << endl;
	cout << c[2] << endl;


	return 0;
}

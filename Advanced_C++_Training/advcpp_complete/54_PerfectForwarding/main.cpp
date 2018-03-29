#include <iostream>
#include <vector>

using namespace std;

struct Test
{
	Test() { cout << "Test() - " << this << endl; }
	~Test() { cout << "~Test() - " << this << endl; }
	Test(Test&& other) noexcept { cout << "Test(&&) - " << this << endl; }
	Test& operator=(const Test&) { cout << "Test&= - " << endl; }
};

void level2(Test& test)
{
    cout << "level2 - lValue" << endl;
}


void level2(Test&& test)
{
    cout << "level2 - rValue" << endl;
}


Test getTest()
{
    return Test();
}


template<typename T>
void level1_1(T &&t)
{
    level2(t);
}

void level1_2(Test &&t)
{
	level2(static_cast<Test&&>(t));
}


void level1_3(Test &&t)
{
    level2((Test&&)t);  // C-style cast also possible; BUT: T&&(t) doesn't work! :)
}


void level1_4(Test &&t)
{
    level2(std::forward<Test>(t));    // same thing as in level1_2, but it's clear what we want
}


template <typename T>
void swap(T& a, T& b) noexcept
{
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}


/**
 * Appends a new element to the end of the container.
 * <p>
 * The element is constructed through std::allocator_traits::construct,
 * which typically uses placement-new to <strong>construct the element in-place
 * at the location provided by the container</strong>
 */
void test_emplace_back() noexcept
{
    vector<Test> v{};
	cout << "==================" << endl;
    cout << "Test emplace_back - begin: adding 2 Test object:" << endl;
    v.emplace_back();  // one construction
    cout << "Test emplace_back - end" << endl;
    cout << "Test push_back - begin: adding 1 Test object:" << endl;
    v.push_back(Test{});  // one construction and two moves
    cout << "Test push_back - end" << endl;

	cout << "==================" << endl;
    // Conclusion: emplace_back eliminates the extra copy or move operation
    // that is required by push_back
}


int main()
{
    auto&& t = getTest();
    level2(t);
    level2(getTest());        // we already know the rules :)

	// now let's try a call chain:
    level1_1(getTest());      // lValue version
    level1_1(Test());         // lValue version
    level1_1(t);

    level1_2(Test());         // rValue version => static_cast<T&&> makes the call to 
    // level1_2(t);           // won't compile! (logic)
    level1_3(Test());
    level1_4(Test());

    test_emplace_back();

    getchar();
    return 0;
}

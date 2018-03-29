#include <vector>
#include <string>
#include <iostream>


using namespace std;


class Test
{
public:
    Test(initializer_list<int> numbers, std::string m_name)
    : m_numbers(numbers)
    { }
    
    friend ostream& operator << (ostream& out, const Test& test)
    {
        for (int i : test.m_numbers)
        {
            out << i << " ";
        }
        return out;
    }
    
    static void print(initializer_list<string> values)
    {
        cout << "printing..." << endl;
        for (auto v: values)
        {
            cout << v << " ";
        }
        cout << endl;
    }
    
private:
    vector<int> m_numbers;
    std::string m_name;
    
    
};


int main()
{
    // Init list is more efficient than pushback, pushback also creates copies and allocates mem every time you run it
    // where init list allocates only once (check this for validity)
    Test t{ { 1, 2, 3, 4, 5}, "Cucu" };
    cout << t << endl;
    t.print({"ana", "are", "mere"}); // Woah, this is awesome, play with this more
    getchar();
    return 0;
}

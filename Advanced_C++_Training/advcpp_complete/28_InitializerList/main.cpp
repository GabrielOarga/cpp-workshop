#include <iostream>
#include <vector>
#include <initializer_list>
#include <string>

using namespace std;


class Test
{
public:
    Test(initializer_list<string> values, int number) noexcept :
        m_names(values),
		m_number(number)
    {
    }

    static void print(initializer_list<string> values) noexcept
    {
        cout << "printing values: ";
        for (auto v: values) {
            cout << v << " ";
        }
        cout << endl;
    }

    friend ostream& operator<<(ostream& out, const Test& t) noexcept
    {
        for (auto n : t.m_names) {
            out << n << " ";
        }
		out << m_number;
        return out;
    }
private:
    vector<string> m_names{};
	int m_number;
};


int main()
{
    
	Test t{ {"ana", "are", "mere"}, 10 };  // here we construct our custom class with an initializer list
    t.print({"cucurigu", "boieri", "mari"});  // we can pass directly an "inline" array as argument
    cout << t << endl;

    getchar();
    return 0;
}

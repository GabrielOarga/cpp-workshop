#include <iostream>
#include <random>
#include "RandomUtil.h"

using namespace std;
using namespace edocti::utils;


void throw_an_exception()
{
    RandomUtil::randomize();
    auto err = RandomUtil::nextInt(1, 10);
    if (err <= 3) {
        throw 108;
    } else if (err > 3 && err < 7) {
        throw "A const char* exception";
    } else {
        throw string("A string exception");
    }
}


int main()
{
    for (auto i = 0; i < 10; i++) {
        try {
            throw_an_exception();
        } catch (int e) {
            cout << "Caught " << e << endl;
        } catch (char const* e) {
            cout << "Caught " << e << endl;
        } catch (string& e) {
            cout << "Caught " << e.c_str() << endl;
        } catch (...) {
            cout << "Any other kind of exception" << endl;
        }
    }

    getchar();

    return 0;
}

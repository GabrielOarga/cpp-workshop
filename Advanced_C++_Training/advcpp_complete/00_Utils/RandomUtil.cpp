#include "RandomUtil.h"

using namespace std;

namespace edocti { namespace utils {
    default_random_engine& RandomUtil::global_engine()
    {
        // each engine instance is initialized with the same
        // seed => even new objects will produce the same sequence
        // => we make this static and rely on randomize()
        static default_random_engine engine{};
        return engine;
    }


    void RandomUtil::randomize()
    {
        // in order to have different sequences, we must set the seed
        // to a(n almost) truly random value. Such a value is provided
        // by a random_device (usually a HW sub-system). See
        // https://software.intel.com/en-us/articles/intel-digital-random-number-generator-drng-software-implementation-guide
        static random_device device{};
        global_engine().seed(device());
    }


    int RandomUtil::nextInt(int start, int end)
    {
        // distributions generate sequences of unsigned integers
        // (the precise type being provided by each class' typedef)
        // the distribution classes map these numbers to values whose
        // probability corresponds to the parameterized distribution

        static uniform_int_distribution<> dist{};
        using param_t = decltype(dist)::param_type;
        return dist(global_engine(), param_t{start, end});
    }


    double RandomUtil::nextDouble(double start, double end)
    {
        static uniform_real_distribution<> dist{};
        using parm_t = decltype(dist)::param_type;
        return dist(global_engine(), parm_t{start, end});
    }
}}

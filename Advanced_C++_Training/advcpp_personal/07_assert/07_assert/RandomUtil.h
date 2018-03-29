#pragma once
#include <random>

namespace edocti {
    namespace utils
    {
        /**
        * Random number generators produce sequences of numbers
        * which <strong>appear</strong> random. However, most of
        * them use calculations which are pseudo-random; they have
        * an internal state == SEED, which is transformed
        * <strong>deterministically</strong> each time a number is
        * requested => you obtain the same sequence of pseudo-random
        * numbers if you use the same seed.
        * <p>
        * This class implements some convenient methods for dealing
        * with random numbers.
        * <p>
        * Before C++11 we only relied on rand() and srand() (from C)
        * which have a limited functionality and offer a low-quality
        * random generation => <random> library was added in C++11.
        * @author pianas
        */
        class RandomUtil
        {
        public:
            /**
            * Makes the following numbers random by initializing the seed.
            * Without a call to randomize() you will get the same numbers sequence
            */
            static void randomize();

            /**
            * @return  an int value between [start, end]
            */
            static int nextInt(int start, int end);

            /**
            * @return  a double value between [start, end)
            */
            static double nextDouble(double start, double end);

        private:
            /**
            * Returns a global random engine
            */
            static std::default_random_engine& global_engine();
        };
    }
}

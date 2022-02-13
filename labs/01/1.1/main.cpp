#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/timer.hpp>

int main()
{
    std::vector<size_t> v = {7, 1, 12, 5, 9, 20, 15, 2, 3, 4, 21, 23, 26, 28, 99};
    boost::timer timer;
    timer.restart();
    std::sort(v.begin(), v.end());
    do
    {
        copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
        std::cout << std::endl;
    }
    while (std::next_permutation(v.begin(), v.end()));
    double duration = timer.elapsed();

    std::cout << duration << std::endl;
}

/*
 * 7 - 0.2s
 * 10 - 17s
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/timer.hpp>

void GetSort(std::vector<size_t> &v);

double GetTimer(std::vector<size_t> &v);

int main()
{
    std::vector<size_t> v = {7, 1, 12, 5, 9, 20, 15};
    double duration = GetTimer(v);
    std::cout << duration << std::endl;

    return 0;
}

double GetTimer(std::vector<size_t> &v)
{
    boost::timer timer;
    timer.restart();

    GetSort(v);

    double duration = timer.elapsed();

    return duration;
}

void GetSort(std::vector<size_t> &v)
{
    std::sort(v.begin(), v.end());
    do
    {
        copy(v.begin(), v.end(), std::__1::ostream_iterator<size_t>(std::cout, " "));
        std::cout << std::endl;
    }
    while (std::next_permutation(v.begin(), v.end()));
}

/*
 * 7 - 0.18s
 * 10 - 17s
 */
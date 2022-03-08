#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/timer.hpp>

void getRandom(std::vector<int> &randomVector);
void print(std::vector<int> &randomVector);

int main()
{
    std::cout << std::endl;
    std::cout << "Алгоритм порождения случайной перестановки" << std::endl;

    srand(time(nullptr));
    std::vector<int> randomVector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << "input :" << std::endl;
    print(randomVector);

    getRandom(randomVector);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "output :" << std::endl;
    print(randomVector);

    std::cout << std::endl;

    return 0;
}

void getRandom(std::vector<int> &randomVector)
{
    int randomValue = 0;
    for (int i = 0; i < randomVector.size(); ++i)
    {
        randomValue = rand() % randomVector.size();
        std::swap(randomVector[i], randomVector[randomValue]);
    }
}

void print(std::vector<int> &randomVector)
{
    for (int i : randomVector)
    {
        std::cout << i;
    }
}
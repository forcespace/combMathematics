#include <iostream>
#include <vector>
#include <boost/timer.hpp>

void iteratingElOfVectorPermutations(int count, std::vector<int> &currentVector, std::vector<int> &reverseVector, std::vector<int> &directionOfPermutation);

int getInput();

void print(std::vector<int> &result)
{

    for (int i = 1; i < result.size() - 1; ++i) {
//        std::cout << result[i] << " ";
    }

    std::cout << std::endl;
}

int main()
{
    int count = getInput();

    boost::timer time;
    time.restart();

    int countWithBorders = count + 2;

    std::vector<int> currentVector(countWithBorders);
    std::vector<int> reverseVector(countWithBorders);
    std::vector<int> directionOfPermutation(countWithBorders);

    iteratingElOfVectorPermutations(count, currentVector, reverseVector, directionOfPermutation);

    directionOfPermutation[0] = 0;
    currentVector[0] = count + 1;
    currentVector.back() = count + 1;

    int border = 0;

    while (border != 1)
    {
        print(currentVector);
        border = count;

        while (currentVector[reverseVector[border] + directionOfPermutation[border]] > border && border > 1)
        {
            directionOfPermutation[border] = -directionOfPermutation[border];
            border = border - 1;
        }

        std::swap(currentVector[reverseVector[border]], currentVector[reverseVector[border] + directionOfPermutation[border]]);
        std::swap(reverseVector[currentVector[reverseVector[border]]], reverseVector[border]);
    }

    double duration = time.elapsed();
    std::cout << duration << std::endl;
}

int getInput()
{
    int count;
    std::cin >> count;
    std::cout << std::endl;
    return count;
}

void iteratingElOfVectorPermutations(int count, std::vector<int> &currentVector, std::vector<int> &reverseVector, std::vector<int> &directionOfPermutation)
{
    for (int i = 1; i <= count; ++i)
    {
        currentVector[i] = i;
        reverseVector[i] = i;
        directionOfPermutation[i] = -1;
    }
}
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iterator>

void PrintItems(std::vector<int> items);

std::vector<int> SetItems(int maxItems);

void RandomSwap(int maxItems, std::vector<int> &items);

int main()
{
    const int maxItems = 10;
    std::vector<int> items = SetItems(maxItems);

    PrintItems(items);

    RandomSwap(maxItems, items);

    PrintItems(items);

    return 0;
}

void RandomSwap(const int maxItems, std::vector<int> &items)
{
    for (int i = 0; i < maxItems; ++i)
    {
        const int randomPosition = rand() % (maxItems - 1);
        std::swap(items.at(i), items.at(randomPosition));
    }
}

std::vector<int> SetItems(const int maxItems)
{
    std::vector<int> items(maxItems);
    srand(time(nullptr));

    for (int i = 0; i < maxItems; i++)
    {
        items[i] = i + 1;
    }
    return items;
}

void PrintItems(std::vector<int> items)
{
    copy(items.begin(), items.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
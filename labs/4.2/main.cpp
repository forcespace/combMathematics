#include <iostream>
#include <optional>
#include <vector>
#include <fstream>

std::string programMessage[] = {
        "Invalid arguments count",
        "No",
        "Yes",
        "Failed to open input for reading",
        "Matrix attributes error"
};

constexpr int MAX_MATRIX_SIZE = 100;

typedef std::vector<std::vector<int> > Matrix;

struct KunnStruct
{
    int leftSize = 0;
    int rightSize = 0;
    std::vector<std::vector<int>> edges;
    std::vector<int> matchingPair;
    std::vector<bool> usedPair;
};

struct Args
{
    std::string inputFileName;
};

std::optional<Args> parseArgs(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << programMessage[0] << std::endl;
        return std::nullopt;
    }

    Args args;
    args.inputFileName = argv[1];

    return args;
}

int getMatrix(std::ifstream &input, Matrix &field, int sizeX, int sizeY)
{
    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            input >> field[i][j];
        }
    }

    return 0;
}


KunnStruct getDataFromMatrix(Matrix &matrix, int sizeX, int sizeY)
{
    KunnStruct data;

    data.edges.resize(sizeY);

    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            if (matrix[i][j])
            {
                data.edges[i].push_back(j);
            }
        }
    }

    data.leftSize = sizeY;
    data.rightSize = sizeX;

    return data;
}

bool initData(KunnStruct &data, int vertex)
{
    if (data.usedPair[vertex])
    {
        return false;
    }

    data.usedPair[vertex] = true;
    for (size_t i = 0; i < data.edges[vertex].size(); ++i)
    {
        int to = data.edges[vertex][i];
        if (data.matchingPair[to] == -1 || initData(data, data.matchingPair[to]))
        {
            data.matchingPair[to] = vertex;
            return true;
        }
    }

    return false;
}

void SolveKunn(KunnStruct &data)
{
    data.matchingPair.assign(data.rightSize, -1);
    for (int vertexNumber = 0; vertexNumber < data.leftSize; vertexNumber++)
    {
        data.usedPair.assign(data.leftSize, false);
        initData(data, vertexNumber);
    }
}

void print(KunnStruct data)
{
    bool isHaveSolution = true;
    for (int vertex = 0; vertex < data.rightSize; vertex++)
    {
        if (isHaveSolution && data.matchingPair[vertex] == -1)
        {
            isHaveSolution = false;
        }
    }

    if (!isHaveSolution)
    {
        std::cout << programMessage[1] << std::endl;
        return;
    }
    else
    {
        std::cout << programMessage[2];
        for (int vertex = 0; vertex < data.rightSize; vertex++)
        {
            std::cout << data.matchingPair[vertex] + 1 << ' ' << vertex + 1 << "\n";
        }
    }

}

int main(int argc, char *argv[])
{
    auto args = parseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    std::ifstream input(args->inputFileName);
    if (!input.is_open())
    {
        std::cout << programMessage[3] << std::endl;
        return 1;
    }

    int p = 0, q = 0;
    input >> p >> q;

    if (p <= 0 || p > MAX_MATRIX_SIZE || q <= 0 || q > MAX_MATRIX_SIZE)
    {
        std::cout << programMessage[4];
        return 1;
    }

    Matrix matrix(p, std::vector<int>(q, 0));
    getMatrix(input, matrix, q, p);

    KunnStruct kunnData = getDataFromMatrix(matrix, q, p);

    SolveKunn(kunnData);

    print(kunnData);

    return 0;
}